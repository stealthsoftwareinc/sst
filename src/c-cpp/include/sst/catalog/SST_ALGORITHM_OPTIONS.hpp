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

#ifndef SST_CATALOG_SST_ALGORITHM_OPTIONS_HPP
#define SST_CATALOG_SST_ALGORITHM_OPTIONS_HPP

#include <cstddef>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/SST_COMPILES.hpp>
#include <sst/catalog/SST_CONSTEXPR_ASSERT.hpp>
#include <sst/catalog/SST_DISPATCH.h>
#include <sst/catalog/SST_EXPAND.h>
#include <sst/catalog/SST_LISTIFY.h>
#include <sst/catalog/SST_NODISCARD.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/monostate.hpp>

//----------------------------------------------------------------------

#define SST_ALGORITHM_OPTIONS_DECL_required(NAME, TYPE, DEFAULT_VALUE) \
                                                                       \
  template<class SST_B = SST_Base,                                     \
           ::sst::enable_if_t<SST_B::has_compile_time_##NAME()> = 0>   \
  SST_NODISCARD()                                                      \
  static constexpr auto NAME()->decltype(SST_B::NAME()) {              \
    return SST_B::NAME();                                              \
  }                                                                    \
                                                                       \
  template<class SST_B = SST_Base,                                     \
           ::sst::enable_if_t<!SST_B::has_compile_time_##NAME()> = 0>  \
  SST_NODISCARD()                                                      \
  auto NAME() const->decltype(SST_B::NAME()) {                         \
    return SST_B::NAME();                                              \
  }                                                                    \
                                                                       \
  template<SST_EXPAND TYPE SST_Value = (DEFAULT_VALUE)>                \
  struct SST_add_ct_##NAME : SST_Base {                                \
                                                                       \
    SST_add_ct_##NAME() : SST_Base() {}                                \
                                                                       \
    explicit SST_add_ct_##NAME(SST_Base const & base)                  \
        : SST_Base(base) {}                                            \
                                                                       \
    SST_NODISCARD()                                                    \
    static constexpr bool has_compile_time_##NAME() noexcept {         \
      return true;                                                     \
    }                                                                  \
                                                                       \
    SST_NODISCARD() static constexpr SST_EXPAND TYPE NAME() {          \
      return SST_Value;                                                \
    }                                                                  \
                                                                       \
  }; /**/                                                              \
                                                                       \
  SST_NODISCARD()                                                      \
  SST_options<SST_add_ct_##NAME<>> SST_init_##NAME() const {           \
    return SST_options<SST_add_ct_##NAME<>>(*this);                    \
  }                                                                    \
                                                                       \
  template<SST_EXPAND TYPE SST_Value>                                  \
  SST_NODISCARD()                                                      \
  SST_options<SST_add_ct_##NAME<SST_Value>> NAME() const {             \
    return SST_options<SST_add_ct_##NAME<SST_Value>>(*this);           \
  }                                                                    \
                                                                       \
  struct SST_add_rt_##NAME : SST_Base {                                \
                                                                       \
    SST_add_rt_##NAME()                                                \
        : SST_Base(),                                                  \
          SST_val_##NAME((DEFAULT_VALUE)) {}                           \
                                                                       \
    explicit SST_add_rt_##NAME(                                        \
        SST_Base const & base,                                         \
        SST_EXPAND TYPE const value = (DEFAULT_VALUE))                 \
        : SST_Base(base),                                              \
          SST_val_##NAME(value) {}                                     \
                                                                       \
    SST_NODISCARD()                                                    \
    static constexpr bool has_compile_time_##NAME() noexcept {         \
      return false;                                                    \
    }                                                                  \
                                                                       \
    SST_NODISCARD() SST_EXPAND TYPE NAME() const {                     \
      return SST_val_##NAME;                                           \
    }                                                                  \
                                                                       \
  protected:                                                           \
                                                                       \
    SST_EXPAND TYPE SST_val_##NAME;                                    \
                                                                       \
  }; /**/                                                              \
                                                                       \
  struct SST_collider_##NAME {                                         \
    int SST_val_##NAME;                                                \
  };                                                                   \
                                                                       \
  template<class SST_B>                                                \
  struct SST_has_rt_##NAME : SST_B, SST_collider_##NAME {              \
    template<class SST_T = SST_has_rt_##NAME,                          \
             class = decltype(SST_T::SST_val_##NAME)>                  \
    static constexpr bool value_helper(int) {                          \
      return false;                                                    \
    }                                                                  \
    static constexpr bool value_helper(long) { return true; }          \
    static constexpr bool value = value_helper(0);                     \
  };                                                                   \
                                                                       \
  template<class SST_B = SST_Base,                                     \
           ::sst::enable_if_t<!SST_has_rt_##NAME<SST_B>::value> = 0>   \
  SST_NODISCARD()                                                      \
  SST_options<SST_add_rt_##NAME> NAME(SST_EXPAND TYPE const value)     \
      const {                                                          \
    return SST_options<SST_add_rt_##NAME>(*this, value);               \
  }                                                                    \
                                                                       \
  template<class SST_B = SST_Base,                                     \
           ::sst::enable_if_t<SST_has_rt_##NAME<SST_B>::value> = 0>    \
  SST_NODISCARD()                                                      \
  SST_options NAME(SST_EXPAND TYPE const value) const {                \
    auto x = *this;                                                    \
    x.SST_val_##NAME = value;                                          \
    return x;                                                          \
  }

