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
#include "simple-dictionary.h"
#include <stdlib.h>

typedef struct {
    const void* key;
    simple_list_t* values;
} key_entry_t;

typedef struct simple_dictionary {
    simple_list_t* keys;
    simple_dictionary_key_comparator_t are_keys_equal;
} simple_dictionary_t;

simple_dictionary_t* create_simple_dictionary(simple_dictionary_key_comparator_t comparator) {
    if (!comparator) {
        return NULL;
    }
    simple_dictionary_t* dict = calloc(1, sizeof(simple_dictionary_t));
    if (!dict) {
        return NULL;
    }
    dict->are_keys_equal = comparator;
    dict->keys = create_simple_list();
    if (!dict->keys) {
        free(dict);
        return NULL;
    }
    return dict;
}

static key_entry_t* search_for_key(simple_dictionary_t* dictionary, const void* key) {
    for (simple_list_iterator_t* it = simple_list_begin(dictionary->keys); it; it = simple_list_next(it)) {
        key_entry_t* entry = get_from_simple_list_iterator(it);
        if (dictionary->are_keys_equal(entry->key, key)) {
            return entry;
        }
    }
    return NULL;
}

static key_entry_t* create_key_entry(const void* key) {
    key_entry_t* entry = calloc(1, sizeof(key_entry_t));
    if (!entry) {
        return NULL;
    }
    entry->values = create_simple_list();
    if (!entry->values) {
        free(entry);
        return NULL;
    }
    entry->key = key;
    return entry;
}

static key_entry_t* search_or_create_key_entry(simple_dictionary_t* dictionary, const void* key) {
    key_entry_t* entry = search_for_key(dictionary, key);
    if (!entry) {
        entry = create_key_entry(key);
    }
    return entry;
}

void insert_to_simple_dictionary(simple_dictionary_t* dictionary, const void* key, void* value) {
    if (!dictionary || !key) {
        return;
    }
    key_entry_t* entry = search_or_create_key_entry(dictionary, key);
    if (!entry) {
        return;
    }
    append_to_simple_list(entry->values, value);
    append_to_simple_list(dictionary->keys, entry);
}

void* get_first_from_simple_dictionary(simple_dictionary_t* dictionary, const void* key) {
    simple_list_iterator_t* it = get_all_from_simple_dictionary(dictionary, key);
    return get_from_simple_list_iterator(it);
}

simple_list_iterator_t* get_all_from_simple_dictionary(simple_dictionary_t* dictionary, const void* key) {
    if (!dictionary || !key) {
        return NULL;
    }
    key_entry_t* entry = search_for_key(dictionary, key);
    if (!entry) {
        return NULL;
    }
    return simple_list_begin(entry->values);
}