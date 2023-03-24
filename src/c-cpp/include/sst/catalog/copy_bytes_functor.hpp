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

#ifndef SST_CATALOG_COPY_BYTES_FUNCTOR_HPP
#define SST_CATALOG_COPY_BYTES_FUNCTOR_HPP

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/SST_THROW_UNIMPLEMENTED.hpp>
#include <sst/catalog/buffer_underrun.hpp>
#include <sst/catalog/char_bit_v.hpp>
#include <sst/catalog/checked_t.hpp>
#include <sst/catalog/checked_cast.hpp>
#include <sst/catalog/enable_if.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/perfect_ge.hpp>
#include <sst/catalog/perfect_gt.hpp>
#include <sst/catalog/remove_cvref.hpp>
#include <sst/catalog/type_max.hpp>
#include <sst/catalog/unsigned_gt.hpp>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace sst {

//----------------------------------------------------------------------

class copy_bytes_functor;

//----------------------------------------------------------------------

class copy_bytes_functor {

  // Copy [src,src+size) or [src,end) to dst, updating src and returning
  // the updated dst.
  template<class ByteIt,
           class SizeOrByteIt,
           class ByteIt2,
           class Function>
  ByteIt2 private_copy_bytes(ByteIt & src,
                             SizeOrByteIt size_or_end,
                             ByteIt2 dst,
                             Function && step) {
    while (step(src, size_or_end)) {
      // TODO: Should this be using static_cast to prevent warnings for,
      //       e.g., long -> int? Or should it be doing something to
      //       reject those cases?
      *dst++ = *src++;
    }
    return dst;
  }

public:
  // Copy [*src,*src+size) to dst, updating *src and returning the
  // updated dst.
  template<class ByteIt,
           class Size,
           class ByteIt2,
           typename sst::enable_if<
               std::is_same<typename sst::remove_cvref<decltype(
                                *std::declval<ByteIt>())>::type,
                            unsigned char>::value
               && std::is_integral<typename sst::remove_cvref<
                   Size>::type>::value>::type = 0>
  ByteIt2
  operator()(ByteIt * const src, Size const size, ByteIt2 const dst) {
    SST_ASSERT(src != nullptr);
    SST_ASSERT(sst::perfect_ge(size, 0));
    return private_copy_bytes(*src, size, dst, [](ByteIt, Size & size) {
      return size != 0 ? (--size, true) : false;
    });
  }

  // Copy [*src,*src+size) to dst, updating *src and returning the
  // updated dst. Also update avail, detecting underrun.
  template<class ByteIt,
           class Size,
           class Avail,
           class ByteIt2,
           typename sst::enable_if<
               std::is_same<typename sst::remove_cvref<decltype(
                                *std::declval<ByteIt>())>::type,
                            unsigned char>::value
               && std::is_integral<typename sst::remove_cvref<
                   Size>::type>::value>::type = 0>
  ByteIt2 operator()(ByteIt * const src,
                     Size const size,
                     Avail & avail,
                     ByteIt2 dst) {
    SST_ASSERT(src != nullptr);
    SST_ASSERT(sst::perfect_ge(size, 0));
    SST_ASSERT(sst::perfect_ge(avail, 0));
    if (sst::unsigned_gt(size, avail)) {
      throw sst::buffer_underrun("sst::copy_bytes: buffer underrun");
    }
    dst = operator()(src, size, dst);
    avail -= static_cast<Avail>(size);
    return dst;
  }

  // Copy [src,src+size) to dst, returning the updated dst.
  template<class ByteIt,
           class Size,
           class ByteIt2,
           typename sst::enable_if<
               std::is_same<typename sst::remove_cvref<decltype(
                                *std::declval<ByteIt>())>::type,
                            unsigned char>::value
               && std::is_integral<typename sst::remove_cvref<
                   Size>::type>::value>::type = 0>
  ByteIt2 operator()(ByteIt src, Size const size, ByteIt2 const dst) {
    SST_ASSERT(sst::perfect_ge(size, 0));
    return operator()(&src, size, dst);
  }

  // Copy [src,src+size) to dst, returning the updated dst. Also update
  // avail, detecting underrun.
  template<class ByteIt,
           class Size,
           class Avail,
           class ByteIt2,
           typename sst::enable_if<
               std::is_same<typename sst::remove_cvref<decltype(
                                *std::declval<ByteIt>())>::type,
                            unsigned char>::value
               && std::is_integral<typename sst::remove_cvref<
                   Size>::type>::value>::type = 0>
  ByteIt2 operator()(ByteIt src,
                     Size const size,
                     Avail & avail,
                     ByteIt2 const dst) {
    SST_ASSERT(sst::perfect_ge(size, 0));
    SST_ASSERT(sst::perfect_ge(avail, 0));
    return operator()(&src, size, dst, avail);
  }
};

//----------------------------------------------------------------------

} // namespace sst

#endif // #ifndef SST_CATALOG_COPY_BYTES_FUNCTOR_HPP
