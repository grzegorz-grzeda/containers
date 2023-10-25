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
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cmocka.h"

#include "dynamic-queue.h"

static void test_create_dynamic_queue(void** state) {
    dynamic_queue_t* queue = dynamic_queue_create();
    assert_ptr_not_equal(queue, NULL);
    dynamic_queue_destroy(queue);
}

static void test_try_to_use_invalid_queue_pointer(void** state) {
    dynamic_queue_t* queue = NULL;
    int input = rand();

    dynamic_queue_enqueue(queue, &input);
    void* ptr = dynamic_queue_dequeue(queue);
    assert_ptr_equal(ptr, NULL);
}

static void test_try_to_dequeue_an_empty_queue(void** state) {
    dynamic_queue_t* queue = (dynamic_queue_t*)(*state);
    void* ptr = dynamic_queue_dequeue(queue);
    assert_ptr_equal(ptr, NULL);
}

static void test_pass_one_element_through_queue(void** state) {
    dynamic_queue_t* queue = (dynamic_queue_t*)(*state);
    int input = rand();
    int output = 0 - input;

    dynamic_queue_enqueue(queue, &input);
    output = *(int*)(dynamic_queue_dequeue(queue));
    assert_int_equal(input, output);

    void* ptr = dynamic_queue_dequeue(queue);
    assert_ptr_equal(ptr, NULL);
}

static void test_pass_couple_elements_through_queue(void** state) {
    dynamic_queue_t* queue = (dynamic_queue_t*)(*state);
    int input = rand();
    int output = 0 - input;
    dynamic_queue_enqueue(queue, &input);
    output = *(int*)(dynamic_queue_dequeue(queue));
    assert_int_equal(input, output);

    input = rand();
    output = 0 - input;
    dynamic_queue_enqueue(queue, &input);
    output = *(int*)(dynamic_queue_dequeue(queue));
    assert_int_equal(input, output);

    void* ptr = dynamic_queue_dequeue(queue);
    assert_ptr_equal(ptr, NULL);

    input = rand();
    output = 0 - input;
    dynamic_queue_enqueue(queue, &input);
    output = *(int*)(dynamic_queue_dequeue(queue));
    assert_int_equal(input, output);

    ptr = dynamic_queue_dequeue(queue);
    assert_ptr_equal(ptr, NULL);
}

static void test_pass_couple_of_elements_in_series(void** state) {
    dynamic_queue_t* queue = (dynamic_queue_t*)(*state);
    int input[10];
    int output[10];
    size_t input_counter = 0;
    size_t output_counter = 0;

    for (size_t i = 0; i < sizeof(input) / sizeof(input[0]); i++) {
        input[i] = rand();
    }
    memset(output, rand(), sizeof(output) / sizeof(output[0]));

    dynamic_queue_enqueue(queue, input + (input_counter++));
    dynamic_queue_enqueue(queue, input + (input_counter++));
    dynamic_queue_enqueue(queue, input + (input_counter++));
    dynamic_queue_enqueue(queue, input + (input_counter++));
    output[output_counter++] = *(int*)(dynamic_queue_dequeue(queue));
    assert_int_equal(input[0], output[0]);

    dynamic_queue_enqueue(queue, input + (input_counter++));
    dynamic_queue_enqueue(queue, input + (input_counter++));
    for (size_t i = 0; i < 5; i++) {
        output[output_counter++] = *(int*)(dynamic_queue_dequeue(queue));
    }
    assert_int_equal(input[1], output[1]);
    assert_int_equal(input[2], output[2]);
    assert_int_equal(input[3], output[3]);
    assert_int_equal(input[4], output[4]);
    assert_int_equal(input[5], output[5]);

    size_t input_elements_left_count =
        ((sizeof(input) / sizeof(input[0])) - input_counter);
    for (size_t i = 0; i < input_elements_left_count; i++) {
        dynamic_queue_enqueue(queue, input + (input_counter++));
    }
    size_t output_elements_left_count =
        ((sizeof(input) / sizeof(input[0])) - output_counter);
    for (size_t i = 0; i < output_elements_left_count; i++) {
        output[output_counter++] = *(int*)(dynamic_queue_dequeue(queue));
    }
    assert_memory_equal(input, output, sizeof(input) / sizeof(input[0]));

    void* ptr = dynamic_queue_dequeue(queue);
    assert_ptr_equal(ptr, NULL);
}

static int test_suite_setup(void** state) {
    srand(time(NULL));
    return 0;
}

static int test_setup(void** state) {
    *state = dynamic_queue_create();
    assert_ptr_not_equal(*state, NULL);
    return 0;
}

static int test_teardown(void** state) {
    dynamic_queue_destroy(*state);
    return 0;
}

int main(int argc, char** argv) {
    srand(time(NULL));
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_create_dynamic_queue),
        cmocka_unit_test(test_try_to_use_invalid_queue_pointer),
        cmocka_unit_test_setup_teardown(test_try_to_dequeue_an_empty_queue,
                                        test_setup, test_teardown),
        cmocka_unit_test_setup_teardown(test_pass_one_element_through_queue,
                                        test_setup, test_teardown),
        cmocka_unit_test_setup_teardown(test_pass_couple_elements_through_queue,
                                        test_setup, test_teardown),
        cmocka_unit_test_setup_teardown(test_pass_couple_of_elements_in_series,
                                        test_setup, test_teardown),
    };

    return cmocka_run_group_tests(tests, test_suite_setup, NULL);
}