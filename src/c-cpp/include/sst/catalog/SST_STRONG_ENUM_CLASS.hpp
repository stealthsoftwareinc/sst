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

#ifndef SST_CATALOG_SST_STRONG_ENUM_CLASS_HPP
#define SST_CATALOG_SST_STRONG_ENUM_CLASS_HPP

//
// TODO: Support serialize() and deserialize() via friend function ADL.
//       (What about non ADL? Haven't thought much about interface
//       conventions for that yet.)
//

#include <stdexcept>

#include <sst/catalog/SST_CONSTEXPR_ASSERT.hpp>
#include <sst/catalog/SST_CPP14_CONSTEXPR.hpp>
#include <sst/catalog/SST_DISPATCH.h>
#include <sst/catalog/SST_LISTIFY.h>
#include <sst/catalog/SST_REVERSE.h>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/json/exception.hpp>
#include <sst/catalog/json/get_as.hpp>
#include <sst/catalog/json/is_nlohmann.hpp>
#include <sst/catalog/monostate.hpp>
#include <sst/catalog/size.hpp>
#include <sst/catalog/underlying_type_t.hpp>
#include <sst/catalog/unsigned_ge.hpp>
#include <sst/catalog/unsigned_lt.hpp>

//----------------------------------------------------------------------

#define SST_STRONG_ENUM_CLASS_TYPE_type(T) , T

#define SST_STRONG_ENUM_CLASS_TYPE_member(...)

//----------------------------------------------------------------------

#define SST_STRONG_ENUM_CLASS_A_type(...)

#define SST_STRONG_ENUM_CLASS_A_member_1(NAME) NAME,

#define SST_STRONG_ENUM_CLASS_A_member_2(NAME, VALUE) NAME = (VALUE),

#define SST_STRONG_ENUM_CLASS_A_member(...)                            \
  SST_DISPATCH(SST_STRONG_ENUM_CLASS_A_member_, __VA_ARGS__)           \
  (__VA_ARGS__)

//----------------------------------------------------------------------

#define SST_STRONG_ENUM_CLASS_B_type(...)

#define SST_STRONG_ENUM_CLASS_B_member_1(NAME)                         \
  static constexpr SST_class NAME() noexcept {                         \
    return SST_class(SST_enum::NAME);                                  \
  }

#define SST_STRONG_ENUM_CLASS_B_member_2(NAME, VALUE)                  \
  SST_STRONG_ENUM_CLASS_B_member_1(NAME)

#define SST_STRONG_ENUM_CLASS_B_member(...)                            \
  SST_DISPATCH(SST_STRONG_ENUM_CLASS_B_member_, __VA_ARGS__)           \
  (__VA_ARGS__)

//----------------------------------------------------------------------

#define SST_STRONG_ENUM_CLASS_C_type(...)

#define SST_STRONG_ENUM_CLASS_C_member_1(NAME) #NAME,

#define SST_STRONG_ENUM_CLASS_C_member_2(NAME, VALUE)                  \
  SST_STRONG_ENUM_CLASS_C_member_1(NAME)

#define SST_STRONG_ENUM_CLASS_C_member(...)                            \
  SST_DISPATCH(SST_STRONG_ENUM_CLASS_C_member_, __VA_ARGS__)           \
  (__VA_ARGS__)

//----------------------------------------------------------------------

#define SST_STRONG_ENUM_CLASS_D_type(...)

#define SST_STRONG_ENUM_CLASS_D_member_1(NAME) , SST_enum::NAME

#define SST_STRONG_ENUM_CLASS_D_member_2(NAME, VALUE)                  \
  SST_STRONG_ENUM_CLASS_D_member_1(NAME)

#define SST_STRONG_ENUM_CLASS_D_member(...)                            \
  SST_DISPATCH(SST_STRONG_ENUM_CLASS_D_member_, __VA_ARGS__)           \
  (__VA_ARGS__)

//----------------------------------------------------------------------

#define SST_STRONG_ENUM_CLASS_NLOHMANN_type(...)

#define SST_STRONG_ENUM_CLASS_NLOHMANN_member_1(NAME)                  \
  if (SST_x == #NAME) {                                                \
    SST_dst = NAME();                                                  \
    return;                                                            \
  }

#define SST_STRONG_ENUM_CLASS_NLOHMANN_member_2(NAME, VALUE)           \
  SST_STRONG_ENUM_CLASS_NLOHMANN_member_1(NAME)

