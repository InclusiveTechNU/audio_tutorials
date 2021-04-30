#  Copyright 2020 Northwestern Inclusive Technology Lab
# 
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.

workspace(
    name = "itl",
    managed_directories = {"@npm": ["third_party/node/node_modules"]},
)

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

###########################################
### Define URL and keys for build rules ###
###########################################

# Python Build Rules
rules_python_name = "rules_python"
rules_python_url = "https://github.com/bazelbuild/rules_python/releases/download/0.1.0/rules_python-0.1.0.tar.gz"
rules_python_sha256 = "b6d46438523a3ec0f3cead544190ee13223a52f6a6765a29eae7b7cc24cc83a0"

# Protocol Buffer Rules
rules_proto_name = "rules_proto"
rules_proto_url = "https://github.com/bazelbuild/rules_proto/archive/97d8af4dc474595af3900dd85cb3a29ad28cc313.tar.gz"
rules_proto_sha256 = "602e7161d9195e50246177e7c55b2f39950a9cf7366f74ed5f22fd45750cd208"
rules_proto_strip_prefix = "rules_proto-97d8af4dc474595af3900dd85cb3a29ad28cc313"

# Protocol Buffer Extension Rules
rules_proto_ext_name = "build_stack_rules_proto"
rules_proto_ext_url = "https://github.com/stackb/rules_proto.git"
rules_proto_ext_commit = "e20cebe14d1b9059dc4e7faee159f5b7176e0050"

# Node.js Build Rules
rules_node_js_name = "build_bazel_rules_nodejs"
rules_node_js_sha256 = "f533eeefc8fe1ddfe93652ec50f82373d0c431f7faabd5e6323f6903195ef227"
rules_node_js_url = "https://github.com/bazelbuild/rules_nodejs/releases/download/3.3.0/rules_nodejs-3.3.0.tar.gz"

################################################
### Define URL and keys for third party deps ###
################################################

gtest_name = "gtest"
gtest_url = "https://github.com/google/googletest.git"

################################################
### Define Third-Party Supported Build Files ###
################################################

###################################
### Retrieve Rules From Sources ###
###################################

http_archive(
    name = rules_python_name,
    url = rules_python_url,
    sha256 = rules_python_sha256,
)

http_archive(
    name = rules_proto_name,
    url = rules_proto_url,
    sha256 = rules_proto_sha256,
    strip_prefix = rules_proto_strip_prefix,
)

git_repository(
    name = rules_proto_ext_name,
    remote = rules_proto_ext_url,
    commit = rules_proto_ext_commit,
)

http_archive(
    name = rules_node_js_name,
    sha256 = rules_node_js_sha256,
    urls = [rules_node_js_url],
)

git_repository(
    name = gtest_name,
    remote = gtest_url,
    branch = "master"
)

##############################################
### Load & Customize Retrieved Build Rules ###
##############################################

http_archive(
    name = "build_stack_rules_proto",
    urls = ["https://github.com/stackb/rules_proto/archive/b2913e6340bcbffb46793045ecac928dcf1b34a5.tar.gz"],
    sha256 = "d456a22a6a8d577499440e8408fc64396486291b570963f7b157f775be11823e",
    strip_prefix = "rules_proto-b2913e6340bcbffb46793045ecac928dcf1b34a5",
)
load("@build_stack_rules_proto//node:deps.bzl", "node_proto_library")

node_proto_library()

load("@org_pubref_rules_node//node:rules.bzl", "node_repositories", "yarn_modules")

node_repositories()

yarn_modules(
    name = "proto_node_modules",
    deps = {
        "google-protobuf": "3.6.1",
    },
)

# Install pip dependencies
load("@rules_python//python:pip.bzl", "pip_install")
pip_install(
   name = "pip",
   requirements = "//third_party/pip:requirements.txt",
)

# Install protocol buffer dependencies and build toolchain
load("@rules_proto//proto:repositories.bzl", "rules_proto_dependencies", "rules_proto_toolchains")
rules_proto_dependencies()
rules_proto_toolchains()

# Install protocol buffer extension library
load("@build_stack_rules_proto//python:deps.bzl", "python_proto_library")
python_proto_library()
pip_install(
    name = "protobuf_py_deps",
    requirements = "@build_stack_rules_proto//python/requirements:protobuf.txt",
)

# Install Node.JS build rules and add packages from Yarn
load("@build_bazel_rules_nodejs//:index.bzl", "node_repositories", "yarn_install")
node_repositories(
    node_version = "16.0.0",
    node_repositories = {
    "16.0.0-darwin_amd64": ("node-v16.0.0-darwin-arm64.tar.gz", "node-v16.0.0-darwin-arm64", "2d6d412abcf7c9375f19fde14086a6423e5bb9415eeca1ccad49638ffc476ea3"),
    "16.0.0-linux_amd64": ("node-v16.0.0-linux-x64.tar.xz", "node-v16.0.0-linux-x64", "92220638d661a43bd0fee2bf478cb283ead6524f231aabccf14c549ebc2bc338"),
    "16.0.0-windows_amd64": ("node-v16.0.0-win-x64.zip", "node-v16.0.0-win-x64", "936ada36cb6f09a5565571e15eb8006e45c5a513529c19e21d070acf0e50321b"),
  },
    node_urls = ["https://nodejs.org/dist/v{version}/{filename}"],
    package_json = ["//third_party/node:package.json"]
)
yarn_install(
    name = "npm",
    package_json = "//third_party/node:package.json",
    yarn_lock = "//third_party/node:yarn.lock",
)

http_archive(
   name = "rules_foreign_cc",
   sha256 = "c2cdcf55ffaf49366725639e45dedd449b8c3fe22b54e31625eb80ce3a240f1e",
   strip_prefix = "rules_foreign_cc-0.1.0",
   url = "https://github.com/bazelbuild/rules_foreign_cc/archive/0.1.0.zip",
)
load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")

# Install @bazel/labs modules
load("@npm//@bazel/labs:package.bzl", "npm_bazel_labs_dependencies")
npm_bazel_labs_dependencies()

# Abseil C++ version
local_repository(
    name = "abseil_cpp",
    path = "third_party/abseil/cpp",
)

local_repository(
    name = "com_google_absl",
    path = "third_party/abseil/cpp",
)

# Abseil Python Version
local_repository(
    name = "abseil_py",
    path = "third_party/abseil/py",
)
