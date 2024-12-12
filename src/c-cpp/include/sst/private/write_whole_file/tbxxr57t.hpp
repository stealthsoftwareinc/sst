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

#ifndef SST_PRIVATE_WRITE_WHOLE_FILE_TBXXR57T_HPP
#define SST_PRIVATE_WRITE_WHOLE_FILE_TBXXR57T_HPP

#include <type_traits>
#include <utility>

#include <sst/catalog/c_str.hpp>
#include <sst/catalog/cbegin.hpp>
#include <sst/catalog/cend.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/is_byte_input_iterable.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/write_whole_file.hpp>
#include <sst/catalog/write_whole_file_functor.hpp>
#include <sst/catalog/write_whole_file_options.hpp>

namespace sst {

#define SST_src_t sst::remove_cvref_t<Src>
#define SST_dst_t sst::remove_cvref_t<Dst>
#define SST_dst (std::declval<SST_dst_t const &>())

//----------------------------------------------------------------------

template<class Unused, class Src, class Dst, class Options>
class write_whole_file_functor<
    sst::enable_if_t<
        sst::is_byte_input_iterable<Src>::value
        && std::is_convertible<decltype(sst::c_str(SST_dst)),
                               char const *>::value
        && std::is_convertible<Options,
                               sst::write_whole_file_options>::value>,
    Unused,
    Src,
    Dst,
    Options> {

  using src_t = SST_src_t;
  using dst_t = SST_dst_t;

public:

  void
  operator()(src_t const & src,
             dst_t const & dst,
             sst::write_whole_file_options const & options = {}) const {
    sst::write_whole_file(sst::cbegin(src),
                          sst::cend(src),
                          dst,
                          options);
  }

}; //

//----------------------------------------------------------------------

template<class Unused, class Src, class Dst>
class write_whole_file_functor<
    sst::enable_if_t<
        sst::is_byte_input_iterable<Src>::value
        && std::is_convertible<decltype(sst::c_str(SST_dst)),
                               char const *>::value>,
    Unused,
    Src,
    Dst>
    : public write_whole_file_functor<sst::enable_t,
                                      Unused,
                                      Src,
                                      Dst,
                                      sst::write_whole_file_options> {};

//----------------------------------------------------------------------

#undef SST_dst
#undef SST_dst_t
#undef SST_src_t

} // namespace sst

#endif // SST_PRIVATE_WRITE_WHOLE_FILE_TBXXR57T_HPP
