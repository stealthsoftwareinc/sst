//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#include <TEST_EXIT.h>
#include <iostream>
#include <limits>
#include <sst/catalog/ceil_sqrt.hpp>
#include <string>

namespace {

struct fail {};

void expect(bool const x, std::string const & x_str) {
  if (!x) {
    std::cout << "expected " << x_str << std::endl;
    throw fail();
  }
}

#define expect(x) expect(x, #x)

} // namespace

int main() {
  try {

    expect(sst::ceil_sqrt(0) == 0);
    expect(sst::ceil_sqrt(1) == 1);
    expect(sst::ceil_sqrt(2) == 2);
    expect(sst::ceil_sqrt(3) == 2);
    expect(sst::ceil_sqrt(4) == 2);
    expect(sst::ceil_sqrt(5) == 3);
    expect(sst::ceil_sqrt(6) == 3);
    expect(sst::ceil_sqrt(7) == 3);
    expect(sst::ceil_sqrt(8) == 3);
    expect(sst::ceil_sqrt(9) == 3);
    expect(sst::ceil_sqrt(10) == 4);
    expect(sst::ceil_sqrt(11) == 4);
    expect(sst::ceil_sqrt(12) == 4);
    expect(sst::ceil_sqrt(13) == 4);
    expect(sst::ceil_sqrt(14) == 4);
    expect(sst::ceil_sqrt(15) == 4);
    expect(sst::ceil_sqrt(16) == 4);
    expect(sst::ceil_sqrt(17) == 5);
    expect(sst::ceil_sqrt(18) == 5);
    expect(sst::ceil_sqrt(19) == 5);

    int const n = (std::numeric_limits<int>::digits - 1) / 2 * 2;
    expect(sst::ceil_sqrt((1 << n) - 1) == (1 << (n / 2)) + 0);
    expect(sst::ceil_sqrt((1 << n) + 0) == (1 << (n / 2)) + 0);
    expect(sst::ceil_sqrt((1 << n) + 1) == (1 << (n / 2)) + 1);

  } catch (fail const &) {
    return TEST_EXIT_FAIL;
  } catch (...) {
    return TEST_EXIT_ERROR;
  }
  return TEST_EXIT_PASS;
}
