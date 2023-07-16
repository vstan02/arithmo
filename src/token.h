/* Token - Math expression tokens
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

#ifndef ARITHMO_TOKEN_H
#define ARITHMO_TOKEN_H

#include "stddef.h"

typedef struct token token_t;

typedef enum {
	TKN_ERROR,
  TKN_DOLLAR,
	TKN_PLUS,
	TKN_MINUS,
	TKN_STAR,
	TKN_SLASH,
	TKN_LPAREN,
	TKN_RPAREN,
	TKN_EQUAL,
	TKN_NUMBER,
	TKN_ID,
	TKN_END
} token_type_t;

struct token {
  token_type_t type;
  const char* target;
  size_t size;
};

#endif // ARITHMO_TOKEN_H
