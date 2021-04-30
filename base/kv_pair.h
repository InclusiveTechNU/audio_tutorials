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

#include <stdbool.h>

struct base_kv_pair {
    void* key;
    void* value;
};
typedef struct base_kv_pair* KeyValuePair;

struct base_kv_pair_list {
    size_t size;
    KeyValuePair* list;
};
typedef struct base_kv_pair_list* KeyValuePairList;

// KeyValuePair Functions
KeyValuePair base_allocateKeyValuePair(void* key, void* value);
void base_destroyKeyValuePair(KeyValuePair pair);

void kv_pair_setKey(KeyValuePair pair, void* key);
const void* kv_pair_getKey(KeyValuePair pair);

void kv_pair_setValue(KeyValuePair pair, void* value);
const void* kv_pair_getValue(KeyValuePair pair);

// KeyValuePairList Functions
// TODO: Don't return null on size 0 but create an empty array.
KeyValuePairList base_allocateKeyValuePairList(size_t size);
void base_destroyKeyValuePairList(KeyValuePairList list);

void kv_pair_list_setKeyValuePair(KeyValuePairList list, size_t index, KeyValuePair pair);
const KeyValuePair kv_pair_list_getKeyValuePair(KeyValuePairList list, size_t index);
size_t kv_pair_list_getSize(KeyValuePairList list);
bool kv_pair_list_resizeList(KeyValuePairList list, size_t size);
void kv_pair_list_clearList(KeyValuePairList list);
