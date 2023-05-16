#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <cmocka.h>

#include "simple-dictionary.h"

#define MINIMAL_TEST_SAMPLE_SIZE (10)
#define MAXIMAL_TEST_SAMPLE_SIZE (10000)
#define MINIMAL_KEY_SIZE (10)
#define MAXIMAL_KEY_SIZE (10000)

typedef struct {
    const char *key;
    int value;
} key_value_pair_t;

static key_value_pair_t *test_pairs_sample = NULL;
static size_t test_pairs_sample_size = 0;

static bool string_key_comparator(const void *key_0, const void *key_1)
{
    return (strcmp((const char *) key_0, (const char *) key_1) == 0);
}

static void simple_test(void **state)
{
    simple_dictionary_t *dict = create_simple_dictionary(NULL);
    assert_ptr_equal(dict, NULL);

    dict = create_simple_dictionary(string_key_comparator);
    assert_ptr_not_equal(dict, NULL);

    for (size_t i = 0; i < test_pairs_sample_size; i++) {
        insert_to_simple_dictionary(dict, test_pairs_sample[i].key, &test_pairs_sample[i].value);
    }

    for (size_t i = 0; i < test_pairs_sample_size; i++) {
        int value = *(int *) get_first_from_simple_dictionary(dict, test_pairs_sample[i].key);
        assert_int_equal(test_pairs_sample[i].value, value);
    }
}

static size_t generate_random_size(int min, int max)
{
    return (size_t) ((rand() % (max - min)) + min);
}

static int generate_random_value(void)
{
    return rand();
}

static const char *generate_random_key(void)
{
    size_t buffer_size = generate_random_size(MINIMAL_KEY_SIZE, MAXIMAL_KEY_SIZE);
    char *buffer = calloc(buffer_size + 1, sizeof(char));
    for (size_t i = 0; i < buffer_size; i++) {
        buffer[i] = (char) ((rand() % ('z' - 'a') + 'a'));
    }
    return (const char *) buffer;
}
static void generate_random_pair(key_value_pair_t *pair)
{
    pair->key = generate_random_key();
    pair->value = generate_random_value();
}

static void destroy_pair(key_value_pair_t *pair)
{
    free((void *) pair->key);
}

static int per_test_setup(void **state)
{
    test_pairs_sample_size = generate_random_size(MINIMAL_TEST_SAMPLE_SIZE, MAXIMAL_TEST_SAMPLE_SIZE);
    test_pairs_sample = calloc(test_pairs_sample_size, sizeof(key_value_pair_t));
    for (size_t i = 0; i < test_pairs_sample_size; i++) {
        generate_random_pair(test_pairs_sample + i);
    }
    return 0;
}

static int per_test_tear_down(void **state)
{
    for (size_t i = 0; i < test_pairs_sample_size; i++) {
        destroy_pair(test_pairs_sample + i);
    }
    free(test_pairs_sample);
    test_pairs_sample = NULL;
    test_pairs_sample_size = 0;
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(simple_test, per_test_setup, per_test_tear_down),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}