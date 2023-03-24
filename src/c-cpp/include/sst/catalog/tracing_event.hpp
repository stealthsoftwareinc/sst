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

#ifndef SST_CATALOG_TRACING_EVENT_HPP
#define SST_CATALOG_TRACING_EVENT_HPP

#include <iterator>
#include <type_traits>
#include <utility>

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/string_to_string_options.hpp>
#include <sst/catalog/to_string.hpp>
#include <sst/catalog/tracing_exception.hpp>
#include <sst/catalog/value_sentinel.hpp>
#include <sst/private/guts/tracing_event/dummy.hpp>

namespace sst {

//----------------------------------------------------------------------
// Enabled implementation
//----------------------------------------------------------------------

template<class Json, bool = true>
class tracing_event {

  template<class>
  friend class sst::tracing_exception;

public:

  //--------------------------------------------------------------------
  // json_t
  //--------------------------------------------------------------------

  using json_t = sst::remove_cvref_t<Json>;

  //--------------------------------------------------------------------

private:

  //--------------------------------------------------------------------

  using string_t = typename json_t::string_t;
  using char_t = typename string_t::value_type;

  json_t json_;
  string_t source_locations_key_;

  //--------------------------------------------------------------------
  // Copy constructor
  //--------------------------------------------------------------------

  tracing_event(tracing_event const & other) noexcept {
    try {
      json_ = other.json_;
      source_locations_key_ = other.source_locations_key_;
    } catch (...) {
      json_ = json_t();
    }
  }

  //--------------------------------------------------------------------
  // add (overload 1)
  //--------------------------------------------------------------------

  template<class Line>
  void add(char const * const file, Line const line) noexcept {
    try {
      SST_ASSERT((file != nullptr));
      SST_ASSERT((line > 0));
      if (!json_.is_null()) {
        string_t s;
        auto p = std::back_inserter(s);
        p = sst::to_string<char_t>(
            file,
            sst::value_sentinel('\0'),
            std::move(p),
            sst::string_to_string_options().replace_unrepresentable(
                true));
        *p = static_cast<char_t>(':');
        ++p;
        p = sst::to_string(line, std::move(p));
        json_[source_locations_key_] += std::move(s);
      }
    } catch (...) {
      json_ = json_t();
    }
  }

  //--------------------------------------------------------------------
  // add (overload 2)
  //--------------------------------------------------------------------

  template<class Line, class... Args>
  void add(char const * const file,
           Line const line,
           json_t const & j,
           Args &&... args) noexcept {
    try {
      SST_ASSERT((file != nullptr));
      SST_ASSERT((line > 0));
      SST_ASSERT((j.is_object()));
      if (!json_.is_null()) {
        SST_ASSERT((!j.contains(source_locations_key_)));
        json_.merge_patch(j);
        add(file, line, std::forward<Args>(args)...);
      }
    } catch (...) {
      json_ = json_t();
    }
  }

  //--------------------------------------------------------------------
  // add (overload 3)
  //--------------------------------------------------------------------

  template<class Line,
           class Key,
           class Value,
           class... Args,
           sst::enable_if_t<!std::is_same<sst::remove_cvref_t<Key>,
                                          json_t>::value> = 0>
  void add(char const * const file,
           Line const line,
           Key && k,
           Value && v,
           Args &&... args) noexcept {
    try {
      SST_ASSERT((file != nullptr));
      SST_ASSERT((line > 0));
      if (!json_.is_null()) {
        json_t j = json_t::object();
        j[std::forward<Key>(k)] = std::forward<Value>(v);
        SST_ASSERT((!(j.begin().key() == source_locations_key_)));
        add(file, line, std::move(j), std::forward<Args>(args)...);
      }
    } catch (...) {
      json_ = json_t();
    }
  }

  //--------------------------------------------------------------------
  // add (overload 4)
  //--------------------------------------------------------------------

  template<class Line>
  void add(char const * const file,
           Line const line,
           guts::tracing_event::dummy) noexcept {
    try {
      SST_ASSERT((file != nullptr));
      SST_ASSERT((line > 0));
      if (!json_.is_null()) {
        add(file, line);
      }
    } catch (...) {
      json_ = json_t();
    }
  }

  //--------------------------------------------------------------------

public:

  //--------------------------------------------------------------------
  // enabled
  //--------------------------------------------------------------------

  static constexpr bool enabled() noexcept {
    return true;
  }

  //--------------------------------------------------------------------
  // Constructor (overload 1)
  //--------------------------------------------------------------------

