//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#include <TEST_EXIT.h>
#include <iostream>
#include <sst/catalog/integer_promotes.hpp>
#include <string>

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

#define TEST(T, B) \
  do { \
    TEST2(sst::integer_promotes<T>() == B); \
    TEST2(sst::integer_promotes<T const>() == B); \
    TEST2(sst::integer_promotes<T volatile>() == B); \
    TEST2(sst::integer_promotes<T const volatile>() == B); \
  } while (false)

} // namespace

int main() {
  try {

    TEST(bool, true);
    TEST(signed char, true);
    TEST(unsigned char, true);
    TEST(short, true);
    TEST(unsigned short, true);
    TEST(int, false);
    TEST(unsigned int, false);
    TEST(long, false);
    TEST(unsigned long, false);
    TEST(long long, false);
    TEST(unsigned long long, false);

  } catch (fail const &) {
    return TEST_EXIT_FAIL;
  } catch (...) {
    return TEST_EXIT_ERROR;
  }
  return TEST_EXIT_PASS;
}
