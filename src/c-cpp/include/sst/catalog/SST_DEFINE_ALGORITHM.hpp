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

#ifndef SST_CATALOG_SST_DEFINE_ALGORITHM_HPP
#define SST_CATALOG_SST_DEFINE_ALGORITHM_HPP

#include <utility>

#include <sst/catalog/SST_EXPAND.h>
#include <sst/catalog/enable_t.hpp>

//
// One reason we use a functor instead of an overloaded function is
// because it makes it easy for different overloads to call each other.
// The functor is declared as "template<class...> class functor;", and
// the dispatch function is defined immediately thereafter. This allows
// the dispatch function to be called from anywhere, even from within a
// functor specialization, and even if doing so causes mutual recursion
// between functor specializations. The only requirement is that all of
// the necessary functor specializations must be defined (in any order)
// before they are needed by an actual instantiation.
//
// It would be possible to make the dispatch function always prefer ADL.
// For example, sst::to_hex could prefer an ADL match via an unqualified
// to_hex call over using to_hex_functor. However, this has questionable
// long term properties, as ADL can cause surprising matches and there
// would be no way to opt out. It seems more prudent to stick with the
// approach that sst::to_hex will always use to_hex_functor.
//
// We also prevent ADL from ever matching sst::to_hex itself. If we
// didn't, then ADL would often select it over all other candidates
// because it's a forwarding function. This would be confusing.
//

#define SST_DEFINE_ALGORITHM_r(FUNCTOR, PASS)                          \
  (FUNCTOR<::sst::enable_t, SST_EXPAND PASS, SST_Rest...>()(           \
      ::std::forward<SST_Rest>(SST_rest)...))

#define SST_DEFINE_ALGORITHM_4(FUNCTION, PARAM, PASS, FUNCTOR)         \
                                                                       \
  template<class...>                                                   \
  class FUNCTOR;                                                       \
                                                                       \
  namespace SST_DEFINE_ALGORITHM_ADL_BARRIER_##FUNCTION {              \
                                                                       \
    template<SST_EXPAND PARAM, class... SST_Rest>                      \
    constexpr auto FUNCTION(SST_Rest &&... SST_rest) noexcept(         \
        noexcept(SST_DEFINE_ALGORITHM_r(FUNCTOR, PASS)))               \
        ->decltype(SST_DEFINE_ALGORITHM_r(FUNCTOR, PASS)) {            \
      return SST_DEFINE_ALGORITHM_r(FUNCTOR, PASS);                    \
    }                                                                  \
                                                                       \
  } /* namespace SST_DEFINE_ALGORITHM_ADL_BARRIER_##FUNCTION */        \
                                                                       \
  /* ADL never matches functions imported with "using namespace". */   \
  using namespace SST_DEFINE_ALGORITHM_ADL_BARRIER_##FUNCTION;

#define SST_DEFINE_ALGORITHM_3(FUNCTION, PARAM, PASS)                  \
  SST_DEFINE_ALGORITHM_4(FUNCTION, PARAM, PASS, FUNCTION##_functor)

#define SST_DEFINE_ALGORITHM_1(FUNCTION)                               \
  SST_DEFINE_ALGORITHM_3(FUNCTION, (class = void), (void))

#define SST_DEFINE_ALGORITHM_A5(A1, A2, A3, A4, A5, ...) A5

#define SST_DEFINE_ALGORITHM_PICK(...)                                 \
  SST_DEFINE_ALGORITHM_A5(__VA_ARGS__,                                 \
                          SST_DEFINE_ALGORITHM_4,                      \
                          SST_DEFINE_ALGORITHM_3,                      \
                          SST_DEFINE_ALGORITHM_2,                      \
                          SST_DEFINE_ALGORITHM_1, )

#define SST_DEFINE_ALGORITHM(...)                                      \
  SST_DEFINE_ALGORITHM_PICK(__VA_ARGS__)(__VA_ARGS__)

#endif // SST_CATALOG_SST_DEFINE_ALGORITHM_HPP
