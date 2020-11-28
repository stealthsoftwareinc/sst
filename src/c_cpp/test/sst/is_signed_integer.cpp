//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#include <TEST_EXIT.h>
#include <climits>
#include <cwchar>
#include <iostream>
#include <sst/type.h>
#include <string>

namespace {

struct fail {};

static void test(bool const x, std::string const & x_str) {
  if (!x) {
    std::cout << "expected " << x_str << std::endl;
    throw fail{};
  }
}

#define TEST3(x) test(x, #x)

#define TEST2(T, v) \
  ((v) ? TEST3((sst::is_signed_integer<T>::value)) : \
         TEST3((!sst::is_signed_integer<T>::value)))

#define TEST(T, v) \
  do { \
    TEST2(T, (v)); \
    TEST2(T const, (v)); \
    TEST2(T volatile, (v)); \
    TEST2(T const volatile, (v)); \
  } while (0)

} // namespace

int main() {
  try {

    TEST(signed char, true);
    TEST(short, true);
    TEST(int, true);
    TEST(long, true);
    TEST(long long, true);

    TEST(unsigned char, false);
    TEST(unsigned short, false);
    TEST(unsigned int, false);
    TEST(unsigned long, false);
    TEST(unsigned long long, false);

    TEST(bool, false);
    TEST(char, CHAR_MIN != 0);
    TEST(char16_t, false);
    TEST(char32_t, false);
    TEST(wchar_t, WCHAR_MIN != 0);

    TEST(float, false);
    TEST(double, false);
    TEST(long double, false);

    TEST(void, false);

    struct empty_struct {};
    TEST(empty_struct, false);

    enum class empty_enum_class {};
    TEST(empty_enum_class, false);

    return TEST_EXIT_PASS;

  } catch (fail const &) {
    return TEST_EXIT_FAIL;
  } catch (...) {
    return TEST_EXIT_ERROR;
  }
}
