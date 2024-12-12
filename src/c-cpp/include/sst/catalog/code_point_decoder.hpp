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

#ifndef SST_CATALOG_CODE_POINT_DECODER_HPP
#define SST_CATALOG_CODE_POINT_DECODER_HPP

#include <sst/catalog/code_point_decoder_options.hpp>
#include <sst/catalog/code_point_decoder_t.hpp>
#include <sst/catalog/text_encoding.hpp>

namespace sst {

#define SST_r (sst::code_point_decoder_t<Encoding, Options>(options))

template<sst::text_encoding Encoding,
         class Options = sst::code_point_decoder_options>
auto code_point_decoder(Options const & options = Options()) noexcept(
    noexcept(SST_r)) -> decltype(SST_r) {
  return SST_r;
}

#undef SST_r

} // namespace sst

#endif // SST_CATALOG_CODE_POINT_DECODER_HPP
