/* Lexer - Math expression lexical analyzer
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

#include <string.h>
#include <stdbool.h>

#include "lexer.h"

static void skip_spaces(lexer_t* lexer);

static token_t lang_token(lexer_t* lexer);
static token_t id_token(lexer_t* lexer);
static token_t number_token(lexer_t* lexer);
static token_t base_token(lexer_t* lexer);

static inline bool at_end(const lexer_t* lexer) {
  return *lexer->current == '\0';
}

static inline bool is_space(const lexer_t* lexer) {
  return *lexer->current == ' ';
}

static inline bool is_digit(const lexer_t* lexer) {
  return *lexer->current >= '0' && *lexer->current <= '9';
}

static inline bool is_alpha(const lexer_t* lexer) {
  return *lexer->current == '_'
    || (*lexer->current >= 'a' && *lexer->current <= 'z')
    || (*lexer->current >= 'A' && *lexer->current <= 'Z');
}

static inline bool is_alphanum(const lexer_t* lexer) {
  return is_digit(lexer) || is_alpha(lexer);
}

static inline token_t make_token(lexer_t* lexer, token_type_t type) {
  return (token_t) { type, lexer->start, lexer->current - lexer->start };
}

extern void lexer_init(lexer_t* lexer, const char* expression) {
  lexer->current = lexer->start = expression;
}

extern token_t lexer_next(lexer_t* lexer) {
  while (!at_end(lexer)) {
    if (is_space(lexer)) {
      skip_spaces(lexer);
      continue;
    }
    return lang_token(lexer);
  }

  lexer->start = lexer->current;
  return make_token(lexer, TKN_END);
}

static token_t lang_token(lexer_t* lexer) {
  lexer->start = lexer->current;
  if (is_alpha(lexer))
    return id_token(lexer);
  if (is_digit(lexer))
    return number_token(lexer);
  return base_token(lexer);
}

static token_t number_token(lexer_t* lexer) {
  while (!at_end(lexer) && is_digit(lexer))
    ++lexer->current;

  if (*lexer->current == '.') {
    ++lexer->current;
    while (!at_end(lexer) && is_digit(lexer))
      ++lexer->current;
  }
  return make_token(lexer, TKN_NUMBER);
}

static token_t id_token(lexer_t* lexer) {
  while (!at_end(lexer) && is_alphanum(lexer))
    ++lexer->current;
  return make_token(lexer, TKN_ID);
}

static token_t base_token(lexer_t* lexer) {
  char current = *lexer->current;
  ++lexer->current;
  switch (current) {
    case '+': return make_token(lexer, TKN_PLUS);
    case '-': return make_token(lexer, TKN_MINUS);
    case '*': return make_token(lexer, TKN_STAR);
    case '/': return make_token(lexer, TKN_SLASH);
    case '(': return make_token(lexer, TKN_LPAREN);
    case ')': return make_token(lexer, TKN_RPAREN);
    case '$': return make_token(lexer, TKN_DOLLAR);
    case '=': return make_token(lexer, TKN_EQUAL);
    default: return make_token(lexer, TKN_ERROR);
  }
}

static void skip_spaces(lexer_t* lexer) {
  while (!at_end(lexer) && is_space(lexer))
    ++lexer->current;
}
