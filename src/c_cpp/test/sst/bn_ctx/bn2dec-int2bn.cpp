/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/bn_ctx.h>
#include <sst/bn_ctx.h>

#include <sst/SST_HAVE_LIB_CRYPTO.h>
#if SST_HAVE_LIB_CRYPTO

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
