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

#ifndef SST_CATALOG_SEQ_HASH_SHELL_HPP
#define SST_CATALOG_SEQ_HASH_SHELL_HPP

#include <utility>

#include <sst/catalog/SST_COMPILES.hpp>
#include <sst/catalog/SST_NOEXCEPT.hpp>
#include <sst/catalog/cbegin.hpp>
#include <sst/catalog/cend.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_input_iterator.hpp>
#include <sst/catalog/is_integer_ish.hpp>
#include <sst/catalog/is_iterable.hpp>
#include <sst/catalog/is_sentinel.hpp>
#include <sst/catalog/is_value_sentinel.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/value_sentinel.hpp>
#include <sst/catalog/value_type_t.hpp>

namespace sst {

template<class SeqHashCore>
class seq_hash_shell : public sst::remove_cvref_t<SeqHashCore> {

  using core = sst::remove_cvref_t<SeqHashCore>;

public:

  seq_hash_shell() SST_NOEXCEPT(true) = default;

  seq_hash_shell(seq_hash_shell const &) SST_NOEXCEPT(
      noexcept(core(std::declval<core const &>()))) = default;

  seq_hash_shell &
  operator=(seq_hash_shell const &) SST_NOEXCEPT(noexcept(
      std::declval<core &>() = std::declval<core const &>())) = default;

  seq_hash_shell(seq_hash_shell &&) SST_NOEXCEPT(true) = default;

  seq_hash_shell & operator=(seq_hash_shell &&)
      SST_NOEXCEPT(true) = default;

  ~seq_hash_shell() SST_NOEXCEPT(true) = default;

  template<class T>
  using is_input = typename core::template is_input<T>;

  using output_t = typename core::output_t;

  seq_hash_shell & clear() noexcept {
    core::clear();
    return *this;
  }

  seq_hash_shell &
  init() noexcept(noexcept(std::declval<core &>().init())) {
    core::init();
    return *this;
  }

  template<class Src,
           class End,
           sst::enable_if_t<
               sst::is_input_iterator<Src, is_input>::value
               && (sst::is_integer_ish<End>::value
                   || sst::is_sentinel<End, Src>::value
                   || sst::is_value_sentinel<End, Src>::value)> = 0>
  seq_hash_shell & update(Src && src, End && end) noexcept(
      noexcept(std::declval<core &>().update(std::forward<Src>(src),
                                             std::forward<End>(end)))) {
    core::update(std::forward<Src>(src), std::forward<End>(end));
    return *this;
  }

  template<class Src,
           class End,
           sst::enable_if_t<
               sst::is_iterable<Src, is_input>::value
               && (sst::is_integer_ish<End>::value
                   || sst::is_sentinel<End, Src>::value
                   || sst::is_value_sentinel<End, Src>::value)> = 0>
  seq_hash_shell & update(Src && src, End && end) noexcept(noexcept(
      std::declval<core &>().update(sst::cbegin(std::forward<Src>(src)),
                                    std::forward<End>(end)))) {
    core::update(sst::cbegin(std::forward<Src>(src)),
                 std::forward<End>(end));
    return *this;
  }

  seq_hash_shell &
  finish() noexcept(noexcept(std::declval<core &>().finish())) {
    core::finish();
    return *this;
  }

  using core::output;

  //--------------------------------------------------------------------

  template<class Src,
           sst::enable_if_t<sst::is_iterable<Src, is_input>::value> = 0>
  seq_hash_shell & update(Src && src) noexcept(noexcept(
      std::declval<seq_hash_shell &>().update(sst::cbegin(src),
                                              sst::cend(src)))) {
    return update(sst::cbegin(src), sst::cend(src));
  }

  template<class Src,
           sst::enable_if_t<
               sst::is_input_iterator<Src, is_input>::value> = 0>
  seq_hash_shell & update(Src && src) noexcept(
      noexcept(std::declval<seq_hash_shell &>().update(
          std::forward<Src>(src),
          sst::value_sentinel(sst::value_type_t<Src>())))) {
    return update(std::forward<Src>(src),
                  sst::value_sentinel(sst::value_type_t<Src>()));
  }

  //--------------------------------------------------------------------

  template<class... Args>
  output_t const & operator()(Args &&... args) const & {
    init();
    update(std::forward<Args>(args)...);
    finish();
    return output();
  }

  template<class... Args>
  output_t && operator()(Args &&... args) && {
    init();
    update(std::forward<Args>(args)...);
    finish();
    return std::move(*this).output();
  }

  //--------------------------------------------------------------------
};

} // namespace sst

#endif // SST_CATALOG_SEQ_HASH_SHELL_HPP
