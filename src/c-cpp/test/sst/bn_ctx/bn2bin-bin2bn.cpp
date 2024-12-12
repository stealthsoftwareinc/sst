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
#include <string>
#include <vector>

struct fail {};

static std::string v2s(
  std::vector<unsigned char> const & x
) {
  std::string y;
  y += "{";
  for (decltype(x.size()) i{0}; i != x.size(); ++i) {
    if (i != 0) {
      y += ", ";
    }
    y += std::to_string(x[i]);
  }
  y += "}";
  return y;
}

static void f(
  sst::bn_ctx bn,
  std::vector<unsigned char> const & x
) {
  std::vector<unsigned char> const y{bn.bn2bin(bn.bin2bn(x))};
  if (x != y) {
    std::cerr
      << "x                 = " << v2s(x) << std::endl
      << "bn2bin(bin2bn(x)) = " << v2s(y) << std::endl
    ;
    throw fail{};
  }
}

int main(
) {
  try {
    sst::bn_ctx bn;
    std::vector<unsigned char> x;
    f(bn.arg(), x);
    for (unsigned char i{1}; i != 101; ++i) {
      x.push_back(i);
      f(bn.arg(), x);
    }
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
