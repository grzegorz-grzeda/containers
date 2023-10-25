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
#ifndef CONTAINERS_STATIC_QUEUE_H
#define CONTAINERS_STATIC_QUEUE_H

#include <stdbool.h>
#include <stddef.h>

/**
 * @defgroup static-queue Static Queue
 *
 * @brief Statically allocated queue
 * @{
 */

typedef struct static_queue static_queue_t; /**< @brief Static queue absctract
                                               type. Use only as pointer */

/**
 * @brief Create a new static queue
 * @param[in] element_count Maximum number of elements stored
 * @param[in] element_size Size of a single element
 * @note Uses memory allocation
 * @return pointer to a new static queue
 */
static_queue_t* static_queue_create(size_t element_count, size_t element_size);

/**
 * @brief Destroy a the static queue
 * @param[in] queue pointer to the static queue to destroy
 * @note Uses memory de-allocation
 */
void static_queue_destroy(static_queue_t* queue);

/**
 * @brief Appends the element to the front of the static queue
 * @param[in] queue pointer to the static queue
 * @param[in] data pointer to the new data to be placed
 * @return true if data is stored successfully
 * @return false if pointers are invalid or queue is full
 * @note The data pointer has to be a valid memory location.
 * @note Enqueueing is a shallow copy operation!
 */
bool static_queue_enqueue(static_queue_t* queue, const void* data);

/**
 * @brief Retrieve value from current position
 * @param[in] queue pointer to the static queue
 * @param[out] data pointer to the destination data receiver
 * @return false if the pointers are invalid
 * @return false if the queue is empty
 * @return true if data dequeued
 * @note The data pointer has to be a valid memory location.
 * @note Dequeueing is a shallow copy operation!
 */
bool static_queue_dequeue(static_queue_t* queue, void* data);

/**
 * @}
 */

#endif  // CONTAINERS_STATIC_QUEUE_H