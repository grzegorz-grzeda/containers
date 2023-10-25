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
#include "static-queue.h"
#include <stdlib.h>
#include <string.h>

typedef struct static_queue {
    void* data;
    void* head;
    void* tail;
    size_t data_size;
    size_t element_size;
    bool is_full;
    bool is_empty;
} static_queue_t;

static_queue_t* static_queue_create(size_t element_count, size_t element_size) {
    if (!element_count || !element_size) {
        return NULL;
    }
    static_queue_t* queue = calloc(1, sizeof(static_queue_t));
    if (!queue) {
        return NULL;
    }
    queue->data = calloc(element_count, element_size);
    if (!queue->data) {
        free(queue);
        return NULL;
    }
    queue->head = queue->data;
    queue->tail = queue->data;
    queue->element_size = element_count;
    queue->data_size = element_size * element_count;
    queue->is_empty = true;
    return queue;
}

void static_queue_destroy(static_queue_t* queue) {
    if (!queue) {
        return;
    }
    free(queue->data);
    free(queue);
}

bool static_queue_enqueue(static_queue_t* queue, const void* data) {
    if (!queue || !data || queue->is_full) {
        return false;
    }
    memcpy(queue->tail, data, queue->element_size);
    queue->tail += queue->element_size;
    if (queue->tail >= (queue->data + queue->data_size)) {
        queue->tail = queue->data;
    }
    queue->is_full = (queue->head == queue->tail);
    return true;
}

bool static_queue_dequeue(static_queue_t* queue, void* data) {
    if (!queue || !data || queue->is_empty) {
        return false;
    }
    memcpy(data, queue->head, queue->element_size);
    queue->head += queue->element_size;
    if (queue->head >= (queue->data + queue->data_size)) {
        queue->head = queue->data;
    }
    queue->is_empty = (queue->head == queue->tail);
    return true;
}
