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

#ifndef SST_CATALOG_PROMOTE_WITH_SIGN_HPP
#define SST_CATALOG_PROMOTE_WITH_SIGN_HPP

#include <sst/catalog/promote_unsigned.hpp>
#include <sst/language.h>
#include <type_traits>

namespace sst {

template<class T>
class promote_with_sign {
  SST_STATIC_ASSERT(std::is_integral<T>::value);
  using T1 = typename std::conditional<
      std::is_signed<T>::value,
      decltype(+T()),
      typename promote_unsigned<T>::type>::type;
  using T2 =
      typename std::conditional<std::is_const<T>::value,
                                typename std::add_const<T1>::type,
                                T1>::type;
  using T3 =
      typename std::conditional<std::is_volatile<T>::value,
                                typename std::add_volatile<T2>::type,
                                T2>::type;

public:
  using type = T3;
};

} // namespace sst

#endif // #ifndef SST_CATALOG_PROMOTE_WITH_SIGN_HPP
