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

#ifndef SST_PRIVATE_WRITE_WHOLE_FILE_KQ74CP3F_HPP
#define SST_PRIVATE_WRITE_WHOLE_FILE_KQ74CP3F_HPP

#include <cstdio>
#include <stdexcept>
#include <type_traits>
#include <utility>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/c_quote.hpp>
#include <sst/catalog/c_str.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/is_byte_input_iterator.hpp>
#include <sst/catalog/is_sentinel.hpp>
#include <sst/catalog/peek.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/write_whole_file.hpp>
#include <sst/catalog/write_whole_file_functor.hpp>
#include <sst/catalog/write_whole_file_options.hpp>

namespace sst {

#define SST_src_t sst::remove_cvref_t<Src>
#define SST_end_t sst::remove_cvref_t<End>
#define SST_dst_t sst::remove_cvref_t<Dst>
#define SST_dst (std::declval<SST_dst_t const &>())

//----------------------------------------------------------------------

template<class Unused, class Src, class End, class Dst, class Options>
class write_whole_file_functor<
    sst::enable_if_t<
        sst::is_byte_input_iterator<Src>::value
        && sst::is_sentinel<End, Src>::value
        && std::is_convertible<decltype(sst::c_str(SST_dst)),
                               char const *>::value
        && std::is_convertible<Options,
                               sst::write_whole_file_options>::value>,
    Unused,
    Src,
    End,
    Dst,
    Options> {

  using src_t = SST_src_t;
  using end_t = SST_end_t;
  using dst_t = SST_dst_t;
  using src_value_t = sst::value_type_t<Src>;

public:

  void
  operator()(src_t src,
             end_t const & end,
             dst_t const & dst,
             sst::write_whole_file_options const & options = {}) const {
    char const * const s = sst::c_str(dst);
    SST_ASSERT((s != nullptr));
    FILE * f = std::fopen(s, "wb");
    if (f == nullptr) {
      throw std::runtime_error("Error opening file " + sst::c_quote(s)
                               + " for writing.");
    }
    try {
      unsigned char buf[BUFSIZ];
      static_cast<void>(std::setvbuf(f, nullptr, _IONBF, 0));
      while (true) {
        bool done = false;
        std::size_t n = 0;
        while (n < sizeof(buf)) {
          auto const px = sst::peek(src, end);
          if (px == nullptr) {
            done = true;
            break;
          }
          src_value_t const & x = *px;
          if (!options.allow_zero(x) && x == 0) {
            done = true;
            break;
          }
          ++src;
          buf[n++] = static_cast<unsigned char>(x);
        }
        if (std::fwrite(buf, 1, n, f) != n) {
          throw std::runtime_error("Error while writing to file "
                                   + sst::c_quote(s) + ".");
        }
        if (done) {
          break;
        }
      }
      if (std::fclose(f) != 0) {
        f = nullptr;
        throw std::runtime_error("Error while writing to file "
                                 + sst::c_quote(s) + ".");
      }
      f = nullptr;
    } catch (...) {
      if (f != nullptr) {
        static_cast<void>(std::fclose(f));
      }
      throw;
    }
  }

}; //

//----------------------------------------------------------------------

template<class Unused, class Src, class End, class Dst>
class write_whole_file_functor<
    sst::enable_if_t<
        sst::is_byte_input_iterator<Src>::value
        && sst::is_sentinel<End, Src>::value
        && std::is_convertible<decltype(sst::c_str(SST_dst)),
                               char const *>::value>,
    Unused,
    Src,
    End,
    Dst>
    : public write_whole_file_functor<sst::enable_t,
                                      Unused,
                                      Src,
                                      End,
                                      Dst,
                                      sst::write_whole_file_options> {};

//----------------------------------------------------------------------

#undef SST_dst
#undef SST_dst_t
#undef SST_end_t
#undef SST_src_t

} // namespace sst

#endif // SST_PRIVATE_WRITE_WHOLE_FILE_KQ74CP3F_HPP
