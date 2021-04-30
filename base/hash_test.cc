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

#include <gtest/gtest.h>
extern "C" {
    #include "base/hash.h"
}

TEST(BaseHashLibTest, StringEqualText) {
    uint32_t string_one_hash = base_hashString("Hello World");
    uint32_t string_two_hash = base_hashString("Hello World");
    EXPECT_EQ(string_one_hash, string_two_hash);

    string_one_hash = base_hashString("hello world");
    string_two_hash = base_hashString("Hello World");
    EXPECT_NE(string_one_hash, string_two_hash);
}

TEST(BaseHashLibTest, StringNotEqualText) {
    uint32_t string_one_hash = base_hashString("Hello World");
    uint32_t string_two_hash = base_hashString("Hello World!");
    EXPECT_NE(string_one_hash, string_two_hash);

    string_one_hash = base_hashString("Apple");
    string_two_hash = base_hashString("Pear");
    EXPECT_NE(string_one_hash, string_two_hash);
}
