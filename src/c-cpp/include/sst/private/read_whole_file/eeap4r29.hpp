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

#ifndef SST_PRIVATE_READ_WHOLE_FILE_EEAP4R29_HPP
#define SST_PRIVATE_READ_WHOLE_FILE_EEAP4R29_HPP

#include <cstdio>
#include <stdexcept>
#include <type_traits>
#include <utility>

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/c_quote.hpp>
#include <sst/catalog/c_str.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_output_iterator.hpp>
#include <sst/catalog/read_whole_file.hpp>
#include <sst/catalog/read_whole_file_functor.hpp>
#include <sst/catalog/remove_cvref_t.hpp>

namespace sst {

#define SST_src_t sst::remove_cvref_t<Src>
#define SST_dst_t sst::remove_cvref_t<Dst>
#define SST_src (std::declval<SST_src_t const &>())

template<class Unused, class Src, class Dst>
class read_whole_file_functor<
    sst::enable_if_t<
        std::is_convertible<decltype(sst::c_str(SST_src)),
                            char const *>::value
        && sst::is_output_iterator<Dst, unsigned char>::value>,
    Unused,
    Src,
    Dst> {

  using src_t = SST_src_t;
  using dst_t = SST_dst_t;

public:

  dst_t operator()(src_t const & src, dst_t dst) const {
    char const * const s = sst::c_str(src);
    SST_ASSERT((s != nullptr));
    FILE * const f = std::fopen(s, "rb");
    if (f == nullptr) {
      throw std::runtime_error("Error opening file " + sst::c_quote(s)
                               + " for reading.");
    }
    try {
      unsigned char buf[BUFSIZ];
      static_cast<void>(std::setvbuf(f, nullptr, _IONBF, 0));
      while (true) {
        std::size_t const n = std::fread(buf, 1, sizeof(buf), f);
        if (n < sizeof(buf) && std::ferror(f)) {
          throw std::runtime_error("Error while reading from file "
                                   + sst::c_quote(s) + ".");
        }
        for (std::size_t i = 0; i < n; ++i) {
          *dst = buf[i];
          ++dst;
        }
        if (n < sizeof(buf)) {
          break;
        }
      }
      static_cast<void>(std::fclose(f));
    } catch (...) {
      static_cast<void>(std::fclose(f));
      throw;
    }
    return dst;
  }

}; //

#undef SST_src
#undef SST_dst_t
#undef SST_src_t

} // namespace sst

#endif // #ifndef SST_PRIVATE_READ_WHOLE_FILE_EEAP4R29_HPP
