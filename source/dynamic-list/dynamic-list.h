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
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef CONTAINERS_DYNAMIC_LIST_H
#define CONTAINERS_DYNAMIC_LIST_H

/**
 * @defgroup dynamic-list Dynamic Queue
 *
 * @brief Dynamically allocated list
 * @{
 */

typedef struct dynamic_list dynamic_list_t; /**< @brief Dynamic list absctract
                                               type. Use only as pointer */

typedef struct dynamic_list_iterator dynamic_list_iterator_t; /**< @brief Dynamic list iterator abstract type.
                                                                 Use only as pointer */

/**
 * @brief Create a new dynamic list
 * @note Uses memory allocation
 * @return pointer to a new dynamic list
 */
dynamic_list_t* dynamic_list_create(void);

/**
 * @brief Destroy a the dynamic list
 * @param[in] list pointer to the dynamic list to destroy
 * @note Uses memory de-allocation
 * @note Make sure to destroy the referenced data!
 */
void dynamic_list_destroy(dynamic_list_t* list);

/**
 * @brief Append to dynamic list
 * @param[in] list pointer to the dynamic list
 * @param[in] data pointer to data to append
 * @note The data pointer has to be valid
 */
void dynamic_list_append(dynamic_list_t* list, void* data);

/**
 * @brief Get the beginning iterator of the dynamic list
 * @param[in] list pointer to dynamic list
 * @return NULL if list pointer invalid or list empty
 * @return pointer to the dynamic list beginning otherwise
 */
dynamic_list_iterator_t* dynamic_list_begin(dynamic_list_t* list);

/**
 * @brief Get next position in dynamic list
 * @param[in] iterator pointer to current position in dynamic list
 * @return NULL if pointer invalid or next position is empty
 * @return pointer to next position otherwise
 */
dynamic_list_iterator_t* dynamic_list_next(dynamic_list_iterator_t* iterator);

/**
 * @brief Get the value of current position
 * @param[in] iterator pointer to current position in dynamic list
 * @return NULL if pointer is invalid or position is empty
 * @return pointer to value of current position otherwise
 */
void* dynamic_list_get(dynamic_list_iterator_t* iterator);

/**
 * @}
 */

#endif  // CONTAINERS_DYNAMIC_LIST_H