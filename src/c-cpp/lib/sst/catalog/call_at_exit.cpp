//
// Copyright (C) 2012-2023 Stealth Software Technologies, Inc.
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice (including
// the next paragraph) shall be included in all copies or
// substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// SPDX-License-Identifier: MIT
//

// Include first to test independence.
#include <sst/catalog/call_at_exit.hpp>
// Include twice to test idempotence.
#include <sst/catalog/call_at_exit.hpp>
//

#include <cstdlib>
#include <mutex>
#include <stdexcept>
#include <vector>

#include <sst/catalog/SST_ASSERT.h>

namespace {

std::once_flag flag_;
std::vector<void (*)()> funcs_;
std::mutex mutex_;

void cleanup() noexcept {
  try {
    std::lock_guard<decltype(mutex_)> const lock(mutex_);
    for (auto i = funcs_.size(); i-- > 0;) {
      try {
        funcs_[i]();
      } catch (...) {
      }
    }
  } catch (...) {
  }
}

} // namespace

namespace sst {

void call_at_exit(void (*const func)()) {
  SST_ASSERT((func != nullptr));
  std::call_once(flag_, [] {
    if (std::atexit(cleanup) != 0) {
      throw std::runtime_error("std::atexit() failed.");
    }
  });
  std::lock_guard<decltype(mutex_)> const lock(mutex_);
  funcs_.push_back(func);
}

} // namespace sst
