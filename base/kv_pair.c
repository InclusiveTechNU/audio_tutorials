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
#include "base/kv_pair.h"

KeyValuePair base_allocateKeyValuePair(void* key, void* value) {
    KeyValuePair pair = malloc(sizeof(struct base_kv_pair));
    if (pair == NULL) {
        return NULL;
    }
    pair->key = key;
    pair->value = value;
    return pair;
}

void base_destroyKeyValuePair(KeyValuePair pair) {
    if (pair == NULL) {
        return;
    }
    free(pair->key);
    free(pair->value);
    free(pair);
}

void kv_pair_setKey(KeyValuePair pair, void* key) {
    if (pair == NULL) {
        return;
    }
    free(pair->key);
    pair->key = key;
}

const void* kv_pair_getKey(KeyValuePair pair) {
    if (pair == NULL) {
        return NULL;
    }
    return pair->key;
}

void kv_pair_setValue(KeyValuePair pair, void* value) {
    if (pair == NULL) {
        return;
    }
    free(pair->value);
    pair->value = value;
}

const void* kv_pair_getValue(KeyValuePair pair) {
    if (pair == NULL) {
        return NULL;
    }
    return pair->value;
}

KeyValuePairList base_allocateKeyValuePairList(size_t size) {
    if (size <= 0) {
        return NULL;
    }

    KeyValuePair* internal_pair_list = malloc(size * sizeof(KeyValuePair));
    if (internal_pair_list == NULL) {
        return NULL;
    }

    KeyValuePairList pair_list = malloc(sizeof(KeyValuePairList));
    if (pair_list == NULL) {
        free(internal_pair_list);
        return NULL;
    }

    for (size_t list_index = 0; list_index < size; list_index++) {
        internal_pair_list[list_index] = NULL;
    }
    pair_list->list = internal_pair_list;
    pair_list->size = size;
    return pair_list;
}

void base_destroyKeyValuePairList(KeyValuePairList list) {
    if (list == NULL) {
        return;
    }
    size_t list_size = kv_pair_list_getSize(list);
    for (size_t list_index = 0; list_index < list_size; list_index++) {
        KeyValuePair pair = list->list[list_index];
        base_destroyKeyValuePair(pair);
    }
    free(list->list);
    free(list);
}

void kv_pair_list_setKeyValuePair(KeyValuePairList list, size_t index, KeyValuePair pair) {
    if (list == NULL) {
        return;
    }
    size_t list_size = kv_pair_list_getSize(list);
    if (index >= list_size) {
        return;
    }
    KeyValuePair current_pair = list->list[index];
    base_destroyKeyValuePair(current_pair);
    list->list[index] = pair;
}

const KeyValuePair kv_pair_list_getKeyValuePair(KeyValuePairList list, size_t index) {
    if (list == NULL) {
        return NULL;
    }
    size_t list_size = kv_pair_list_getSize(list);
    if (index >= list_size) {
        return NULL;
    }
    return list->list[index];
}

size_t kv_pair_list_getSize(KeyValuePairList list) {
    if (list == NULL) {
        return 0;
    }
    return list->size;
}

bool kv_pair_list_resizeList(KeyValuePairList list, size_t size) {
    if (list == NULL) {
        return false;
    }
    size_t current_size = kv_pair_list_getSize(list);
    if (current_size == size) {
        return true;
    } else if (current_size > size) {
        size_t bottom_index = current_size - (current_size - size) - 1;
        size_t start_index = current_size - 1;
        for (size_t list_index = start_index; list_index >= bottom_index; list_index--) {
            KeyValuePair pair = list->list[list_index];
            base_destroyKeyValuePair(pair);
            list->list[list_index] = NULL;
        }
    }
    KeyValuePair* new_list = realloc(list->list, size*sizeof(KeyValuePair));
    if (new_list == NULL) {
        return false;
    }
    list->list = new_list;
    if (current_size < size) {
        for (size_t list_index = current_size; list_index < size; list_index++) {
            list->list[list_index] = NULL;
        }
    }
    return true;
}

void kv_pair_list_clearList(KeyValuePairList list) {
    if (list == NULL) {
        return;
    }
    size_t list_size = kv_pair_list_getSize(list);
    for (size_t list_index = 0; list_index < list_size; list_index++) {
        KeyValuePair pair = list->list[list_index];
        base_destroyKeyValuePair(pair);
        list->list[list_index] = NULL;
    }
}