  template<class Line>
  explicit tracing_event(char const * const file,
                         Line const line) noexcept {
    try {
      SST_ASSERT((file != nullptr));
      SST_ASSERT((line > 0));
      json_ = json_t::object();
      char const k[] = "source_locations";
      using sz = decltype(source_locations_key_.size());
      sz const n = static_cast<sz>(sizeof(k) - 1U);
      source_locations_key_.resize(n);
      for (sz i = 0; i < n; ++i) {
        source_locations_key_[i] = static_cast<char_t>(k[i]);
      }
      json_[source_locations_key_] = json_t::array();
      add(file, line);
    } catch (...) {
      json_ = json_t();
    }
  }

  //--------------------------------------------------------------------
  // Constructor (overload 2)
  //--------------------------------------------------------------------

  template<class Line, class Tev, class... Args>
  explicit tracing_event(char const * const file,
                         Line const line,
                         Tev && tev,
                         Args &&... args) noexcept
      : tracing_event(std::forward<Tev>(tev)) {
    try {
      SST_ASSERT((file != nullptr));
      SST_ASSERT((line > 0));
      if (!json_.is_null()) {
        add(file, line, std::forward<Args>(args)...);
      }
    } catch (...) {
      json_ = json_t();
    }
  }

  //--------------------------------------------------------------------
  // Copy assignment
  //--------------------------------------------------------------------

  tracing_event & operator=(tracing_event const &) = delete;

  //--------------------------------------------------------------------
  // Move constructor
  //--------------------------------------------------------------------

  tracing_event(tracing_event && other) noexcept {
    try {
      json_ = std::move(other.json_);
      source_locations_key_ = std::move(other.source_locations_key_);
    } catch (...) {
      json_ = json_t();
    }
  }

  //--------------------------------------------------------------------
  // Move assignment
  //--------------------------------------------------------------------

  tracing_event & operator=(tracing_event &&) = delete;

  //--------------------------------------------------------------------
  // Destructor
  //--------------------------------------------------------------------

  ~tracing_event() noexcept {
  }

  //--------------------------------------------------------------------
  // SST_ADL_add
  //--------------------------------------------------------------------

  template<class Line, class... Args>
  friend void SST_ADL_add(char const * const file,
                          Line const line,
                          tracing_event & tev,
                          Args &&... args) noexcept {
    SST_ASSERT((file != nullptr));
    SST_ASSERT((line > 0));
    tev.add(file, line, std::forward<Args>(args)...);
  }

  //--------------------------------------------------------------------
  // json
  //--------------------------------------------------------------------

  json_t const * json() const noexcept {
    return json_.is_null() ? nullptr : &json_;
  }

  //--------------------------------------------------------------------
};

//----------------------------------------------------------------------
// Disabled implementation
//----------------------------------------------------------------------

template<class Json>
class tracing_event<Json, false> {

public:

  //--------------------------------------------------------------------
  // json_t
  //--------------------------------------------------------------------

  using json_t = sst::remove_cvref_t<Json>;

  //--------------------------------------------------------------------

private:

  //--------------------------------------------------------------------
  // Copy constructor
  //--------------------------------------------------------------------

  tracing_event(tracing_event const &) = delete;

public:

  //--------------------------------------------------------------------
  // enabled
  //--------------------------------------------------------------------

  static constexpr bool enabled() noexcept {
    return false;
  }

  //--------------------------------------------------------------------
  // Constructor
  //--------------------------------------------------------------------

  template<class Line, class... Args>
  tracing_event(char const * const file,
                Line const line,
                Args &&...) noexcept {
    SST_ASSERT((file != nullptr));
    SST_ASSERT((line > 0));
  }

  //--------------------------------------------------------------------
  // Copy assignment
  //--------------------------------------------------------------------

  tracing_event & operator=(tracing_event const &) = delete;

  //--------------------------------------------------------------------
  // Move constructor
  //--------------------------------------------------------------------

  tracing_event(tracing_event && other) noexcept {
  }

  //--------------------------------------------------------------------
  // Move assignment
  //--------------------------------------------------------------------

  tracing_event & operator=(tracing_event &&) = delete;

  //--------------------------------------------------------------------
  // Destructor
  //--------------------------------------------------------------------

  ~tracing_event() noexcept {
  }

  //--------------------------------------------------------------------
  // SST_ADL_add
  //--------------------------------------------------------------------

  template<class Line, class... Args>
  friend void SST_ADL_add(char const * const file,
                          Line const line,
                          tracing_event &,
                          Args &&...) noexcept {
    SST_ASSERT((file != nullptr));
    SST_ASSERT((line > 0));
  }

  //--------------------------------------------------------------------
  // json
  //--------------------------------------------------------------------

  Json const * json() const noexcept {
    return nullptr;
  }

  //--------------------------------------------------------------------
};

} // namespace sst

#endif // #ifndef SST_CATALOG_TRACING_EVENT_HPP
