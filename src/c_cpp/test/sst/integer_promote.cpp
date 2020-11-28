//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

// TODO: Change <sst/limits.h> to <sst/catalog/value_bits.hpp>

#include <TEST_EXIT.h>
#include <iostream>
#include <sst/catalog/integer_promote.hpp>
#include <sst/limits.h>
#include <string>
#include <type_traits>

namespace {

struct fail {};

void test3(bool const x, std::string const & x_str) {
  std::cout.exceptions(std::cout.badbit | std::cout.failbit);
  if (x) {
    std::cout << "pass: " << x_str << std::endl;
  } else {
    std::cout << "fail: " << x_str << std::endl;
    throw fail();
  }
}

#define TEST2(x) test3(x, #x)

#define TEST(T, U) \
  do { \
    TEST2((std::is_same<sst::integer_promote<T>::type, U>())); \
    TEST2((std::is_same<sst::integer_promote<T const>::type, \
                        U const>())); \
    TEST2((std::is_same<sst::integer_promote<T volatile>::type, \
                        U volatile>())); \
    TEST2((std::is_same<sst::integer_promote<T const volatile>::type, \
                        U const volatile>())); \
  } while (false)

} // namespace

int main() {
  try {

    TEST(bool, int);
    TEST(signed char, int);
    if (sst::value_bits<unsigned char>() <= sst::value_bits<int>()) {
      TEST(unsigned char, int);
    } else {
      TEST(unsigned char, unsigned int);
    }
    TEST(short, int);
    if (sst::value_bits<unsigned short>() <= sst::value_bits<int>()) {
      TEST(unsigned short, int);
    } else {
      TEST(unsigned short, unsigned int);
    }
    TEST(int, int);
    TEST(unsigned int, unsigned int);
    TEST(long, long);
    TEST(unsigned long, unsigned long);
    TEST(long long, long long);
    TEST(unsigned long long, unsigned long long);

  } catch (fail const &) {
    return TEST_EXIT_FAIL;
  } catch (...) {
    return TEST_EXIT_ERROR;
  }
  return TEST_EXIT_PASS;
}
