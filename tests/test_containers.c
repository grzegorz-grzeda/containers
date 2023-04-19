#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <stdlib.h>
#include <time.h>
#include <cmocka.h>

#include "simple_list.h"

#define MINIMAL_TEST_SAMPLE_SIZE (10)
#define MAXIMAL_TEST_SAMPLE_SIZE (10000)

static int *test_sample = NULL;
static size_t test_sample_size = 0;

static void simple_list_test(void **state)
{
    simple_list_t *list = create_simple_list();
    assert_ptr_not_equal(list, NULL);

    for (size_t i = 0; i < test_sample_size; i++) {
        append_to_simple_list(list, test_sample + i);
    }
    size_t counter = 0;
    for (simple_list_iterator_t *it = simple_list_begin(list); it; it = simple_list_next(it)) {
        assert_int_equal(*(int *) get_from_simple_list_iterator(it), test_sample[counter++]);
    }
}

static int setup(void **state)
{
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

int main(int argc, char **argv)
{
    srand(time(NULL));
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup(simple_list_test, setup),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}