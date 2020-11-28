//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#include <TEST_EXIT.h>
#include <exception>
#include <iostream>
#include <sst/catalog/is_exact_width_integer.hpp>
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
  ((v) ? TEST3(sst::is_exact_width_integer<T>::value) : \
         TEST3(!sst::is_exact_width_integer<T>::value))

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

    TEST(bool, false);
    TEST(void, false);
    TEST(float, false);
    TEST(double, false);
    TEST(std::exception, false);
#ifdef INT8_MAX
    TEST(std::int8_t, true);
#endif
#ifdef UINT8_MAX
    TEST(std::uint8_t, true);
#endif
#ifdef INT16_MAX
    TEST(std::int16_t, true);
#endif
#ifdef UINT16_MAX
    TEST(std::uint16_t, true);
#endif
#ifdef INT32_MAX
    TEST(std::int32_t, true);
#endif
#ifdef UINT32_MAX
    TEST(std::uint32_t, true);
#endif
#ifdef INT64_MAX
    TEST(std::int64_t, true);
#endif
#ifdef UINT64_MAX
    TEST(std::uint64_t, true);
#endif

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
