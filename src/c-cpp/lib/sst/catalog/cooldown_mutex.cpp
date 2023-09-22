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
#include <sst/catalog/cooldown_mutex.hpp>
// Include twice to test idempotence.
#include <sst/catalog/cooldown_mutex.hpp>
//

#include <chrono>
#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/mono_time_ns.hpp>

namespace sst {

cooldown_mutex::timer_t::timer_t() : t_(sst::mono_time_ns()) {
}

bool cooldown_mutex::timer_t::reset() noexcept {
  try {
    t_.store(sst::mono_time_ns());
    return true;
  } catch (...) {
    // This means sst::mono_time_ns() threw an exception. In this case,
    // the next (successful) try_lock() call will skip the cooldown and
    // acquire the lock immediately. You'd think this would be easy to
    // fix, but it's not. The problem is that t_ must be atomic and
    // std::steady_clock::time_point can't be made atomic, so
    // std::steady_clock::now() being noexcept isn't enough.
    return false;
  }
}

bool cooldown_mutex::timer_t::exceeds(
    std::chrono::nanoseconds::rep const cooldown) const {
  return sst::mono_time_ns() - t_.load() >= cooldown;
}

cooldown_mutex::lock_guard::lock_guard() noexcept : m_(nullptr) {
}

cooldown_mutex::lock_guard::lock_guard(cooldown_mutex & m) noexcept
    : m_(&m) {
}

cooldown_mutex::lock_guard::lock_guard(lock_guard && other) noexcept
    : m_(other.m_) {
  other.m_ = nullptr;
}

cooldown_mutex::lock_guard::operator bool() const noexcept {
  return m_ != nullptr;
}

cooldown_mutex::lock_guard::~lock_guard() noexcept {
  if (m_ != nullptr) {
    m_->timer_.reset();
    m_->count_and_locked_.fetch_xor(1);
  }
}

cooldown_mutex::cooldown_mutex(bool const start_hot)
    : cooldown_(0),
      timer_(),
      count_and_locked_(start_hot ? 2 : 0),
      moved_from_(false) {
}

cooldown_mutex::lock_guard cooldown_mutex::try_lock() {
  SST_ASSERT((!moved_from_));
  auto expected = count_and_locked_.load();
  while (true) {
    auto const count = expected >> 1;
    if (count > 0) {
      bool const locked = (expected & 1) == 1;
      if (locked || !timer_.exceeds(cooldown_.load())) {
        return {};
      }
    }
    // Doing += 2 prevents count from ever hitting 0 again.
    auto const desired = count > 0 ? ((count + 2) << 1) | 1 : 3;
    if (count_and_locked_.compare_exchange_strong(expected, desired)) {
      return {*this};
    }
  }
}

template cooldown_mutex::cooldown_mutex(std::chrono::hours cooldown,
                                        bool start_hot);

template cooldown_mutex::cooldown_mutex(std::chrono::minutes cooldown,
                                        bool start_hot);

template cooldown_mutex::cooldown_mutex(std::chrono::seconds cooldown,
                                        bool start_hot);

template cooldown_mutex::cooldown_mutex(
    std::chrono::milliseconds cooldown,
    bool start_hot);

template cooldown_mutex::cooldown_mutex(
    std::chrono::microseconds cooldown,
    bool start_hot);

template cooldown_mutex::cooldown_mutex(
    std::chrono::nanoseconds cooldown,
    bool start_hot);

} // namespace sst
