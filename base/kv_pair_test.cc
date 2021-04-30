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

#include <cstring>
#include <gtest/gtest.h>
extern "C" {
    #include "base/kv_pair.h"
}

KeyValuePair kv_pair_test_createTestPair() {
    // Create key and value objects
    char* sample_key = (char*) malloc(3*sizeof(char));
    if (sample_key == NULL) {
        return NULL;
    }
    char* sample_value = (char*) malloc(5*sizeof(char));
    if (sample_value == NULL) {
        free(sample_key);
        return NULL;
    }
    strcpy(sample_key, "key");
    strcpy(sample_value, "value");

    // Allocate keyvalue pair
    return base_allocateKeyValuePair(sample_key, sample_value);
}

TEST(BaseKeyValuePairTest, PairAllocation) {
    KeyValuePair pair = kv_pair_test_createTestPair();
    ASSERT_FALSE(pair == NULL);
    base_destroyKeyValuePair(pair);
}

TEST(BaseKeyValuePairTest, PairGetKey) {
    KeyValuePair pair = kv_pair_test_createTestPair();
    ASSERT_FALSE(pair == NULL);

    const char* key = (const char*) kv_pair_getKey(pair);
    EXPECT_EQ(strcmp("key", key), 0);

    base_destroyKeyValuePair(pair);
}

TEST(BaseKeyValuePairTest, PairSetKey) {
    KeyValuePair pair = kv_pair_test_createTestPair();
    ASSERT_FALSE(pair == NULL);
    
    // Check key is updated and does not equal previous value
    char* sample_key = (char*) malloc(4*sizeof(char));
    if (sample_key == NULL) {
        base_destroyKeyValuePair(pair);
    }
    ASSERT_FALSE(sample_key == NULL);
    strcpy(sample_key, "test");
    kv_pair_setKey(pair, sample_key);
    const char* key = (const char*) kv_pair_getKey(pair);
    EXPECT_EQ(strcmp("test", key), 0);
    EXPECT_NE(strcmp("key", key), 0);

    // Check that value is not updated on key change
    const char* value = (const char*) kv_pair_getValue(pair);
    EXPECT_EQ(strcmp("value", value), 0);
    EXPECT_NE(strcmp("key", value), 0);
    EXPECT_NE(strcmp(sample_key, value), 0);

    base_destroyKeyValuePair(pair);
}

TEST(BaseKeyValuePairTest, PairGetValue) {
    KeyValuePair pair = kv_pair_test_createTestPair();
    ASSERT_FALSE(pair == NULL);

    const char* value = (const char*) kv_pair_getValue(pair);
    EXPECT_EQ(strcmp("value", value), 0);

    base_destroyKeyValuePair(pair);
}

TEST(BaseKeyValuePairTest, PairSetValue) {
    KeyValuePair pair = kv_pair_test_createTestPair();
    ASSERT_FALSE(pair == NULL);
    
    // Check value is updated and does not equal previous value
    char* sample_value = (char*) malloc(4*sizeof(char));
    if (sample_value == NULL) {
        base_destroyKeyValuePair(pair);
    }
    ASSERT_FALSE(sample_value == NULL);
    strcpy(sample_value, "test");
    kv_pair_setValue(pair, sample_value);
    const char* value = (const char*) kv_pair_getValue(pair);
    EXPECT_EQ(strcmp("test", value), 0);
    EXPECT_NE(strcmp("value", value), 0);

    // Check that key is not updated on value change
    const char* key = (const char*) kv_pair_getKey(pair);
    EXPECT_EQ(strcmp("key", key), 0);
    EXPECT_NE(strcmp("value", key), 0);
    EXPECT_NE(strcmp(sample_value, key), 0);

    base_destroyKeyValuePair(pair);
}

TEST(BaseKeyValuePairTest, PairListAllocation) {
    KeyValuePairList pair_list = base_allocateKeyValuePairList(0);
    EXPECT_TRUE(pair_list == NULL);

    pair_list = base_allocateKeyValuePairList(1);
    ASSERT_FALSE(pair_list == NULL);
    base_destroyKeyValuePairList(pair_list);

    pair_list = base_allocateKeyValuePairList(20);
    ASSERT_FALSE(pair_list == NULL);
    base_destroyKeyValuePairList(pair_list);
}

TEST(BaseKeyValuePairTest, PairListSetKeyValuePair) {
    // TODO: Check that setting pair changes the key value pair from NULL
    // TODO: Check that setting pair changes the key value pair from old value
    // TODO: Check that setting pair changes doesn't change other pairs
    // TODO: Check that setting pair out of index doesn't change pair list
}

TEST(BaseKeyValuePairTest, PairListGetKeyValuePair) {
    // Check that pair values default to NULL
    KeyValuePairList pair_list = base_allocateKeyValuePairList(1);
    ASSERT_FALSE(pair_list == NULL);
    KeyValuePair pair_one = kv_pair_list_getKeyValuePair(pair_list, 0);
    EXPECT_TRUE(pair_one == NULL);
    base_destroyKeyValuePairList(pair_list);

    // Check that pair list returns proper pair at index
    pair_list = base_allocateKeyValuePairList(1);
    KeyValuePair pair_two = kv_pair_test_createTestPair();
    kv_pair_list_setKeyValuePair(pair_list, 0, pair_two);
    KeyValuePair get_pair_two = kv_pair_list_getKeyValuePair(pair_list, 0);
    EXPECT_FALSE(get_pair_two == NULL);

    const char* key = (const char*) kv_pair_getKey(get_pair_two);
    const char* value = (const char*) kv_pair_getValue(get_pair_two);
    EXPECT_EQ(strcmp("key", key), 0);
    EXPECT_EQ(strcmp("value", value), 0);
    base_destroyKeyValuePairList(pair_list);

    // TODO: Check that pair list returns proper pair at index in many array
    // TODO: Check that pair list returns nulls for out of range index
    // TODO: Check that null pair list returns null for anything
}

TEST(BaseKeyValuePairTest, PairListGetSize) {
    // TODO: Check that null pair list returns 0
    // TODO: Check that pair list returns initialized size
    // TODO: Check that resizing list returns new size
    // TODO: Check that setting pair doesn't change size
    // TODO: Check that getting pair doesn't change size
}


TEST(BaseKeyValuePairTest, PairListResizeList) {
    // TODO: Check that resize null pair list returns false
    // TODO: Check that resizing list to same size returns true
    // TODO: Check that resizing list to same size keeps list the same
    // TODO: Check that resizing list larger adds new null elements
    // TODO: Check that resizing list smaller removes last few elements
}

TEST(BaseKeyValuePairTest, PairListClearList) {
    // Check that clearing empty list remains empty
    // Check that clearing list sets values to null
}
