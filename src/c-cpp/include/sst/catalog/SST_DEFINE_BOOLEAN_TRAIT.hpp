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

#ifndef SST_CATALOG_SST_DEFINE_BOOLEAN_TRAIT_HPP
#define SST_CATALOG_SST_DEFINE_BOOLEAN_TRAIT_HPP

#include <type_traits>

#include <sst/catalog/SST_DISPATCH.h>
#include <sst/catalog/SST_EXPAND.h>
#include <sst/catalog/SST_LISTIFY.h>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/enable_t.hpp>

//----------------------------------------------------------------------
//
// Example:
//
//       SST_TVKYKBEHSU(class(T), class(Args, ...))
//    -> class, class...
//

#define SST_TVKYKBEHSU_class_2(T, ELLIPSIS) class ELLIPSIS T

#define SST_TVKYKBEHSU_class_1(T) class T

#define SST_TVKYKBEHSU_class(...)                                      \
  SST_DISPATCH(SST_TVKYKBEHSU_class_, __VA_ARGS__)                     \
  (__VA_ARGS__)

#define SST_TVKYKBEHSU(...)                                            \
  SST_LISTIFY(SST_TVKYKBEHSU_, (, ), __VA_ARGS__)

//----------------------------------------------------------------------
//
// Example:
//
//       SST_JRNKYXXHDF(class(T), class(Args, ...))
//    -> class T, class... Args
//

#define SST_JRNKYXXHDF_class_2(T, ELLIPSIS) class ELLIPSIS T

#define SST_JRNKYXXHDF_class_1(T) class T

#define SST_JRNKYXXHDF_class(...)                                      \
  SST_DISPATCH(SST_JRNKYXXHDF_class_, __VA_ARGS__)                     \
  (__VA_ARGS__)

#define SST_JRNKYXXHDF(...)                                            \
  SST_LISTIFY(SST_JRNKYXXHDF_, (, ), __VA_ARGS__)

//----------------------------------------------------------------------
//
// Example:
//
//       SST_ZGQVVJDFPJ(class(T), class(Args, ...))
//    -> T, Args...
//

#define SST_ZGQVVJDFPJ_class_2(T, ELLIPSIS) T ELLIPSIS

#define SST_ZGQVVJDFPJ_class_1(T) T

#define SST_ZGQVVJDFPJ_class(...)                                      \
  SST_DISPATCH(SST_ZGQVVJDFPJ_class_, __VA_ARGS__)                     \
  (__VA_ARGS__)

#define SST_ZGQVVJDFPJ(...)                                            \
  SST_LISTIFY(SST_ZGQVVJDFPJ_, (, ), __VA_ARGS__)

//----------------------------------------------------------------------

// TODO: Rename IMTXBGHSGP -> DEFINE_BOOLEAN_TRAIT after the old
//       SST_DEFINE_BOOLEAN_TRAIT_<N> macros are gone.

#define SST_IMTXBGHSGP_5(NAME, PARAMS, EXPR, TRUE_TYPE, FALSE_TYPE)    \
                                                                       \
  template<class, SST_TVKYKBEHSU PARAMS>                               \
  class SST_IMTXBGHSGP_##NAME : public SST_EXPAND FALSE_TYPE {};       \
                                                                       \
  template<SST_JRNKYXXHDF PARAMS>                                      \
  class SST_IMTXBGHSGP_##NAME<sst::enable_if_t<(EXPR)>,                \
                              SST_ZGQVVJDFPJ PARAMS>                   \
      : public SST_EXPAND TRUE_TYPE {};                                \
                                                                       \
  template<SST_JRNKYXXHDF PARAMS>                                      \
  using NAME =                                                         \
      SST_IMTXBGHSGP_##NAME<sst::enable_t, SST_ZGQVVJDFPJ PARAMS>;     \
                                                                       \
  struct SST_semicolon

#define SST_IMTXBGHSGP_4(NAME, PARAMS, EXPR, TRUE_TYPE)                \
  SST_IMTXBGHSGP_5(NAME, PARAMS, EXPR, TRUE_TYPE, (std::false_type))

#define SST_IMTXBGHSGP_3(NAME, PARAMS, EXPR)                           \
  SST_IMTXBGHSGP_4(NAME, PARAMS, EXPR, (std::true_type))

#define SST_DEFINE_BOOLEAN_TRAIT(...)                                  \
  SST_DISPATCH(SST_IMTXBGHSGP_, __VA_ARGS__)(__VA_ARGS__)

//----------------------------------------------------------------------

#endif // SST_CATALOG_SST_DEFINE_BOOLEAN_TRAIT_HPP
