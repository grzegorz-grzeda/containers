/**
 * MIT License
 * Copyright (c) 2023 Grzegorz Grzęda
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

typedef struct simple_list simple_list_t;

typedef struct simple_list_iterator simple_list_iterator_t;

simple_list_t *create_simple_list(void);

void append_to_simple_list(simple_list_t *list, void *element);

simple_list_iterator_t *simple_list_begin(simple_list_t *list);

simple_list_iterator_t *simple_list_next(simple_list_iterator_t*iterator);

void *get_from_simple_list_iterator(simple_list_iterator_t*iterator);

#endif // CONTAINERS_SIMPLE_LIST_H