/*
 * Copyright (C) 2012-2023 Stealth Software Technologies, Inc.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice (including
 * the next paragraph) shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 */

#include <sst/bn_ctx.h>
#include <sst/bn_ctx.h>

#include <sst/config.h>

#if SST_WITH_OPENSSL_CRYPTO

#include <iostream>
#include <TEST_EXIT.h>
#include <string>
#include <type_traits>

struct fail {};

template<class T>
static void f1(
  sst::bn_ctx bn,
  T const x
) {
  std::string const s1 = std::to_string(x);
  std::string const s2 = bn.bn2dec(bn.int2bn(x));
  if (s1 != s2) {
    std::cerr
      << "x = " << s1 << ":" << std::endl
      << "  std::tostring(x):        " << s1 << std::endl
      << "  bn.bn2dec(bn.int2bn(x)): " << s2 << std::endl
    ;
    throw fail{};
  }
}

template<class T>
static void f2(
  sst::bn_ctx bn
) {
  if (std::is_signed<T>::value) {
    f1(bn.arg(), std::numeric_limits<T>::min());
    f1(bn.arg(), std::numeric_limits<T>::min() / 2);
  }
  f1(bn.arg(), static_cast<T>(0));
  f1(bn.arg(), std::numeric_limits<T>::max() / 2);
  f1(bn.arg(), std::numeric_limits<T>::max());
}

int main(
) {
  try {
    sst::bn_ctx bn;
    f2<int>(bn.arg());
    f2<long>(bn.arg());
    f2<long long>(bn.arg());
    f2<unsigned int>(bn.arg());
    f2<unsigned long>(bn.arg());
    f2<unsigned long long>(bn.arg());
    return TEST_EXIT_PASS;
  } catch (fail) {
    return TEST_EXIT_FAIL;
  } catch (...) {
    return TEST_EXIT_ERROR;
  }
}

#else

#include <TEST_EXIT.h>

int main(
) {
  return TEST_EXIT_SKIP;
}

#endif
