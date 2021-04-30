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

#include <node_api.h>

// Returns a javascript function called sendMessage that will be handled by the
// 
napi_value create_send_request_func(napi_env env) {
    return NULL;
}

napi_value create_send_request_func(napi_env env) {
    return NULL;
}

NAPI_MODULE_INIT() {
  return create_messaging_func(env);
}
