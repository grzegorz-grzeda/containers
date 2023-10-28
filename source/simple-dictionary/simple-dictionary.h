/*
 * MIT License
 *
 * Copyright (c) 2023 Grzegorz Grzęda
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef CONTAINERS_SIMPLE_DICTIONARY_H
#define CONTAINERS_SIMPLE_DICTIONARY_H

#include <stdbool.h>
#include "simple-list.h"

/**
 * @defgroup simple-dictionary Simple dictionary
 *
 * @brief Implementation of a dynamic dictionary structure
 * @{
 */

typedef struct simple_dictionary simple_dictionary_t; /**< @brief Simple dictionary type. Use only as pointer */

/**
 * @brief Key comparator function type
 *
 * Used for comparing two key while searching in dictionary.
 * The comparator basically should perform a (*key_0 - *key_1) comparison.
 * @param[in] key_0 pointer to one key
 * @param[in] key_1 pointer to another key
 * @return true if two keys are equal
 * @return false if two keys differ
 */
typedef bool (*simple_dictionary_key_comparator_t)(const void* key_0, const void* key_1);

/**
 * @brief Create a new dictionary
 * @note Uses memory allocation
 * @param[in] comparator pointer to key comparator function
 * @return pointer to a new simple dictionary
 */
simple_dictionary_t* create_simple_dictionary(simple_dictionary_key_comparator_t comparator);

/**
 * @brief Inserts a value for specified key into the dictionary
 * @note The `key` and `value` must be created outside. New value is stored even if actual pointers
 * to `key` and/or `value` already exist.
 * @param[in] dictionary pointer to the simple dictionary
 * @param[in] key pointer to the key to store the value under
 * @param[in] value pointer to the new value
 */
void insert_to_simple_dictionary(simple_dictionary_t* dictionary, const void* key, void* value);

/**
 * @brief Get value of key in the dictionary
 * @param[in] dictionary pointer to the simple dictionary
 * @param[in] key pointer to the key to get the value from
 * @return NULL if dictionary invalid or does not contain the given key
 * @return pointer to first value in dictionary under key if not empty
 */
void* get_first_from_simple_dictionary(simple_dictionary_t* dictionary, const void* key);

/**
 * @brief Get all values of key in the dictionary
 * @param[in] dictionary pointer to the simple dictionary
 * @param[in] key pointer to the key to get the values from
 * @return NULL if dictionary invalid or does not contain the given key
 * @return pointer to simple list iterator structure with all values in dictionary under key if not empty
 */
simple_list_iterator_t* get_all_from_simple_dictionary(simple_dictionary_t* dictionary, const void* key);

/**
 * @}
 */

#endif  // CONTAINERS_SIMPLE_DICTIONARY_H