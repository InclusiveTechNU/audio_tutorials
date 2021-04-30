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
#include "base/messaging/request.h"
#include "base/messaging/selector.h"

struct msg_service {};

typedef struct msg_service* Service;

Service msg_allocateService(const char* name);
void msg_destroyService(Service service);

const char* service_getName(Service service);
size_t service_getSize(Service service);
bool service_addRequest(Service service, Selector selector);
bool service_respondsToSelector(Service service, Selector selector);
