/*
 * Copyright 2020 Northwestern Inclusive Technology Lab
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "base/hashtable.h"

HashTable base_allocateHashTable(size_t size) {

}

HashTable base_allocateHashTable() {
    return base_allocateHashTable(10);
}

void base_destroyHashTable(HashTable hashtable) {
    hashtable_clearTable(hashtable, false);
}

size_t hashtable_getSize(HashTable hashtable) {
    return hashtable->size;
}

void hashtable_clearTable(HashTable hashtable, bool reallocate) {
    size_t bin_count = hashtable->allocated_bins;
    for (size_t bin_index = 0; bin_index < bin_count; bin_index++) {
        KeyValuePairList pair = hashtable->pairs[bin_index];
        size_t pair_index = 0;
        while (pair != NULL) {
            base_destroyKeyValuePair(pair);
            pair_index++;
            pair = &(hashtable->pairs[bin_index][pair_index]);
        }
    }
}

void hashtable_clearTable(HashTable hashtable) {
    hashtable_clearTable(hashtable, true);
}

bool hashtable_resizeTable(HashTable hashtable, size_t size);
