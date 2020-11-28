//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#include <TEST_EXIT.h>
#include <iostream>
#include <limits>
#include <sst/language.h>
#include <sst/type.h>
#include <string>
#include <type_traits>

namespace {

struct fail {};

void test3(bool const x, std::string const & x_str) {
  if (x) {
    std::cout << "pass: " << x_str << std::endl;
  } else {
    std::cout << "fail: " << x_str << std::endl;
    throw fail();
  }
}

#define TEST2(x) test3(x, #x)

#define TEST(T) \
  do { \
    TEST2( \
        (static_cast<void>(sst::is_sign_magnitude<T>::value), true)); \
    TEST2((static_cast<void>(sst::is_sign_magnitude<T>()), true)); \
    TEST2((static_cast<void>( \
               static_cast<T>(sst::is_sign_magnitude<T>())), \
           true)); \
    TEST2((std::is_same<decltype(sst::is_sign_magnitude<T>::value), \
                        bool const>())); \
    TEST2(sst::is_sign_magnitude<T>() \
          == sst::is_sign_magnitude<T>::value); \
    int const int_min = std::numeric_limits<int>::min(); \
    TEST2(sst::is_sign_magnitude<T>() \
          == (sst::is_signed_integer<T>() && ~2 == int_min + 2)); \
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
