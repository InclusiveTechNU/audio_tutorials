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
#include "base/hashtable.h"
#include "base/messaging/service.h"
#include "base/messaging/selector.h"

struct msg_runtime {
    HashTable services;
    HashTable selectors;
};

typedef struct msg_runtime* Runtime;

Runtime msg_getRuntime();

// Service Handling
void msg_registerService(Service service);
void msg_unregisterService(Service service);
size_t msg_getServiceList(Service* buffer, size_t bufferCount);
Service msg_getService(const char* name);

// Selector Handling
Selector msg_getSelector(const char* name);
void msg_registerSelector(Selector selector);
void msg_unregisterSelector(Selector selector);

// Runtime API
HashTable runtime_getServices(Runtime runtime);
HashTable runtime_getSelectors(Runtime runtime);
