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

#ifndef SST_CATALOG_CRYPTO_RNG_HPP
#define SST_CATALOG_CRYPTO_RNG_HPP

#include <utility>

#include <sst/catalog/crypto_rng_t.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/private/SST_DLL_EXPORT.h>

namespace sst {

//----------------------------------------------------------------------
// sst::crypto_rng (uto8d8vg)
//----------------------------------------------------------------------

extern SST_DLL_EXPORT sst::crypto_rng_t & crypto_rng();

//----------------------------------------------------------------------
// sst::crypto_rng (mc29wudn)
//----------------------------------------------------------------------

#define SST_r (sst::crypto_rng()(std::forward<Args>(args)...))

template<class... Args, sst::enable_if_t<(sizeof...(Args) > 0U)> = 0>
auto crypto_rng(Args &&... args) noexcept(noexcept(SST_r))
    -> decltype(SST_r) {
  return SST_r;
}

#undef SST_r

//----------------------------------------------------------------------

} // namespace sst

#endif // SST_CATALOG_CRYPTO_RNG_HPP
