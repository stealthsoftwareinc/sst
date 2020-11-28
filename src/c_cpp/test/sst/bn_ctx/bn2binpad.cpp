/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/bn_ctx.h>
#include <sst/bn_ctx.h>

#include <sst/SST_HAVE_LIB_CRYPTO.h>
#if SST_HAVE_LIB_CRYPTO

/* begin_includes */

#include <TEST_EXIT.h>
#include <iostream>
#include <stdexcept>
#include <vector>

/* end_includes */

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
