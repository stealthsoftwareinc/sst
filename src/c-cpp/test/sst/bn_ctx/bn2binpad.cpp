/*
 * Copyright (C) 2012-2024 Stealth Software Technologies, Inc.
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

#include <TEST_EXIT.h>
#include <iostream>
#include <stdexcept>
#include <vector>

struct fail {};

template<class T>
void f(
  sst::bn_ctx bn,
  T const a,
  std::vector<unsigned char> const & b
) {
  std::vector<unsigned char> const c{
    bn.bn2binpad(bn.int2bn(a), b.size())
  };
  if (b != c) {
    throw fail{};
  }
}

int main(
) {
  try {
    sst::bn_ctx bn;
    f(bn.arg(), 0, {});
    f(bn.arg(), 0, {0});
    f(bn.arg(), 0, {0,0});
    f(bn.arg(), 1, {1});
    f(bn.arg(), 1, {0,1});
    return TEST_EXIT_PASS;
  } catch (fail const &) {
    return TEST_EXIT_FAIL;
  } catch (std::exception const & e) {
    try {
      std::cout << e.what() << std::endl;
    } catch (...) {
    }
    return TEST_EXIT_ERROR;
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
