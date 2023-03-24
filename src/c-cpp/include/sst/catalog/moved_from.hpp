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

#ifndef SST_CATALOG_MOVED_FROM_HPP
#define SST_CATALOG_MOVED_FROM_HPP

#include <atomic>
#include <cstdlib>

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/SST_DEBUG.h>

namespace sst {

namespace guts {

//
// b_ is atomic because it helps avoid exacerbating use-after-move bugs
// in multithreaded code. If b_ weren't atomic, such bugs may introduce
// extra data races on b_.
//

class debug_moved_from final {

  std::atomic<bool> b_{false};

public:

  debug_moved_from() noexcept {
  }

  explicit debug_moved_from(bool const b) noexcept : b_(b) {
  }

  debug_moved_from(debug_moved_from const & other) noexcept
      : b_(other.b_.load()) {
    SST_DEBUG_ASSERT((!b_),
                     ("A moved-from object was illegally copied from"));
  }

  debug_moved_from &
  operator=(debug_moved_from const & other) noexcept {
    b_.store(other.b_.load());
    SST_DEBUG_ASSERT((!b_),
                     ("A moved-from object was illegally copied from"));
    return *this;
  }

  debug_moved_from(debug_moved_from && other) noexcept
      : b_(other.b_.exchange(true)) {
    SST_DEBUG_ASSERT((!b_),
                     ("A moved-from object was illegally moved from"));
  }

  debug_moved_from & operator=(debug_moved_from && other) noexcept {
    b_.store(other.b_.exchange(true));
    SST_DEBUG_ASSERT((!b_),
                     ("A moved-from object was illegally moved from"));
    return *this;
  }

  ~debug_moved_from() noexcept {
  }

  operator bool() const noexcept {
    return b_.load();
  }

  debug_moved_from & operator=(bool const b) noexcept {
    b_.store(b);
    return *this;
  }

}; //

class ndebug_moved_from final {

public:

  ndebug_moved_from() noexcept {
  }

  explicit ndebug_moved_from(bool) noexcept {
  }

  ndebug_moved_from(ndebug_moved_from const &) noexcept {
  }

  ndebug_moved_from & operator=(ndebug_moved_from const &) noexcept {
    return *this;
  }

  ndebug_moved_from(ndebug_moved_from &&) noexcept {
  }

  ndebug_moved_from & operator=(ndebug_moved_from &&) noexcept {
    return *this;
  }

  ~ndebug_moved_from() noexcept {
  }

  operator bool() const {
    SST_DEBUG_ASSERT(false,
                     "An sst::moved_from object was converted to bool "
                     "outside of SST_DEBUG mode.");
    std::abort();
  }

  ndebug_moved_from & operator=(bool) noexcept {
    return *this;
  }

}; //

} // namespace guts

#if SST_DEBUG
using moved_from = sst::guts::debug_moved_from;
#else
using moved_from = sst::guts::ndebug_moved_from;
#endif

} // namespace sst

#endif // #ifndef SST_CATALOG_MOVED_FROM_HPP
