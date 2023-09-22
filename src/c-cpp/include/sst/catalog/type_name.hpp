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

#ifndef SST_CATALOG_TYPE_NAME_HPP
#define SST_CATALOG_TYPE_NAME_HPP

#include <cstdlib>
#include <iterator>
#include <string>
#include <typeinfo>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_output_iterator.hpp>
#include <sst/catalog/remove_cvref_t.hpp>

// TODO: Use a ./configure feature test instead of bare __GLIBCXX__?
#if __GLIBCXX__
#include <cxxabi.h>
#endif

namespace sst {

namespace guts {
namespace type_name {

template<class Dst>
void copy(char const * p, Dst & dst) {
  SST_ASSERT((p != nullptr));
  for (; *p != '\0'; ++p) {
    *dst = *p;
    ++dst;
  }
}

} // namespace type_name
} // namespace guts

template<
    class T,
    class Dst,
    sst::enable_if_t<sst::is_output_iterator<Dst, char>::value> = 0>
Dst type_name(Dst dst) {
  char const * const n1 = typeid(T).name();
#if __GLIBCXX__
  int s;
  char * const n2 = abi::__cxa_demangle(n1, nullptr, nullptr, &s);
  if (n2 == nullptr) {
    guts::type_name::copy(n1, dst);
  } else {
    try {
      guts::type_name::copy(n2, dst);
    } catch (...) {
      std::free(n2);
      throw;
    }
    std::free(n2);
  }
#else
  guts::type_name::copy(n1, dst);
#endif
  return dst;
}

template<class T,
         class Dst_ = std::string,
         class Dst = sst::remove_cvref_t<Dst_>>
Dst type_name() {
  Dst dst;
  sst::type_name<T>(std::back_inserter(dst));
  return dst;
}

} // namespace sst

#endif // SST_CATALOG_TYPE_NAME_HPP
