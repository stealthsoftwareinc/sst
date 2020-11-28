//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#include <TEST_EXIT.h>
#include <exception>
#include <iostream>
#include <sst/catalog/perfect_eq.hpp>
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
    TEST2((sst::perfect_eq(a, b))); \
    TEST2((sst::perfect_eq(b, a))); \
  } while (false)

} // namespace

int main() {
  try {

    TEST(false, false);
    TEST(false, 0);
    TEST(false, 0U);

    TEST(true, true);
    TEST(true, 1);
    TEST(true, 1U);

    TEST(0, 0);
    TEST(0, 0U);

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
