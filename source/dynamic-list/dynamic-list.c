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
#include "dynamic-list.h"
#include <stddef.h>
#include <stdlib.h>

typedef struct dynamic_list_iterator {
    struct dynamic_list_iterator* next;
    void* data;
} dynamic_list_iterator_t;

typedef struct dynamic_list {
    dynamic_list_iterator_t* head;
    dynamic_list_iterator_t* tail;
} dynamic_list_t;

dynamic_list_t* dynamic_list_create(void) {
    return calloc(1, sizeof(dynamic_list_t));
}

void dynamic_list_destroy(dynamic_list_t* list) {
    if (!list) {
        return;
    }
    free(list);
}

void dynamic_list_append(dynamic_list_t* list, void* data) {
    if (!list || !data) {
        return;
    }
    dynamic_list_iterator_t* node = calloc(1, sizeof(dynamic_list_iterator_t));
    if (!node) {
        return;
    }
    node->data = data;
    if (list->tail) {
        list->tail->next = node;
    } else {
        list->head = node;
    }
    list->tail = node;
}

dynamic_list_iterator_t* dynamic_list_begin(dynamic_list_t* list) {
    if (!list) {
        return NULL;
    }
    return list->head;
}

dynamic_list_iterator_t* dynamic_list_next(dynamic_list_iterator_t* iterator) {
    if (!iterator) {
        return NULL;
    }
    return iterator->next;
}

void* dynamic_list_get(dynamic_list_iterator_t* iterator) {
    if (!iterator) {
        return NULL;
    }
    return iterator->data;
}
