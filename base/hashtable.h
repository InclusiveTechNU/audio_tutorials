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

#include <stdlib.h>
#include <stdbool.h>
#include "base/kv_pair.h"

struct base_hashtable {
    size_t size;
    size_t allocated_bins;
    KeyValuePairList* pairs;
};

typedef struct base_hashtable* HashTable;

HashTable base_allocateHashTable(size_t size);
HashTable base_allocateHashTable();

size_t hashtable_getSize(HashTable hashtable);
void hashtable_clearTable(HashTable hashtable, bool reallocate);
void hashtable_clearTable(HashTable hashtable);
bool hashtable_resizeTable(HashTable hashtable, size_t size);

void base_destroyHashTable(HashTable hashtable);
