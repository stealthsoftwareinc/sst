//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#include <TEST_EXIT.h>
#include <exception>
#include <iostream>
#include <sst/catalog/is_bool.hpp>
#include <string>

namespace {

struct fail {};

void test(bool const x, std::string const & x_str) {
  if (x) {
    std::cout << "pass: " << x_str << std::endl;
  } else {
    std::cout << "fail: " << x_str << std::endl;
    throw fail();
  }
}

#define TEST3(x) test(x, #x)

#define TEST2(T, v) \
  ((v) ? TEST3(sst::is_bool<T>::value) : TEST3(!sst::is_bool<T>::value))

#define TEST(T, v) \
  do { \
    TEST2(T, (v)); \
    TEST2(T const, (v)); \
    TEST2(T volatile, (v)); \
    TEST2(T const volatile, (v)); \
  } while (false)

} // namespace

int main() {
  try {

    TEST(signed char, false);
    TEST(short, false);
    TEST(int, false);
    TEST(long, false);
    TEST(long long, false);

    TEST(unsigned char, false);
    TEST(unsigned short, false);
    TEST(unsigned int, false);
    TEST(unsigned long, false);
    TEST(unsigned long long, false);

    TEST(bool, true);
    TEST(char, false);
    TEST(char16_t, false);
    TEST(char32_t, false);
    TEST(wchar_t, false);

    TEST(float, false);
    TEST(double, false);
    TEST(long double, false);

    TEST(void, false);

    struct empty_struct {};
    TEST(empty_struct, false);

    enum class empty_enum_class {};
    TEST(empty_enum_class, false);

  } catch (fail const &) {
    return TEST_EXIT_FAIL;
  } catch (std::exception const & e) {
    std::cerr << "error: " << e.what() << std::endl;
    return TEST_EXIT_ERROR;
  } catch (...) {
    return TEST_EXIT_ERROR;
  }
  return TEST_EXIT_PASS;
}
