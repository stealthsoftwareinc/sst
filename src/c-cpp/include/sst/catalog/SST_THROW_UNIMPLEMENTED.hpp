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

#ifndef SST_CATALOG_SST_THROW_UNIMPLEMENTED_HPP
#define SST_CATALOG_SST_THROW_UNIMPLEMENTED_HPP

#include <stdexcept>

#include <sst/catalog/to_string.hpp>

// TODO: We should replace this with just SST_UNIMPLEMENTED() that
//       constructs the exception object. Then it can be composed with
//       things like SST_TEV_THROW(tev, SST_UNIMPLEMENTED()) or just
//       throw SST_UNIMPLEMENTED(). First implement SST_UNIMPLEMENTED,
//       then deprecate SST_THROW_UNIMPLEMENTED. Or just leave it
//       around forever, that's fine too.

#define SST_THROW_UNIMPLEMENTED()                                      \
  (throw std::runtime_error("Unimplemented code at " __FILE__ ":"      \
                            + sst::to_string(__LINE__) + "."))

#endif // SST_CATALOG_SST_THROW_UNIMPLEMENTED_HPP
