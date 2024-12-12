//
// Copyright (C) 2012-2024 Stealth Software Technologies, Inc.
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

#ifndef SST_CATALOG_COOLDOWN_MUTEX_HPP
#define SST_CATALOG_COOLDOWN_MUTEX_HPP

#include <atomic>
#include <chrono>
#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/private/SST_DLL_EXPORT.h>
#include <sst/catalog/SST_STATIC_ASSERT.h>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_bool.hpp>

namespace sst {

class SST_DLL_EXPORT cooldown_mutex final {
  class SST_DLL_EXPORT timer_t final {
    std::atomic<std::chrono::nanoseconds::rep> t_;

  public:
    timer_t();
    bool reset() noexcept;
    bool exceeds(std::chrono::nanoseconds::rep cooldown) const;
  };

public:
  class SST_DLL_EXPORT lock_guard final {
    friend cooldown_mutex;

    cooldown_mutex * m_;

    lock_guard() noexcept;
    lock_guard(cooldown_mutex & m) noexcept;

  public:
    lock_guard(lock_guard && other) noexcept;
    operator bool() const noexcept;
    ~lock_guard() noexcept;

    lock_guard(lock_guard const &) = delete;
    lock_guard & operator=(lock_guard const &) = delete;
    lock_guard & operator=(lock_guard &&) = delete;
  };

private:
  std::atomic<std::chrono::nanoseconds::rep> cooldown_;
  timer_t timer_;
  std::atomic_uintmax_t count_and_locked_;
  bool moved_from_;

public:
  explicit cooldown_mutex(bool start_hot = false);

  template<class Duration,
           sst::enable_if_t<!sst::is_bool<Duration>::value> = 0>
  explicit cooldown_mutex(Duration const cooldown,
                          bool const start_hot = false)
      : cooldown_mutex(start_hot) {
    SST_STATIC_ASSERT(
        (Duration::period::num > 0 || Duration::period::num == 0));
    SST_STATIC_ASSERT((Duration::period::den > 0));
    SST_ASSERT((cooldown.count() > 0 || cooldown.count() == 0));
    cooldown_ = std::chrono::nanoseconds(cooldown).count();
  }

  cooldown_mutex(cooldown_mutex const &) = delete;
  cooldown_mutex(cooldown_mutex &&) = delete;
  cooldown_mutex & operator=(cooldown_mutex const &) = delete;
  cooldown_mutex & operator=(cooldown_mutex &&) = delete;

  ~cooldown_mutex() = default;

  template<class Duration>
  Duration cooldown() const {
    return std::chrono::nanoseconds(cooldown_.load());
  }

  template<class Duration>
  void cooldown(Duration const cooldown) {
    SST_STATIC_ASSERT(
        (Duration::period::num > 0 || Duration::period::num == 0));
    SST_STATIC_ASSERT((Duration::period::den > 0));
    SST_ASSERT((cooldown.count() > 0 || cooldown.count() == 0));
    cooldown_.store(std::chrono::nanoseconds(cooldown).count());
  }

  lock_guard try_lock();
};

extern template SST_DLL_EXPORT cooldown_mutex::cooldown_mutex(
    std::chrono::hours cooldown,
    bool start_hot);

extern template SST_DLL_EXPORT cooldown_mutex::cooldown_mutex(
    std::chrono::minutes cooldown,
    bool start_hot);

extern template SST_DLL_EXPORT cooldown_mutex::cooldown_mutex(
    std::chrono::seconds cooldown,
    bool start_hot);

extern template SST_DLL_EXPORT cooldown_mutex::cooldown_mutex(
    std::chrono::milliseconds cooldown,
    bool start_hot);

extern template SST_DLL_EXPORT cooldown_mutex::cooldown_mutex(
    std::chrono::microseconds cooldown,
    bool start_hot);

extern template SST_DLL_EXPORT cooldown_mutex::cooldown_mutex(
    std::chrono::nanoseconds cooldown,
    bool start_hot);

} // namespace sst

#endif // SST_CATALOG_COOLDOWN_MUTEX_HPP