//----------------------------------------------------------------------

#define SST_DEFINE_optional_ALG_OPTION(NAME,                           \
                                       TYPE,                           \
                                       DEFAULT_HAVE,                   \
                                       DEFAULT_VALUE)                  \
                                                                       \
  template<class SST_B = SST_Base,                                     \
           ::sst::enable_if_t<SST_B::has_compile_time_##NAME()> = 0>   \
  SST_NODISCARD()                                                      \
  static constexpr auto NAME()->decltype(SST_B::NAME()) {              \
    return SST_B::NAME();                                              \
  }                                                                    \
                                                                       \
  template<class SST_B = SST_Base,                                     \
           ::sst::enable_if_t<!SST_B::has_compile_time_##NAME()> = 0>  \
  SST_NODISCARD()                                                      \
  auto NAME() const->decltype(SST_B::NAME()) {                         \
    return SST_B::NAME();                                              \
  }                                                                    \
                                                                       \
  template<bool SST_Have = (DEFAULT_HAVE),                             \
           SST_EXPAND TYPE SST_Value = (DEFAULT_VALUE)>                \
  struct SST_add_ct_##NAME : SST_Base {                                \
                                                                       \
    SST_add_ct_##NAME() : SST_Base() {}                                \
                                                                       \
    explicit SST_add_ct_##NAME(SST_Base const & base)                  \
        : SST_Base(base) {}                                            \
                                                                       \
    SST_NODISCARD()                                                    \
    static constexpr bool has_compile_time_##NAME() noexcept {         \
      return true;                                                     \
    }                                                                  \
                                                                       \
    SST_NODISCARD() static constexpr bool has_##NAME() {               \
      return SST_Have;                                                 \
    }                                                                  \
                                                                       \
    SST_NODISCARD() static constexpr SST_EXPAND TYPE NAME() {          \
      SST_CONSTEXPR_ASSERT((has_##NAME()));                            \
      return SST_Value;                                                \
    }                                                                  \
                                                                       \
  }; /**/                                                              \
                                                                       \
  SST_NODISCARD()                                                      \
  SST_options<SST_add_ct_##NAME<>> SST_init_##NAME() const {           \
    return SST_options<SST_add_ct_##NAME<>>(*this);                    \
  }                                                                    \
                                                                       \
  template<::std::nullptr_t>                                           \
  SST_NODISCARD()                                                      \
  SST_options<SST_add_ct_##NAME<false>> NAME() const {                 \
    return SST_options<SST_add_ct_##NAME<false>>(*this);               \
  }                                                                    \
                                                                       \
  template<SST_EXPAND TYPE SST_Value>                                  \
  SST_NODISCARD()                                                      \
  SST_options<SST_add_ct_##NAME<true, SST_Value>> NAME() const {       \
    return SST_options<SST_add_ct_##NAME<true, SST_Value>>(*this);     \
  }                                                                    \
                                                                       \
  struct SST_add_rt_##NAME : SST_Base {                                \
                                                                       \
    SST_add_rt_##NAME()                                                \
        : SST_Base(),                                                  \
          SST_has_##NAME((DEFAULT_HAVE)),                              \
          SST_val_##NAME((DEFAULT_VALUE)) {}                           \
                                                                       \
    explicit SST_add_rt_##NAME(                                        \
        SST_Base const & base,                                         \
        bool const have = (DEFAULT_HAVE),                              \
        SST_EXPAND TYPE const value = (DEFAULT_VALUE))                 \
        : SST_Base(base),                                              \
          SST_has_##NAME(have),                                        \
          SST_val_##NAME(value) {}                                     \
                                                                       \
    SST_NODISCARD()                                                    \
    static constexpr bool has_compile_time_##NAME() noexcept {         \
      return false;                                                    \
    }                                                                  \
                                                                       \
    SST_NODISCARD() bool has_##NAME() const { return SST_has_##NAME; } \
                                                                       \
    SST_NODISCARD() SST_EXPAND TYPE NAME() const {                     \
      SST_ASSERT((has_##NAME()));                                      \
      return SST_val_##NAME;                                           \
    }                                                                  \
                                                                       \
  protected:                                                           \
                                                                       \
    bool SST_has_##NAME;                                               \
    SST_EXPAND TYPE SST_val_##NAME;                                    \
                                                                       \
  }; /**/                                                              \
                                                                       \
  struct SST_collider_##NAME {                                         \
    int SST_val_##NAME;                                                \
  };                                                                   \
                                                                       \
  template<class SST_B>                                                \
  struct SST_has_rt_##NAME : SST_B, SST_collider_##NAME {              \
    template<class SST_T = SST_has_rt_##NAME,                          \
             class = decltype(SST_T::SST_val_##NAME)>                  \
    static constexpr bool value_helper(int) {                          \
      return false;                                                    \
    }                                                                  \
    static constexpr bool value_helper(long) { return true; }          \
    static constexpr bool value = value_helper(0);                     \
  };                                                                   \
                                                                       \
  template<class SST_B = SST_Base,                                     \
           ::sst::enable_if_t<!SST_has_rt_##NAME<SST_B>::value> = 0>   \
  SST_NODISCARD()                                                      \
  SST_options<SST_add_rt_##NAME> NAME(::std::nullptr_t) const {        \
    return SST_options<SST_add_rt_##NAME>(*this, false);               \
  }                                                                    \
                                                                       \
  template<class SST_B = SST_Base,                                     \
           ::sst::enable_if_t<!SST_has_rt_##NAME<SST_B>::value> = 0>   \
  SST_NODISCARD()                                                      \
  SST_options<SST_add_rt_##NAME> NAME(SST_EXPAND TYPE const value)     \
      const {                                                          \
    return SST_options<SST_add_rt_##NAME>(*this, true, value);         \
  }                                                                    \
                                                                       \
  template<class SST_B = SST_Base,                                     \
           ::sst::enable_if_t<SST_has_rt_##NAME<SST_B>::value> = 0>    \
  SST_NODISCARD()                                                      \
  SST_options NAME(::std::nullptr_t) const {                           \
    auto x = *this;                                                    \
    x.SST_has_##NAME = false;                                          \
    return x;                                                          \
  }                                                                    \
                                                                       \
  template<class SST_B = SST_Base,                                     \
           ::sst::enable_if_t<SST_has_rt_##NAME<SST_B>::value> = 0>    \
  SST_NODISCARD()                                                      \
  SST_options NAME(SST_EXPAND TYPE const value) const {                \
    auto x = *this;                                                    \
    x.SST_has_##NAME = true;                                           \
    x.SST_val_##NAME = value;                                          \
    return x;                                                          \
  }

