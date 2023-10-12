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
#ifndef CONTAINERS_SIMPLE_LIST_H
#define CONTAINERS_SIMPLE_LIST_H

#include <stddef.h>

/**
 * @defgroup simple-list Simple list
 * 
 * @brief Implementation of a uni-directional dynamic list structure
 * @{
*/

typedef struct simple_list simple_list_t; /**< @brief Simple list type. Use only as pointer */

typedef struct simple_list_iterator
    simple_list_iterator_t; /**< @brief Simple list iterator type. Use only as pointer */

/**
 * @brief Comparator function type
 * 
 * Used for comparing two elements. The first is the currently held in list, the second is the new element in
 * question. The comparator basically should perform a (*current_element - *new_element) comparison.
 * @param[in] current_element pointer to element already in list
 * @param[in] new_element pointer to new element in question
 * @return < 0 if current_element is lower/smaller than new_element
 * @return = 0 if current_element is equal to new_element
 * @return > 0 if current_element is higher/bigger than new_element
*/
typedef int (*simple_list_element_comparator_t)(const void *current_element, const void *new_element);

/** 
 * @brief Create a new list
 * @note Uses memory allocation
 * @return pointer to a new simple list
*/
simple_list_t *create_simple_list(void);

/**
 * @brief Appends the element to the end of list
 * @param[in] list pointer to the simple list
 * @param[in] element pointer to the new element to be appended
*/
void append_to_simple_list(simple_list_t *list, void *element);

/**
 * @brief Inserts the element in a sorted fashion
 * 
 * The list will insert the element based on the comparator's output. It will place the new element right after
 * the current 'lower/smaller' element.
 * @param[in] list pointer to the simple list
 * @param[in] element pointer to the new element to be inserted
 * @param[in] comparator pointer to comparator function
*/
void insert_sorted_to_simple_list(simple_list_t *list, void *element, simple_list_element_comparator_t comparator);

/**
 * @brief Get beginning of the list
 * @param[in] list pointer to the simple list
 * @return NULL if list is empty
 * @return pointer to first iterator in list if not empty
*/
simple_list_iterator_t *simple_list_begin(simple_list_t *list);

/**
 * @brief Get beginning of the list
 * @param[in] list pointer to the simple list
 * @param[in] reference_element pointer to reference element for comparison
 * @param[in] comparator pointer to comparator function
 * @return NULL if no filtered position was found or pointers were invalid
 * @return pointer to first 'reference element equal' position
*/
simple_list_iterator_t *simple_list_begin_filtered(simple_list_t *list, const void *reference_element,
                                                   simple_list_element_comparator_t comparator);

/**
 * @brief Get next position in the list
 * @param[in] iterator pointer current position
 * @return NULL if this was the last position
 * @return pointer to next iterator in list if otherwise
*/
simple_list_iterator_t *simple_list_next(simple_list_iterator_t *iterator);

/**
 * @brief Get next filtered position in the list
 * @param[in] iterator pointer current position
 * @param[in] reference_element pointer to reference element for comparison
 * @param[in] comparator pointer to comparator function
 * @return NULL if no filtered position was found or pointers were invalid
 * @return pointer to first 'reference element equal' position
*/
simple_list_iterator_t *simple_list_next_filtered(simple_list_iterator_t *iterator, const void *reference_element,
                                                  simple_list_element_comparator_t comparator);

/**
 * @brief Retrieve value from current position
 * @param[in] iterator pointer current position
 * @return NULL if position was invalid
 * @return pointer to element content for given valid position
*/
void *get_from_simple_list_iterator(simple_list_iterator_t *iterator);

/**
 * @}
*/

#endif // CONTAINERS_SIMPLE_LIST_H