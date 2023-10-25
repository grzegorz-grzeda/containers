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
#include "dynamic-queue.h"
#include <stddef.h>
#include <stdlib.h>

typedef struct dynamic_queue_node {
    struct dynamic_queue_node* next;
    void* data;
} dynamic_queue_node_t;

typedef struct dynamic_queue {
    dynamic_queue_node_t* head;
    dynamic_queue_node_t* tail;
} dynamic_queue_t;

dynamic_queue_t* dynamic_queue_create(void) {
    return calloc(1, sizeof(dynamic_queue_t));
}

void dynamic_queue_destroy(dynamic_queue_t* queue) {
    if (!queue) {
        return;
    }
    while (dynamic_queue_dequeue(queue))
        ;
    free(queue);
}

void dynamic_queue_enqueue(dynamic_queue_t* queue, void* data) {
    if (!queue || !data) {
        return;
    }
    dynamic_queue_node_t* node = calloc(1, sizeof(dynamic_queue_node_t));
    node->data = data;
    if (!queue->head) {
        queue->head = node;
    } else {
        queue->tail->next = node;
    }
    queue->tail = node;
}

void* dynamic_queue_dequeue(dynamic_queue_t* queue) {
    if (!queue || !queue->head) {
        return NULL;
    }
    void* data = queue->head->data;
    dynamic_queue_node_t* next = queue->head->next;
    free(queue->head);
    queue->head = next;
    if (!queue->head) {
        queue->tail = NULL;
    }
    return data;
}
