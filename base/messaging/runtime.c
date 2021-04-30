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

#include "base/messaging/runtime.h"

Runtime msg_getRuntime() {
    static struct msg_runtime runtime;
    runtime.selectors = NULL;
    runtime.services = NULL;
    return &runtime;
}

void msg_registerService(Service service);

void msg_unregisterService(Service service);

size_t msg_getServiceList(Service* buffer, size_t bufferCount) {
    // TODO: Allocate services to the buffer
    Runtime runtime = msg_getRuntime();
    HashTable services_table = runtime_getServices(runtime);
    return hashtable_getSize(services_table);
}

Service msg_getService(const char* name);

Selector msg_getSelector(const char* name);

void msg_registerSelector(Selector selector);

void msg_unregisterSelector(Selector selector);

HashTable runtime_getServices(Runtime runtime) {
    return runtime->services;
}

HashTable runtime_getSelectors(Runtime runtime) {
    return runtime->selectors;
}