#define SST_STRONG_ENUM_CLASS_NLOHMANN_member(...)                     \
  SST_DISPATCH(SST_STRONG_ENUM_CLASS_NLOHMANN_member_, __VA_ARGS__)    \
  (__VA_ARGS__)

//----------------------------------------------------------------------

#define SST_STRONG_ENUM_CLASS_VALUE_CTOR_member_1(name)                \
  case static_cast<value_type>(SST_enum::name):                        \
    SST_value_ = SST_enum::name;                                       \
    break;

#define SST_STRONG_ENUM_CLASS_VALUE_CTOR_member_2(name, value)         \
  SST_STRONG_ENUM_CLASS_VALUE_CTOR_member_1(name)

#define SST_STRONG_ENUM_CLASS_VALUE_CTOR_member(...)                   \
  SST_DISPATCH(SST_STRONG_ENUM_CLASS_VALUE_CTOR_member_, __VA_ARGS__)  \
  (__VA_ARGS__)

#define SST_STRONG_ENUM_CLASS_VALUE_CTOR_type(...)

//----------------------------------------------------------------------

#define SST_STRONG_ENUM_CLASS(NAME, ...)                               \
                                                                       \
  class NAME {                                                         \
                                                                       \
    using SST_class = NAME;                                            \
                                                                       \
    template<class, class T, class...>                                 \
    using SST_second_type = T;                                         \
                                                                       \
    /* Note that the default type of a scoped enum is always int. */   \
    /* This is different than an unscoped enum. */                     \
    enum class SST_enum : SST_second_type<                             \
        void SST_LISTIFY(SST_STRONG_ENUM_CLASS_TYPE_,                  \
                         (),                                           \
                         SST_REVERSE(__VA_ARGS__)),                    \
        int>{SST_LISTIFY(SST_STRONG_ENUM_CLASS_A_, (), __VA_ARGS__)};  \
                                                                       \
    SST_enum SST_value_;                                               \
                                                                       \
    explicit constexpr NAME(SST_enum const SST_value) noexcept         \
        : SST_value_(SST_value) {}                                     \
                                                                       \
    template<class... SST_Args>                                        \
    explicit constexpr NAME(::sst::monostate,                          \
                            SST_enum const SST_value,                  \
                            SST_Args &&...) noexcept                   \
        : NAME(SST_value) {}                                           \
                                                                       \
  public:                                                              \
                                                                       \
    constexpr NAME() noexcept                                          \
        : NAME(::sst::monostate()                                      \
                   SST_LISTIFY(SST_STRONG_ENUM_CLASS_D_,               \
                               (),                                     \
                               __VA_ARGS__)) {}                        \
                                                                       \
    SST_LISTIFY(SST_STRONG_ENUM_CLASS_B_, (), __VA_ARGS__);            \
                                                                       \
    /*--------------------------------------------------------------*/ \
    /* Underlying value conversions                                 */ \
    /*--------------------------------------------------------------*/ \
                                                                       \
  public:                                                              \
                                                                       \
    using value_type = ::sst::underlying_type_t<SST_enum>;             \
                                                                       \
    explicit constexpr NAME(value_type const SST_value) : NAME() {     \
      switch (SST_value) {                                             \
        SST_LISTIFY(SST_STRONG_ENUM_CLASS_VALUE_CTOR_,                 \
                    (),                                                \
                    __VA_ARGS__)                                       \
        default:                                                       \
          throw ::std::runtime_error("Invalid underlying enum value"); \
      }                                                                \
    }                                                                  \
                                                                       \
    constexpr value_type value() const noexcept {                      \
      return static_cast<value_type>(SST_value_);                      \
    }                                                                  \
                                                                       \
    explicit constexpr operator value_type() const noexcept {          \
      return value();                                                  \
    }                                                                  \
                                                                       \
    /*--------------------------------------------------------------*/ \
                                                                       \
  public:                                                              \
                                                                       \
    SST_CPP14_CONSTEXPR char const * name() const noexcept {           \
      char const * const names[] = {                                   \
          SST_LISTIFY(SST_STRONG_ENUM_CLASS_C_, (), __VA_ARGS__)};     \
      auto const i = static_cast<value_type>(SST_value_);              \
      SST_CONSTEXPR_ASSERT(::sst::unsigned_ge(i, 0));                  \
      SST_CONSTEXPR_ASSERT(::sst::unsigned_lt(i, ::sst::size(names))); \
      return names[i];                                                 \
    }                                                                  \
                                                                       \
    /*--------------------------------------------------------------*/ \
    /* Switch statement support                                     */ \
    /*--------------------------------------------------------------*/ \
                                                                       \
  public:                                                              \
                                                                       \
    constexpr operator SST_enum() const noexcept {                     \
      return SST_value_;                                               \
    }                                                                  \
                                                                       \
    /*--------------------------------------------------------------*/ \
    /* Comparison operators                                         */ \
    /*--------------------------------------------------------------*/ \
                                                                       \
  private:                                                             \
                                                                       \
    constexpr int compare(NAME const b) const noexcept {               \
      return this->SST_value_ < b.SST_value_ ? -1 :                    \
             this->SST_value_ > b.SST_value_ ? 1 :                     \
                                               0;                      \
    }                                                                  \
                                                                       \
  public:                                                              \
                                                                       \
    friend constexpr bool operator<(NAME const a,                      \
                                    NAME const b) noexcept {           \
      return a.compare(b) < 0;                                         \
    }                                                                  \
                                                                       \
    friend constexpr bool operator>(NAME const a,                      \
                                    NAME const b) noexcept {           \
      return a.compare(b) > 0;                                         \
    }                                                                  \
                                                                       \
    friend constexpr bool operator<=(NAME const a,                     \
                                     NAME const b) noexcept {          \
      return a.compare(b) <= 0;                                        \
    }                                                                  \
                                                                       \
    friend constexpr bool operator>=(NAME const a,                     \
                                     NAME const b) noexcept {          \
      return a.compare(b) >= 0;                                        \
    }                                                                  \
                                                                       \
    friend constexpr bool operator==(NAME const a,                     \
                                     NAME const b) noexcept {          \
      return a.compare(b) == 0;                                        \
    }                                                                  \
                                                                       \
    friend constexpr bool operator!=(NAME const a,                     \
                                     NAME const b) noexcept {          \
      return a.compare(b) != 0;                                        \
    }                                                                  \
                                                                       \
    /*--------------------------------------------------------------*/ \
    /* nlohmann::json conversions                                   */ \
    /*--------------------------------------------------------------*/ \
                                                                       \
  public:                                                              \
                                                                       \
    template<class SST_Json,                                           \
             ::sst::enable_if_t<                                       \
                 ::sst::json::is_nlohmann<SST_Json>::value> = 0>       \
    friend void to_json(SST_Json & SST_dst, NAME const SST_src) {      \
      SST_dst = SST_src.name();                                        \
    }                                                                  \
                                                                       \
    template<class SST_Json,                                           \
             ::sst::enable_if_t<                                       \
                 ::sst::json::is_nlohmann<SST_Json>::value> = 0>       \
    friend void from_json(SST_Json const & SST_src, NAME & SST_dst) {  \
      /* TODO: Eliminate the intermediate std::string. */              \
      /* TODO: Use a compile-time hash table. */                       \
      ::std::string const SST_x =                                      \
          ::sst::json::get_as<::std::string>(SST_src);                 \
      SST_LISTIFY(SST_STRONG_ENUM_CLASS_NLOHMANN_, (), __VA_ARGS__)    \
      throw ::sst::json::exception::invalid_value();                   \
    }                                                                  \
                                                                       \
    /*--------------------------------------------------------------*/ \
  };

