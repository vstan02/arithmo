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

#ifndef ARITHMO_LEXER_H
#define ARITHMO_LEXER_H

#include <stddef.h>

#include "token.h"

typedef struct lexer lexer_t;

struct lexer {
  const char* current;
  const char* start;
};

extern void lexer_init(lexer_t* lexer, const char* expression);
extern token_t lexer_next(lexer_t* lexer);

#endif // ARITHMO_LEXER_H
