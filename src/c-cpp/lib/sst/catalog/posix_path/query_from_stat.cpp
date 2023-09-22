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
#include <sst/catalog/posix_path.hpp>
// Include twice to test idempotence.
#include <sst/catalog/posix_path.hpp>
//

#include <sst/catalog/SST_WITH_POSIX.h>

#if SST_WITH_POSIX

#include <cstdint>
#include <stdexcept>
#include <utility>

#include <sys/stat.h>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/checked_cast.hpp>
#include <sst/catalog/optional.hpp>

namespace sst {

posix_path const &
posix_path::query_from_stat(void const * const data) const {
  SST_ASSERT((!this->moved_from_));

  sst::optional<bool> new_test_e;
  sst::optional<bool> new_test_d;
  sst::optional<bool> new_test_f;
  sst::optional<std::uintmax_t> new_f_size;

  if (data == nullptr) {
    new_test_e.emplace(false);
    new_test_d.emplace(false);
    new_test_f.emplace(false);
    new_f_size.emplace(static_cast<std::uintmax_t>(0));
  } else {
    struct ::stat const & d = *static_cast<struct ::stat const *>(data);
    new_test_e.emplace(true);
    new_test_d.emplace(S_ISDIR(d.st_mode) != 0);
    new_test_f.emplace(S_ISREG(d.st_mode) != 0);
    new_f_size.emplace(sst::checked_cast<std::uintmax_t>(d.st_size));
  }

#define ITEMS                                                          \
  ITEM(test_e)                                                         \
  ITEM(test_d)                                                         \
  ITEM(test_f)                                                         \
  ITEM(f_size)

#define ITEM(X)                                                        \
  if (new_##X && this->X##_ && *new_##X != *this->X##_) {              \
    throw std::runtime_error("Path attribute mismatch");               \
  }

  ITEMS

#undef ITEM

#define ITEM(X)                                                        \
  if (new_##X && !this->X##_) {                                        \
    this->X##_ = std::move(new_##X);                                   \
  }

  ITEMS

#undef ITEM

#undef ITEMS

  return *this;
}

} // namespace sst

#endif // #if SST_WITH_POSIX
