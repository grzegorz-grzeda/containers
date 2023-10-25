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
#ifndef CONTAINERS_DYNAMIC_QUEUE_H
#define CONTAINERS_DYNAMIC_QUEUE_H

/**
 * @defgroup dynamic-queue Dynamic Queue
 *
 * @brief Dynamically allocated queue
 * @{
 */

typedef struct dynamic_queue
    dynamic_queue_t; /**< @brief Dynamic queue absctract type. Use only as
                        pointer */

/**
 * @brief Create a new dynamic queue
 * @note Uses memory allocation
 * @return pointer to a new dynamic queue
 */
dynamic_queue_t* dynamic_queue_create(void);

/**
 * @brief Destroy a the dynamic queue
 * @param[in] queue pointer to the dynamic queue to destroy
 * @note Uses memory de-allocation
 * @note Make sure to destroy the referenced data!
 */
void dynamic_queue_destroy(dynamic_queue_t* queue);

/**
 * @brief Appends the element to the front of the dynamic queue
 * @param[in] queue pointer to the dynamic queue
 * @param[in] data pointer to the new data to be placed
 * @note the data pointer has to be a valid memory location
 */
void dynamic_queue_enqueue(dynamic_queue_t* queue, void* data);

/**
 * @brief Retrieve value from current position
 * @param[in] queue pointer to the dynamic queue
 * @return NULL if the pointer to the queue is invalid
 * @return NULL if the queue is empty
 * @return pointer to data content
 */
void* dynamic_queue_dequeue(dynamic_queue_t* queue);

/**
 * @}
 */

#endif  // CONTAINERS_DYNAMIC_QUEUE_H