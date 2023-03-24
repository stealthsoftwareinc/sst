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
#include <sst/catalog/c_locale.hpp>
// Include twice to test idempotence.
#include <sst/catalog/c_locale.hpp>
//

#include <sst/catalog/SST_WITH_POSIX.h>

#if SST_WITH_POSIX

#include <errno.h>

#include <mutex>
#include <stdexcept>
#include <vector>

#include <sst/catalog/SST_WITH_MACOS.h>
#include <sst/catalog/call_at_exit.hpp>
#include <sst/catalog/to_string.hpp>

#if SST_WITH_MACOS
#include <xlocale.h>
#else
#include <locale.h>
#endif

namespace sst {

namespace {

std::once_flag flag1_;
std::once_flag flag2_;
thread_local locale_t locale_ = (locale_t)0;
std::vector<locale_t> * locales_ = nullptr;
std::mutex mutex_;

void cleanup() noexcept {
  try {
    if (locales_ != nullptr) {
      for (auto i = locales_->size(); i-- > 0;) {
        try {
          freelocale((*locales_)[i]);
        } catch (...) {
        }
      }
      delete locales_;
    }
  } catch (...) {
  }
}

} // namespace

locale_t c_locale() {
  std::call_once(flag1_, [] { sst::call_at_exit(cleanup); });
  std::call_once(flag2_, [] { locales_ = new std::vector<locale_t>; });
  if (locale_ == (locale_t)0) {
    locale_t const locale = newlocale(LC_ALL_MASK, "C", (locale_t)0);
    if (locale == (locale_t)0) {
      int const e = errno;
      // We can't use sst::errno_error_string because that function may
      // depend on this one. Doing so may cause a circular dependency.
      throw std::runtime_error("newlocale(LC_ALL_MASK, \"C\", "
                               "(locale_t)0) failed (errno error code "
                               + sst::to_string(e) + ").");
    }
    try {
      std::lock_guard<decltype(mutex_)> const lock(mutex_);
      locales_->push_back(locale);
    } catch (...) {
      try {
        freelocale(locale);
      } catch (...) {
      }
      throw;
    }
    locale_ = locale;
  }
  return locale_;
}

} // namespace sst

#endif
