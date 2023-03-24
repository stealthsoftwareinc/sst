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

#ifndef SST_CATALOG_ATOMIC_SHARED_PTR_HPP
#define SST_CATALOG_ATOMIC_SHARED_PTR_HPP

#include <atomic>
#include <memory>
#include <sst/catalog/SST_CPP20_OR_LATER.h>

namespace sst {

template<class T>
class atomic_shared_ptr final {
#if SST_CPP20_OR_LATER
  std::atomic<std::shared_ptr<T>> ptr_;
#else
  std::shared_ptr<T> ptr_;
#endif

public:
  atomic_shared_ptr() = default;
  ~atomic_shared_ptr() = default;

  atomic_shared_ptr(atomic_shared_ptr const &) = delete;
  atomic_shared_ptr(atomic_shared_ptr &&) = delete;
  void operator=(atomic_shared_ptr const &) = delete;
  void operator=(atomic_shared_ptr &&) = delete;

  void store(std::shared_ptr<T> const & ptr,
             std::memory_order mo = std::memory_order_seq_cst) {
#if SST_CPP20_OR_LATER
    ptr_.store(ptr, mo);
#else
    std::atomic_store_explicit(&ptr_, ptr, mo);
#endif
  }

  std::shared_ptr<T>
  load(std::memory_order mo = std::memory_order_seq_cst) const {
#if SST_CPP20_OR_LATER
    return ptr_.load(mo);
#else
    return std::atomic_load_explicit(&ptr_, mo);
#endif
  }

  atomic_shared_ptr(std::shared_ptr<T> const & ptr) {
    store(ptr);
  }

  void operator=(std::shared_ptr<T> const & ptr) {
    store(ptr);
  }

  operator std::shared_ptr<T>() const {
    return load();
  }
};

} // namespace sst

#endif // #ifndef SST_CATALOG_ATOMIC_SHARED_PTR_HPP
