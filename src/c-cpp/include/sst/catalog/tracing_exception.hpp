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

#ifndef SST_CATALOG_TRACING_EXCEPTION_HPP
#define SST_CATALOG_TRACING_EXCEPTION_HPP

#include <exception>
#include <utility>

#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/with_what_suffix.hpp>

namespace sst {

template<class Tev>
class tracing_exception : public std::exception,
                          public sst::with_what_suffix {

public:

  //--------------------------------------------------------------------
  // tev_t
  //--------------------------------------------------------------------

  using tev_t = sst::remove_cvref_t<Tev>;

  //--------------------------------------------------------------------

private:

  //--------------------------------------------------------------------

  tev_t tev_;

  //--------------------------------------------------------------------

public:

  //--------------------------------------------------------------------
  // Constructor
  //--------------------------------------------------------------------

  tracing_exception(tev_t && tev) noexcept : tev_(std::move(tev)) {
  }

  //--------------------------------------------------------------------
  // Copy constructor
  //--------------------------------------------------------------------

  tracing_exception(tracing_exception const & other) noexcept
      : tev_(other.tev_) {
  }

  //--------------------------------------------------------------------
  // Copy assignment
  //--------------------------------------------------------------------

  tracing_exception &
  operator=(tracing_exception const & other) noexcept {
    tev_ = other.tev_;
    return *this;
  }

  //--------------------------------------------------------------------
  // Move constructor
  //--------------------------------------------------------------------

  tracing_exception(tracing_exception && other) noexcept
      : tev_(std::move(other.tev_)) {
  }

  //--------------------------------------------------------------------
  // Move assignment
  //--------------------------------------------------------------------

  tracing_exception & operator=(tracing_exception && other) noexcept {
    tev_ = std::move(other.tev_);
  }

  //--------------------------------------------------------------------
  // Destructor
  //--------------------------------------------------------------------

  ~tracing_exception() noexcept {
  }

  //--------------------------------------------------------------------
  // tev
  //--------------------------------------------------------------------

  tev_t const & tev() const noexcept {
    return tev_;
  }

  //--------------------------------------------------------------------
  // what
  //--------------------------------------------------------------------
  //
  // A tracing exception only serves to attach a tracing event to its
  // nested exception, so it does not have a message.
  //

  char const * what() const noexcept override {
    return "";
  }

  char const * what_suffix() const noexcept override {
    return "";
  }

  //--------------------------------------------------------------------

}; //

} // namespace sst

#endif // #ifndef SST_CATALOG_TRACING_EXCEPTION_HPP
