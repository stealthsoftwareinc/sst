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

#ifndef SST_CATALOG_SST_BITMASK_CLASS_HPP
#define SST_CATALOG_SST_BITMASK_CLASS_HPP

#include <cstdint>
#include <type_traits>

#include <sst/catalog/SST_STATIC_ASSERT.h>
#include <sst/catalog/bool_constant.hpp>
#include <sst/catalog/if_chain_t.hpp>
#include <sst/catalog/is_integer.hpp>
#include <sst/catalog/ones_mask.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/underlying_type_t.hpp>
#include <sst/catalog/unsigned_le.hpp>
#include <sst/catalog/value_bits.hpp>

#define SST_BITMASK_CLASS_ITEM_1(NAME) e_##NAME,

#define SST_BITMASK_CLASS_ITEM_2(NAME)                                 \
  static constexpr SST_BITMASK_CLASS_NAME NAME() noexcept {            \
    SST_STATIC_ASSERT(                                                 \
        (sst::unsigned_le(static_cast<exponent_type>(e_##NAME),        \
                          sst::value_bits<value_type>::value)));       \
    return static_cast<value_type>(1)                                  \
           << static_cast<exponent_type>(e_##NAME);                    \
  }

#define SST_BITMASK_CLASS_COMBO(NAME, VALUE)                           \
  static constexpr SST_BITMASK_CLASS_NAME NAME() noexcept {            \
    return VALUE;                                                      \
  }

#define SST_BITMASK_CLASS_6(NAME, ITEMS, COMBOS, TYPE, ALL, NONE)      \
                                                                       \
  class NAME {                                                         \
                                                                       \
    using SST_BITMASK_CLASS_NAME = NAME;                               \
                                                                       \
    SST_STATIC_ASSERT(std::is_void<TYPE>::value                        \
                      || sst::is_integer<TYPE>::value);                \
                                                                       \
    enum exponent_enum { ITEMS(SST_BITMASK_CLASS_ITEM_1) e_##ALL };    \
    using exponent_type = sst::underlying_type_t<exponent_enum>;       \
                                                                       \
  public:                                                              \
                                                                       \
    using value_type = sst::if_chain_t<                                \
        sst::bool_constant<!std::is_void<TYPE>::value>,                \
        sst::remove_cvref_t<TYPE>,                                     \
        sst::bool_constant<sst::unsigned_le(                           \
            static_cast<exponent_type>(e_##ALL),                       \
            sst::value_bits<unsigned int>::value)>,                    \
        unsigned int,                                                  \
        sst::bool_constant<sst::unsigned_le(                           \
            static_cast<exponent_type>(e_##ALL),                       \
            sst::value_bits<unsigned long>::value)>,                   \
        unsigned long,                                                 \
        sst::bool_constant<sst::unsigned_le(                           \
            static_cast<exponent_type>(e_##ALL),                       \
            sst::value_bits<unsigned long long>::value)>,              \
        unsigned long long,                                            \
        std::uintmax_t>;                                               \
                                                                       \
  private:                                                             \
                                                                       \
    value_type value_;                                                 \
                                                                       \
    constexpr NAME(value_type const value) noexcept : value_(value) {} \
                                                                       \
  public:                                                              \
                                                                       \
    constexpr value_type value() const noexcept { return value_; }     \
                                                                       \
    static constexpr NAME NONE() noexcept {                            \
      return static_cast<value_type>(0);                               \
    }                                                                  \
                                                                       \
    static constexpr NAME ALL() noexcept {                             \
      return sst::ones_mask<value_type>(                               \
          static_cast<exponent_type>(e_##ALL));                        \
    }                                                                  \
                                                                       \
    ITEMS(SST_BITMASK_CLASS_ITEM_2)                                    \
                                                                       \
    COMBOS(SST_BITMASK_CLASS_COMBO)                                    \
                                                                       \
    friend constexpr bool operator==(NAME const a,                     \
                                     NAME const b) noexcept {          \
      return a.value() == b.value();                                   \
    }                                                                  \
                                                                       \
    friend constexpr bool operator!=(NAME const a,                     \
                                     NAME const b) noexcept {          \
      return a.value() != b.value();                                   \
    }                                                                  \
                                                                       \
    friend constexpr NAME operator&(NAME const a,                      \
                                    NAME const b) noexcept {           \
      return static_cast<value_type>(a.value() & b.value());           \
    }                                                                  \
                                                                       \
    friend constexpr NAME operator|(NAME const a,                      \
                                    NAME const b) noexcept {           \
      return static_cast<value_type>(a.value() | b.value());           \
    }                                                                  \
                                                                       \
    friend constexpr NAME operator^(NAME const a,                      \
                                    NAME const b) noexcept {           \
      return static_cast<value_type>(a.value() ^ b.value());           \
    }                                                                  \
                                                                       \
    NAME & operator&=(NAME const b) noexcept {                         \
      return *this = *this & b;                                        \
    }                                                                  \
                                                                       \
    NAME & operator|=(NAME const b) noexcept {                         \
      return *this = *this | b;                                        \
    }                                                                  \
                                                                       \
    NAME & operator^=(NAME const b) noexcept {                         \
      return *this = *this ^ b;                                        \
    }                                                                  \
                                                                       \
    constexpr operator bool() const noexcept {                         \
      return *this != NONE();                                          \
    }                                                                  \
                                                                       \
    friend constexpr NAME operator~(NAME const a) noexcept {           \
      return a ^ ALL();                                                \
    }                                                                  \
                                                                       \
  }; //

#define SST_BITMASK_CLASS_5(NAME, ITEMS, COMBOS, TYPE, ALL)            \
  SST_BITMASK_CLASS_6(NAME, ITEMS, COMBOS, TYPE, ALL, none)

#define SST_BITMASK_CLASS_4(NAME, ITEMS, COMBOS, TYPE)                 \
  SST_BITMASK_CLASS_5(NAME, ITEMS, COMBOS, TYPE, all)

#define SST_BITMASK_CLASS_3(NAME, ITEMS, COMBOS)                       \
  SST_BITMASK_CLASS_4(NAME, ITEMS, COMBOS, void)

#define SST_BITMASK_CLASS_A7(A0, A1, A2, A3, A4, A5, A6, ...) A6

#define SST_BITMASK_CLASS_DISPATCH(...)                                \
  SST_BITMASK_CLASS_A7(__VA_ARGS__,                                    \
                       SST_BITMASK_CLASS_6,                            \
                       SST_BITMASK_CLASS_5,                            \
                       SST_BITMASK_CLASS_4,                            \
                       SST_BITMASK_CLASS_3,                            \
                       SST_BITMASK_CLASS_2,                            \
                       SST_BITMASK_CLASS_1, )

#define SST_BITMASK_CLASS(...)                                         \
  SST_BITMASK_CLASS_DISPATCH(__VA_ARGS__)(__VA_ARGS__)

#endif // #ifndef SST_CATALOG_SST_BITMASK_CLASS_HPP
