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

#ifndef SST_CATALOG_OLD_FROM_BYTES_FUNCTOR_HPP
#define SST_CATALOG_OLD_FROM_BYTES_FUNCTOR_HPP

#include <stdexcept>
#include <type_traits>
#include <utility>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/SST_THROW_UNIMPLEMENTED.hpp>
#include <sst/catalog/buffer_underrun.hpp>
#include <sst/catalog/char_bit_v.hpp>
#include <sst/catalog/checked_cast.hpp>
#include <sst/catalog/checked_overflow.hpp>
#include <sst/catalog/checked_t.hpp>
#include <sst/catalog/enable_if.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/integer_rep.hpp>
#include <sst/catalog/perfect_ge.hpp>
#include <sst/catalog/perfect_gt.hpp>
#include <sst/catalog/remove_cvref.hpp>
#include <sst/catalog/type_max.hpp>
#include <sst/catalog/uchar_msb_v.hpp>
#include <sst/catalog/unsigned_gt.hpp>
#include <sst/catalog/value_bits.hpp>

namespace sst {
namespace old {

//----------------------------------------------------------------------

template<class, class = sst::enable_t>
class from_bytes_functor;

//----------------------------------------------------------------------
// Fundamental integer types
//----------------------------------------------------------------------

// TODO: Allow overflow checking to be disabled and byte order to be
// chosen. Perhaps see fromBytes() in Rep.java.m4, which may have more
// fleshed out code.

template<class T1>
class from_bytes_functor<
    T1,
    typename sst::enable_if<std::is_integral<
        typename sst::remove_cvref<T1>::type>::value>::type> {

  using T = typename sst::remove_cvref<T1>::type;

  // Parse [src,src+size) or [src,end), updating src.
  template<class ByteIt,
           class SizeOrByteIt,
           class Function1,
           class Function2>
  T private_from_bytes(ByteIt & src,
                       SizeOrByteIt size_or_end,
                       Function1 && step,
                       Function2 && last,
                       sst::integer_rep const rep =
                           sst::integer_rep::twos_complement()) {
    constexpr T vbits = sst::value_bits<T>::value;
    constexpr T max = sst::type_max<T>::value;
    switch (rep) {
      case sst::integer_rep::twos_complement(): {
        sst::checked_t<T> dst = 0;
        T k = 0;
        T dst_a = 0;
        T dst_b = 0;
        bool a_overflow = false;
        bool b_overflow = false;
        while (step(src, size_or_end)) {
          unsigned char const digit = *src++;
          if (!a_overflow) {
            unsigned char const d = digit;
            if (d != 0) {
              if (k >= vbits || sst::unsigned_gt(d, max >> k)) {
                a_overflow = true;
              } else {
                dst_a += static_cast<T>(d) << k;
              }
            }
          }
          bool const top = last(src, size_or_end);
          unsigned int const msb = top ? digit & sst::uchar_msb_v : 0;
          if (!b_overflow) {
            unsigned char const d = static_cast<unsigned char>(
                ~static_cast<unsigned int>(digit) & ~msb);
            if (d != 0) {
              if (k >= vbits || sst::unsigned_gt(d, max >> k)) {
                b_overflow = true;
              } else {
                dst_b += static_cast<T>(d) << k;
              }
            }
          }
          if (top) {
            if (msb) {
              if (b_overflow) {
                throw sst::checked_overflow(
                    "sst::old::from_bytes<std::integral>: overflow");
              }
              dst = dst_b;
              dst = -dst;
              --dst;
            } else {
              if (a_overflow) {
                throw sst::checked_overflow(
                    "sst::old::from_bytes<std::integral>: overflow");
              }
              dst = dst_a;
            }
          }
          if (k < vbits) {
            k += T(sst::char_bit_v);
          }
        }
        return dst.value();
      } break;
      case sst::integer_rep::pure_unsigned(): {
        sst::checked_t<T> dst = 0;
        T k = 0;
        while (step(src, size_or_end)) {
          unsigned char const digit = *src++;
          if (digit != 0) {
            dst += sst::checked_cast<T>(digit) << k;
          }
          if (k < vbits) {
            k += T(sst::char_bit_v);
          }
        }
        return dst.value();
      } break;
      default: {
        SST_THROW_UNIMPLEMENTED();
      } break;
    }
  }

public:
  // Parse [*src,*src+size), updating *src.
  template<
      class ByteIt,
      class Size,
      typename sst::enable_if<
          std::is_same<typename sst::remove_cvref<
                           decltype(*std::declval<ByteIt>())>::type,
                       unsigned char>::value
          && std::is_integral<
              typename sst::remove_cvref<Size>::type>::value>::type = 0>
  T operator()(ByteIt * const src,
               Size const size,
               sst::integer_rep const rep =
                   sst::integer_rep::twos_complement()) {
    SST_ASSERT(src != nullptr);
    SST_ASSERT(sst::perfect_gt(size, 0));
    return private_from_bytes(
        *src,
        size,
        [](ByteIt, Size & size) {
          return size == 0 ? false : (--size, true);
        },
        [](ByteIt, Size const size) { return size == 0; },
        rep);
  }

  // Parse [*src,*src+size), updating *src. Also update avail, detecting
  // underrun.
  template<
      class ByteIt,
      class Size,
      class Avail,
      typename sst::enable_if<
          std::is_same<typename sst::remove_cvref<
                           decltype(*std::declval<ByteIt>())>::type,
                       unsigned char>::value
          && std::is_integral<
              typename sst::remove_cvref<Size>::type>::value>::type = 0>
  T operator()(ByteIt * const src,
               Size const size,
               Avail & avail,
               sst::integer_rep const rep =
                   sst::integer_rep::twos_complement()) {
    SST_ASSERT(src != nullptr);
    SST_ASSERT(sst::perfect_gt(size, 0));
    SST_ASSERT(sst::perfect_ge(avail, 0));
    if (sst::unsigned_gt(size, avail)) {
      throw sst::buffer_underrun(
          "sst::old::from_bytes: buffer underrun");
    }
    auto v = operator()(src, size, rep);
    avail -= static_cast<Avail>(size);
    return v;
  }

  // Parse [src,src+size).
  template<
      class ByteIt,
      class Size,
      typename sst::enable_if<
          std::is_same<typename sst::remove_cvref<
                           decltype(*std::declval<ByteIt>())>::type,
                       unsigned char>::value
          && std::is_integral<
              typename sst::remove_cvref<Size>::type>::value>::type = 0>
  T operator()(ByteIt src,
               Size const size,
               sst::integer_rep const rep =
                   sst::integer_rep::twos_complement()) {
    SST_ASSERT(sst::perfect_gt(size, 0));
    return operator()(&src, size, rep);
  }

  // Parse [src,src+size). Also update avail, detecting underrun.
  template<
      class ByteIt,
      class Size,
      class Avail,
      typename sst::enable_if<
          std::is_same<typename sst::remove_cvref<
                           decltype(*std::declval<ByteIt>())>::type,
                       unsigned char>::value
          && std::is_integral<
              typename sst::remove_cvref<Size>::type>::value>::type = 0>
  T operator()(ByteIt src,
               Size const size,
               Avail & avail,
               sst::integer_rep const rep =
                   sst::integer_rep::twos_complement()) {
    SST_ASSERT(sst::perfect_gt(size, 0));
    SST_ASSERT(sst::perfect_ge(avail, 0));
    return operator()(&src, size, avail, rep);
  }
};

//----------------------------------------------------------------------

} // namespace old
} // namespace sst

#endif // SST_CATALOG_OLD_FROM_BYTES_FUNCTOR_HPP
