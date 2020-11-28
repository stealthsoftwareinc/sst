/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/bn_ctx.h>
#include <sst/bn_ctx.h>

#include <sst/SST_HAVE_LIB_CRYPTO.h>
#if SST_HAVE_LIB_CRYPTO

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
