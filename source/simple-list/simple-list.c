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
#include "simple-list.h"
#include <stdlib.h>

typedef struct simple_list_iterator {
    struct simple_list_iterator *next;
    void *value;
} simple_list_iterator_t;

typedef struct simple_list {
    simple_list_iterator_t *first;
    simple_list_iterator_t *last;
} simple_list_t;


simple_list_t *create_simple_list(void)
{
    return calloc(1, sizeof(simple_list_t));
}

static simple_list_iterator_t *create_new_iterator(void *element)
{
    simple_list_iterator_t *it = calloc(1, sizeof(simple_list_iterator_t));
    if (it) {
        it->value = element;
    }
    return it;
}

static void insert_first_iterator(simple_list_t *list, simple_list_iterator_t *it)
{
    list->first = it;
    list->last = it;
}

static void append_iterator(simple_list_t *list, simple_list_iterator_t *it)
{
    list->last->next = it;
    list->last = it;
}

void append_to_simple_list(simple_list_t *list, void *element)
{
    if (!list) {
        return;
    }
    simple_list_iterator_t *it = create_new_iterator(element);
    if (!it) {
        return;
    }
    if (list->first) {
        append_iterator(list, it);
    } else {
        insert_first_iterator(list, it);
    }
}

static void insert_sorted_second_to_last_into_list(simple_list_t *list, simple_list_iterator_t *it,
                                                   simple_list_element_comparator_t comparator)
{
    simple_list_iterator_t *cursor = list->first;
    while (cursor->next) {
        if (comparator(cursor->next->value, it->value) > 0) {
            it->next = cursor->next;
            cursor->next = it;
            return;
        } else {
            cursor = cursor->next;
        }
    }
    append_iterator(list, it);
}

void insert_sorted_to_simple_list(simple_list_t *list, void *element, simple_list_element_comparator_t comparator)
{
    if (!list || !comparator) {
        return;
    }
    simple_list_iterator_t *it = create_new_iterator(element);
    if (!it) {
        return;
    }
    if (!list->first) {
        insert_first_iterator(list, it);
        return;
    }
    if (comparator(list->first->value, element) > 0) {
        it->next = list->first;
        list->first = it;
        return;
    }
    insert_sorted_second_to_last_into_list(list, it, comparator);
}

simple_list_iterator_t *simple_list_begin(simple_list_t *list)
{
    if (!list) {
        return NULL;
    }
    return list->first;
}


simple_list_iterator_t *simple_list_begin_filtered(simple_list_t *list, const void *reference_element,
                                                   simple_list_element_comparator_t comparator)
{
    if (!list || !comparator) {
        return NULL;
    }
    simple_list_iterator_t *iterator = NULL;
    for (iterator = simple_list_begin(list); iterator; iterator = simple_list_next(iterator)) {
        if (comparator(iterator->value, reference_element) == 0) {
            break;
        }
    }
    return iterator;
}

simple_list_iterator_t *simple_list_next(simple_list_iterator_t *iterator)
{
    if (!iterator) {
        return NULL;
    }
    return iterator->next;
}

simple_list_iterator_t *simple_list_next_filtered(simple_list_iterator_t *iterator, const void *reference_element,
                                                  simple_list_element_comparator_t comparator)
{
    if (!comparator) {
        return NULL;
    }
    for (iterator = simple_list_next(iterator); iterator; iterator = simple_list_next(iterator)) {
        if (comparator(iterator->value, reference_element) == 0) {
            break;
        }
    }
    return iterator;
}

void *get_from_simple_list_iterator(simple_list_iterator_t *iterator)
{
    if (!iterator) {
        return NULL;
    }
    return iterator->value;
}