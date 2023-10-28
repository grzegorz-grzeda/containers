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

#include "simple-list.h"

#define MINIMAL_TEST_SAMPLE_SIZE (10)
#define MAXIMAL_TEST_SAMPLE_SIZE (10000)

static int* test_sample = NULL;
static size_t test_sample_size = 0;

static void simple_test(void** state) {
    simple_list_t* list = create_simple_list();
    assert_ptr_not_equal(list, NULL);

    for (size_t i = 0; i < test_sample_size; i++) {
        append_to_simple_list(list, test_sample + i);
    }
    size_t counter = 0;
    for (simple_list_iterator_t* it = simple_list_begin(list); it; it = simple_list_next(it)) {
        assert_int_equal(*(int*)get_from_simple_list_iterator(it), test_sample[counter++]);
    }
}

static int element_comparator(const void* current, const void* new_one) {
    int current_int = *(int*)current;
    int new_int = *(int*)new_one;
    return (current_int - new_int);
}

static void sort_on_insert_test(void** state) {
    simple_list_t* list = create_simple_list();
    assert_ptr_not_equal(list, NULL);

    int* sorted = calloc(test_sample_size, sizeof(test_sample[0]));
    memcpy(sorted, test_sample, test_sample_size * sizeof(test_sample[0]));
    qsort(sorted, test_sample_size, sizeof(sorted[0]), element_comparator);

    for (size_t i = 0; i < test_sample_size; i++) {
        insert_sorted_to_simple_list(list, test_sample + i, element_comparator);
    }

    size_t counter = 0;
    for (simple_list_iterator_t* it = simple_list_begin(list); it; it = simple_list_next(it)) {
        assert_int_equal(*(int*)get_from_simple_list_iterator(it), sorted[counter++]);
    }
    free(sorted);
}

static int setup(void** state) {
    if (test_sample) {
        free(test_sample);
    }
    test_sample_size = (rand() % (MAXIMAL_TEST_SAMPLE_SIZE - MINIMAL_TEST_SAMPLE_SIZE)) + MINIMAL_TEST_SAMPLE_SIZE;
    test_sample = calloc(test_sample_size, sizeof(int));
    for (size_t i = 0; i < test_sample_size; i++) {
        test_sample[i] = rand();
    }
    return 0;
}

int main(int argc, char** argv) {
    srand(time(NULL));
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup(simple_test, setup),
        cmocka_unit_test_setup(sort_on_insert_test, setup),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}