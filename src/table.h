/* Table - A simple hash table implementation
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

#ifndef ARITHMO_TABLE_H
#define ARITHMO_TABLE_H

#include <stddef.h>

#define TABLE_DBL_VALUE(_value_) \
  ((table_value_t) { .type = TAB_VAL_DBL, .as = { .dbl = (_value_) }})

#define TABLE_PTR_VALUE(_value_) \
  ((table_value_t) { .type = TAB_VAL_PTR, .as = { .ptr = (_value_) }})

typedef struct table table_t;
typedef struct table_value table_value_t;
typedef struct table_item table_item_t;
typedef void (*table_each_t)(const char*, const table_value_t*);

typedef enum {
  TAB_VAL_DBL,
  TAB_VAL_PTR
} table_value_type_t;

struct table {
  size_t size;
  struct table_item** items;
};

struct table_value {
  table_value_type_t type;
  struct {
    void* ptr;
    double dbl;
  } as;
};

extern void table_init(table_t* table, size_t size);
extern void table_free(table_t* table);

extern void table_each(const table_t* table, table_each_t func);

extern table_value_t table_get(const table_t* table, const char* key);
extern void table_put(table_t* table, const char* key, table_value_t value);

#endif // ARITHMO_TABLE_H
