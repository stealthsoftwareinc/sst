//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#include <TEST_EXIT.h>
#include <iostream>
#include <limits>
#include <sst/catalog/type_max.hpp>
#include <sst/catalog/type_msb.hpp>
#include <string>
#include <type_traits>

namespace {

struct fail {};

void test3(bool const x, std::string const & x_str) {
  if (!x) {
    std::cerr << "expected " << x_str << std::endl;
    throw fail();
  }
}

#define TEST2(x) test3(x, #x)

#define TEST(T) \
  do { \
    T const max = sst::type_max<T>::value; \
    TEST2((static_cast<void>(sst::type_msb<T>::value), true)); \
    TEST2((static_cast<void>(sst::type_msb<T>()), true)); \
    TEST2((static_cast<void>(static_cast<T>(sst::type_msb<T>())), \
           true)); \
    TEST2( \
        (std::is_same<decltype(sst::type_msb<T>::value), T const>())); \
    TEST2(sst::type_msb<T>() == sst::type_msb<T>::value); \
    TEST2(sst::type_msb<T>() == static_cast<T>(max ^ (max >> 1))); \
  } while (false)

} // namespace

int main() {
  try {

    TEST(bool);
    TEST(char);
    TEST(signed char);
    TEST(unsigned char);
    TEST(short);
    TEST(unsigned short);
    TEST(int);
    TEST(unsigned int);
    TEST(long);
    TEST(unsigned long);
    TEST(long long);
    TEST(unsigned long long);

  } catch (fail const &) {
    return TEST_EXIT_FAIL;
  } catch (...) {
    return TEST_EXIT_ERROR;
  }
  return TEST_EXIT_PASS;
}