#define SST_ALGORITHM_OPTIONS_DECL_optional_3(NAME,                    \
                                              TYPE,                    \
                                              DEFAULT_VALUE)           \
  SST_DEFINE_optional_ALG_OPTION(NAME, TYPE, true, DEFAULT_VALUE)

#define SST_ALGORITHM_OPTIONS_DECL_optional_2(NAME, TYPE)              \
  SST_DEFINE_optional_ALG_OPTION(NAME, TYPE, false, (SST_EXPAND TYPE{}))

#define SST_ALGORITHM_OPTIONS_DECL_optional(...)                       \
  SST_DISPATCH(SST_ALGORITHM_OPTIONS_DECL_optional_, __VA_ARGS__)      \
  (__VA_ARGS__)

#define SST_ALGORITHM_OPTIONS_DECL_noop(...)

//----------------------------------------------------------------------

#define SST_ALGORITHM_OPTIONS_INIT_required(NAME, ...)                 \
  .SST_init_##NAME()

#define SST_ALGORITHM_OPTIONS_INIT_optional(NAME, ...)                 \
  .SST_init_##NAME()

#define SST_ALGORITHM_OPTIONS_INIT_noop(...)

//----------------------------------------------------------------------

#define SST_ALGORITHM_OPTIONS_HELPER(NAME, ...)                        \
                                                                       \
  namespace SST_ALGORITHM_OPTIONS_NS_##NAME {                          \
                                                                       \
    template<class SST_Base = ::sst::monostate>                        \
    struct SST_options : SST_Base {                                    \
                                                                       \
      template<class... Args,                                          \
               ::sst::enable_if_t<SST_COMPILES(                        \
                   SST_Base(::std::declval<Args>()...))> = 0>          \
      explicit constexpr SST_options(Args &&... args) noexcept(        \
          noexcept(SST_Base(::std::forward<Args>(args)...)))           \
          : SST_Base(::std::forward<Args>(args)...) {}                 \
                                                                       \
      SST_LISTIFY(SST_ALGORITHM_OPTIONS_DECL_, (), __VA_ARGS__)        \
                                                                       \
    }; /**/                                                            \
                                                                       \
  } /* namespace SST_ALGORITHM_OPTIONS_NS_##NAME */                    \
                                                                       \
  using NAME =                                                         \
      decltype(SST_ALGORITHM_OPTIONS_NS_##NAME::SST_options<>()        \
                   SST_LISTIFY(SST_ALGORITHM_OPTIONS_INIT_,            \
                               (),                                     \
                               __VA_ARGS__));

#define SST_ALGORITHM_OPTIONS(...)                                     \
  SST_ALGORITHM_OPTIONS_HELPER(__VA_ARGS__, noop())

//----------------------------------------------------------------------

#endif // SST_CATALOG_SST_ALGORITHM_OPTIONS_HPP
