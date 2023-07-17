/* Arithmo - A library for math expressions processing
 * Copyright (C) 2023 Stan Vlad <vstan02@protonmail.com>
 *
 * This file is part of Arithmo.
 *
 * Arithmo is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "arithmo.h"
#include "table.h"
#include "lexer.h"

#define ARTM_VALUE(_value_) \
  ((artm_result_t) { ARTM_SUCCESS, { .value = (_value_) } })

#define ARTM_ERROR(_status_, _token_) \
  ((artm_result_t) { (_status_), { .token = { (_token_).size, (_token_).target } } })

#define ARTM_CHECK_TOKEN(_calc_) \
  do { \
    if (check(_calc_, TKN_ERROR)) { \
      return ARTM_ERROR(ARTM_INV_TOKEN, _calc_->token); \
    } \
  } while (0)

#define ARTM_CHECK_RESULT(_var_name_) \
  do { \
    if (_var_name_.status != ARTM_SUCCESS) { \
      return _var_name_; \
    } \
  } while (0)

#define ARTM_ADVANCE(_calc_) \
  do { \
    _calc_->token = lexer_next(&_calc_->lexer); \
    ARTM_CHECK_TOKEN(_calc_); \
  } while (0)

#define ARTM_CONSUME(_calc_, _type_, _status_) \
  do { \
    if (_calc_->token.type == _type_) { \
      ARTM_ADVANCE(_calc_); \
    } else { \
      return ARTM_ERROR(_status_, _calc_->token); \
    } \
  } while (0)

struct artm_calc {
  table_t decls;
  lexer_t lexer;
  token_t token;
};

static artm_result_t parse_decl(artm_calc_t* calc);
static artm_result_t parse_call(artm_calc_t* calc);
static artm_result_t parse_expr(artm_calc_t* calc);
static artm_result_t parse_term(artm_calc_t* calc);
static artm_result_t parse_factor(artm_calc_t* calc);
static artm_result_t parse_paren(artm_calc_t* calc);

static inline bool check(artm_calc_t* calc, token_type_t type) {
  return calc->token.type == type;
}

static inline bool match(artm_calc_t* calc, token_type_t type1, token_type_t type2) {
  return check(calc, type1) || check(calc, type2);
}

extern artm_calc_t* artm_calc_init(size_t decl_table_size) {
  artm_calc_t* result = (artm_calc_t*) malloc(sizeof(artm_calc_t));
  if (result == NULL) {
    return NULL;
  }

  table_init(&result->decls, decl_table_size);
  return result;
}

extern void artm_calc_free(artm_calc_t* calc) {
  if (calc != NULL) {
    table_free(&calc->decls);
    free(calc);
  }
}

extern artm_result_t artm_calc_eval(artm_calc_t* calc, const char* expression) {
  if (calc == NULL) {
    return ARTM_ERROR(ARTM_NULL_CALC, (token_t) { 0 });
  }

  if (expression == NULL) {
    return ARTM_ERROR(ARTM_NULL_EXPR, (token_t) { 0 });
  }

  lexer_init(&calc->lexer, expression);
  calc->token = lexer_next(&calc->lexer);
  switch (calc->token.type) {
    case TKN_ERROR:
      return ARTM_ERROR(ARTM_INV_TOKEN, calc->token);
    case TKN_END:
      return ARTM_VALUE(0);
    case TKN_DOLLAR:
      return parse_decl(calc);
    default:
      return parse_expr(calc);
  }
}

extern double artm_calc_cbk_eval(artm_calc_t* calc, const char* expression, artm_cbk_t callback) {
  artm_result_t result = artm_calc_eval(calc, expression);
  if (result.status == ARTM_SUCCESS)
    return result.as.value;

  callback.target(&result, callback.payload);
  return 0;
}

static artm_result_t parse_decl(artm_calc_t* calc) {
  ARTM_ADVANCE(calc);

  token_t id = calc->token;

  ARTM_CONSUME(calc, TKN_ID, ARTM_INV_TOKEN);
  ARTM_CONSUME(calc, TKN_EQUAL, ARTM_INV_TOKEN);

  artm_result_t result = parse_expr(calc);
  ARTM_CHECK_RESULT(result);

  char* name = strndup(id.target, id.size);
  if (name == NULL) {
    return ARTM_ERROR(ARTM_ALLOC_ERR, id);
  }

  table_put(&calc->decls, name, TABLE_DBL_VALUE(result.as.value));
  free(name);
  return result;
}

static artm_result_t parse_expr(artm_calc_t* calc) {
  artm_result_t result = parse_term(calc);
  ARTM_CHECK_RESULT(result);

  while (match(calc, TKN_PLUS, TKN_MINUS)) {
    token_t token = calc->token;
    ARTM_ADVANCE(calc);

    artm_result_t next = parse_term(calc);
    ARTM_CHECK_RESULT(next);

    result = token.type == TKN_PLUS
      ? ARTM_VALUE(result.as.value + next.as.value)
      : ARTM_VALUE(result.as.value - next.as.value);
  }

  ARTM_CHECK_TOKEN(calc);
  return result;
}

static artm_result_t parse_term(artm_calc_t* calc) {
  artm_result_t result = parse_factor(calc);
  ARTM_CHECK_RESULT(result);

  while (match(calc, TKN_STAR, TKN_SLASH)) {
    token_t token = calc->token;
    ARTM_ADVANCE(calc);

    artm_result_t next = parse_factor(calc);
    ARTM_CHECK_RESULT(next);

    result = token.type == TKN_STAR
      ? ARTM_VALUE(result.as.value * next.as.value)
      : ARTM_VALUE(result.as.value / next.as.value);
  }

  ARTM_CHECK_TOKEN(calc);
  return result;
}

static artm_result_t parse_factor(artm_calc_t* calc) {
  token_t token = calc->token;
  switch (token.type) {
    case TKN_NUMBER:
      ARTM_ADVANCE(calc);
      return ARTM_VALUE(strtod(token.target, NULL));
    case TKN_MINUS: {
      ARTM_ADVANCE(calc);
      artm_result_t result = parse_factor(calc);
      ARTM_CHECK_RESULT(result);
      return ARTM_VALUE(-result.as.value);
    }
    case TKN_PLUS: {
      ARTM_ADVANCE(calc);
      artm_result_t result = parse_factor(calc);
      ARTM_CHECK_RESULT(result);
      return result;
    }
    case TKN_ID:
      return parse_call(calc);
    case TKN_LPAREN:
      return parse_paren(calc);
    default:
      return ARTM_ERROR(ARTM_INV_TOKEN, token);
  }
}

static artm_result_t parse_paren(artm_calc_t* calc) {
  ARTM_ADVANCE(calc);
  artm_result_t result = parse_expr(calc);
  ARTM_CHECK_RESULT(result);
  ARTM_CONSUME(calc, TKN_RPAREN, ARTM_INV_TOKEN);
  return result;
}

static artm_result_t parse_call(artm_calc_t* calc) {
  token_t id = calc->token;
  ARTM_ADVANCE(calc);

  char* name = strndup(id.target, id.size);
  table_value_t value = table_get(&calc->decls, name);
  free(name);

  if (value.type == TAB_VAL_PTR) {
    return ARTM_ERROR(ARTM_UNDEF_VAR, id);
  }

  return ARTM_VALUE(value.as.dbl);
}
