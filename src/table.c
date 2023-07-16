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

#include <malloc.h>
#include <string.h>

#include "table.h"

struct table_item {
  char* key;
  table_value_t data;
  table_item_t* next;
};

static size_t hash(const char* str, size_t size);

extern void table_init(table_t* table, size_t size) {
  table->size = size;
  table->items = (table_item_t**) malloc(size * sizeof(table_item_t*));
  for (size_t i = 0; i < size; ++i)
    table->items[i] = NULL;
}

extern void table_free(table_t* table) {
  for (size_t i = 0; i < table->size; ++i) {
    table_item_t* current = table->items[i];
    while (current != NULL) {
      table_item_t* next = current->next;
      free(current->key);
      free(current);
      current = next;
    }
  }
  free(table->items);
}

extern table_value_t table_get(const table_t* table, const char* key) {
  size_t index = hash(key, table->size);
  table_item_t* current = table->items[index];
  while (current != NULL) {
    if (strcmp(current->key, key) == 0)
      return current->data;
    current = current->next;
  }
  return TABLE_PTR_VALUE(NULL);
}

extern void table_put(table_t* table, const char* key, table_value_t value) {
  size_t index = hash(key, table->size);

  table_item_t* node = (table_item_t*) malloc(sizeof(table_item_t));
  if (node == NULL) return;

  node->key = strdup(key);
  if (node->key == NULL) {
    free(node);
    return;
  }

  node->data = value;
  node->next = table->items[index];
  table->items[index] = node;
}

extern void table_each(const table_t* table, table_each_t callback) {
  for (size_t i = 0; i < table->size; ++i) {
    table_item_t* current = table->items[i];
    while (current != NULL) {
      callback(current->key, &current->data);
      current = current->next;
    }
  }
}

static size_t hash(const char* str, size_t size) {
  size_t result = 0;
  while (*str != '\0')
    result += (size_t) *(str++);
  return result % size;
}
