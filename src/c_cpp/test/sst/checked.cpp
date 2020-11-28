//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#include <TEST_EXIT.h>
#include <climits>
#include <exception>
#include <iostream>
#include <sst/catalog/checked.hpp>
#include <sst/limits.h>
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

#define TEST(x) ((x) ? test(true, #x) : test(false, #x))

#define TEST_THROWS(x) \
  do { \
    try { \
      static_cast<void>(x); \
      std::cout << "fail: " #x " throws sst::checked_error" \
                << std::endl; \
      throw fail(); \
    } catch (sst::checked_error const &) { \
      std::cout << "pass: " #x " throws sst::checked_error" \
                << std::endl; \
    } \
  } while (false)

} // namespace

int main() {
  try {
    std::cout.exceptions(std::cout.badbit | std::cout.failbit);

    TEST(sst::checked<int>() == 0);
    TEST(sst::checked<int>(0) == 0);
    TEST(sst::checked<int>(1) == 1);
    TEST(sst::checked<int>(2) == 2);
    TEST(sst::checked<int>(INT_MIN) == INT_MIN);
    TEST(sst::checked<int>(INT_MAX) == INT_MAX);

    TEST_THROWS(sst::checked<int>(INT_MAX) * 2);
    TEST_THROWS(INT_MAX * sst::checked<int>(2));
    TEST_THROWS(sst::checked<int>(INT_MAX) / 0);
    TEST_THROWS(INT_MAX / sst::checked<int>(0));
    TEST_THROWS(sst::checked<int>(INT_MAX) % 0);
    TEST_THROWS(INT_MAX % sst::checked<int>(0));
    TEST_THROWS(sst::checked<int>(INT_MAX) + 1);
    TEST_THROWS(INT_MAX + sst::checked<int>(1));
    TEST_THROWS(sst::checked<int>(INT_MIN) - 1);
    TEST_THROWS(INT_MIN - sst::checked<int>(1));

    TEST_THROWS(sst::checked<int>(-1) << 0);
    TEST_THROWS(sst::checked<int>(0) << -1);
    TEST_THROWS(sst::checked<int>(0) << sst::value_bits<int>::value);
    TEST_THROWS(sst::checked<int>(INT_MAX) << 1);

    TEST_THROWS(sst::checked<int>(-1) >> 0);
    TEST_THROWS(sst::checked<int>(0) >> -1);
    TEST_THROWS(sst::checked<int>(0) >> sst::value_bits<int>::value);

    TEST_THROWS(sst::checked<unsigned int>(UINT_MAX) * 2);
    TEST_THROWS(UINT_MAX * sst::checked<unsigned int>(2));
    TEST_THROWS(sst::checked<unsigned int>(UINT_MAX) / 0);
    TEST_THROWS(UINT_MAX / sst::checked<unsigned int>(0));
    TEST_THROWS(sst::checked<unsigned int>(UINT_MAX) % 0);
    TEST_THROWS(UINT_MAX % sst::checked<unsigned int>(0));
    TEST_THROWS(sst::checked<unsigned int>(UINT_MAX) + 1);
    TEST_THROWS(UINT_MAX + sst::checked<unsigned int>(1));
    TEST_THROWS(sst::checked<unsigned int>(0) - 1);
    TEST_THROWS(0 - sst::checked<unsigned int>(1));

    TEST_THROWS(sst::checked<unsigned int>(0) << -1);
    TEST_THROWS(sst::checked<unsigned int>(0)
                << sst::value_bits<unsigned int>::value);
    TEST_THROWS(sst::checked<unsigned int>(UINT_MAX) << 1);

    TEST_THROWS(sst::checked<unsigned int>(-1) >> 0);
    TEST_THROWS(sst::checked<unsigned int>(0) >> -1);
    TEST_THROWS(sst::checked<unsigned int>(0)
                >> sst::value_bits<unsigned int>::value);

    TEST_THROWS(static_cast<bool>(sst::checked<int>(2)));

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
