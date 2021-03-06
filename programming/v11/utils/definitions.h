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

#pragma once

#ifndef __lk_unused__
    #define __lk_unused__ (void)
#endif

#define new_space(obj) reinterpret_cast<obj*>(::operator new (sizeof(obj)))

#define print(text) fprintf(stderr, "%s\n", text)
#define print_string(text) fprintf(stderr, "%s\n", text.c_str())

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #define OS_WINDOWS 1
#elif defined(__APPLE__)
    #define OS_APPLE 1
#elif defined(__linux__)
    #define OS_LINUX 1
#else
    #error "Unknown Operating System Compilation Target"
#endif
