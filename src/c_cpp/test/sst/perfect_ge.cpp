//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#include <TEST_EXIT.h>
#include <exception>
#include <iostream>
#include <sst/catalog/perfect_ge.hpp>
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

#define TEST2(x) test(x, #x)

#define TEST(a, b) \
  do { \
    TEST2((sst::perfect_ge(a, b))); \
  } while (false)

} // namespace

int main() {
  try {

    TEST(1, false);
    TEST(1U, false);

    TEST(1, true);
    TEST(1U, true);

    TEST(2, true);
    TEST(2U, true);

    TEST(1, 0);
    TEST(1U, 0);

    TEST(1, 1);
    TEST(1U, 1);

    TEST(1, 0U);
    TEST(1U, 0U);

    TEST(1, 1U);
    TEST(1U, 1U);

    TEST(0, -1);
    TEST(0U, -1);

    TEST(-1, -1);

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