//----------------------------------------------------------------------
// Compile-time tests
//----------------------------------------------------------------------

#include <sst/catalog/SST_COMPILE_TIME_TESTS.h>

#if SST_COMPILE_TIME_TESTS

#include <type_traits>

#include <sst/catalog/SST_STATIC_ASSERT.h>

namespace sst {
namespace guts {
namespace SST_STRONG_ENUM_CLASS {

SST_STRONG_ENUM_CLASS(test1, member(x), member(y, 3), member(z))
SST_STATIC_ASSERT((std::is_same<test1::value_type, int>::value));
SST_STATIC_ASSERT((test1() == test1::x()));
SST_STATIC_ASSERT((test1::x().value() == 0));
SST_STATIC_ASSERT((test1::y().value() == 3));
SST_STATIC_ASSERT((test1::z().value() == 4));

SST_STRONG_ENUM_CLASS(test2, type(long), member(x), type(long long))
SST_STATIC_ASSERT((std::is_same<test2::value_type, long long>::value));

} // namespace SST_STRONG_ENUM_CLASS
} // namespace guts
} // namespace sst

#endif // #if SST_COMPILE_TIME_TESTS

//----------------------------------------------------------------------

#endif // SST_CATALOG_SST_STRONG_ENUM_CLASS_HPP
