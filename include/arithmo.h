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

#ifndef ARITHMO_H
#define ARITHMO_H

#include <stddef.h>

#define ARTM_CBK(_target_, _payload_) \
  ((artm_cbk_t) { .target = (_target_), .payload = (_payload_) })

typedef struct artm_calc artm_calc_t;
typedef struct artm_result artm_result_t;
typedef struct artm_token artm_token_t;
typedef struct artm_cbk artm_cbk_t;

typedef enum {
  ARTM_SUCCESS,
  ARTM_NULL_CALC,
  ARTM_NULL_EXPR,
  ARTM_INV_TOKEN,
  ARTM_ALLOC_ERR,
  ARTM_UNDEF_VAR
} artm_status_t;

struct artm_token {
  size_t size;
  const char* target;
};

struct artm_result {
  artm_status_t status;
  union {
    double value;
    artm_token_t token;
  } as;
};

struct artm_cbk {
  void (*target)(const artm_result_t*, void*);
  void* payload;
};

/**
 * @brief Initializes an Arithmo Interpreter object
 * @param decl_table_size The approximate number of variables that will be used
 * @return The Arithmo Interpreter object
 */
extern artm_calc_t* artm_calc_init(size_t decl_table_size);

/**
 * @brief Deallocates the memory previously allocated by a call to artm_calc_init
 * @param calc An Arithmo Interpreter object
 * @return Void
 */
extern void artm_calc_free(artm_calc_t* calc);

/**
 * @brief Evaluates the given mathematical expression
 * @param calc An Arithmo Interpreter object
 * @param expression The mathematical expression
 * @return The evaluation result structure
 */
extern artm_result_t artm_calc_eval(artm_calc_t* calc, const char* expression);

/**
 * @brief Evaluates the given mathematical expression
 * @param calc An Arithmo Interpreter object
 * @param expression The mathematical expression
 * @param cbk The callback that is called in case of an error
 * @return The evaluation result value
 */
extern double artm_calc_cbk_eval(artm_calc_t* calc, const char* expression, artm_cbk_t cbk);

#endif // ARITHMO_H
