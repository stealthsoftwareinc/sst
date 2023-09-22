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

#ifndef SST_CATALOG_POSIX_CP_HPP
#define SST_CATALOG_POSIX_CP_HPP

#include <sst/config.h>

#if SST_WITH_POSIX

#include <type_traits>

#include <sst/catalog/c_str.hpp>
#include <sst/catalog/cp_options.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_byte_pointer.hpp>
#include <sst/catalog/last_arg.hpp>
#include <sst/private/SST_DLL_EXPORT.h>

namespace sst {

//----------------------------------------------------------------------

extern SST_DLL_EXPORT void posix_cp(char const * const src,
                                    char const * const dst,
                                    sst::cp_options const & options);

//----------------------------------------------------------------------

template<
    class String1,
    class String2,
    sst::enable_if_t<
        sst::is_byte_pointer<String1>::value
        && sst::is_byte_pointer<String2>::value
        && (!std::is_convertible<String1 const &, char const *>::value
            || !std::is_convertible<String2 const &,
                                    char const *>::value)> = 0>
void posix_cp(String1 const & src,
              String2 const & dst,
              sst::cp_options const & options) {
  sst::posix_cp(reinterpret_cast<char const *>(src),
                reinterpret_cast<char const *>(dst),
                options);
}

//----------------------------------------------------------------------

template<class String1,
         class String2,
         sst::enable_if_t<std::is_pointer<String1>::value
                          && !std::is_pointer<String2>::value> = 0>
void posix_cp(String1 const & src,
              String2 const & dst,
              sst::cp_options const & options) {
  sst::posix_cp(src, sst::c_str(dst), options);
}

//----------------------------------------------------------------------

template<class String1,
         class String2,
         sst::enable_if_t<!std::is_pointer<String1>::value> = 0>
void posix_cp(String1 const & src,
              String2 const & dst,
              sst::cp_options const & options) {
  sst::posix_cp(sst::c_str(src), dst, options);
}

//----------------------------------------------------------------------

template<class String1,
         class String2,
         class... Rest,
         sst::enable_if_t<(sizeof...(Rest) >= 2)> = 0>
auto posix_cp(String1 const & src1,
              String2 const & src2,
              Rest const &... rest)
    -> sst::enable_if_t<
        std::is_convertible<decltype(sst::last_arg(rest...)),
                            sst::cp_options const &>::value,
        void> {
  sst::posix_cp(src1,
                sst::last_arg<2>(rest...),
                sst::last_arg(rest...));
  sst::posix_cp(src2, rest...);
}

//----------------------------------------------------------------------

template<class String,
         class... Rest,
         sst::enable_if_t<(sizeof...(Rest) >= 1)> = 0>
auto posix_cp(String const & src, Rest const &... rest)
    -> sst::enable_if_t<
        !std::is_convertible<decltype(sst::last_arg(rest...)),
                             sst::cp_options const &>::value,
        void> {
  sst::posix_cp(src, rest..., sst::cp_options());
}

//----------------------------------------------------------------------

} // namespace sst

#endif // #if SST_WITH_POSIX

#endif // SST_CATALOG_POSIX_CP_HPP
