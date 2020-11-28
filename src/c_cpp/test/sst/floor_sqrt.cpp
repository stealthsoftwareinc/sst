//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#include <TEST_EXIT.h>
#include <iostream>
#include <limits>
#include <sst/catalog/floor_sqrt.hpp>
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

    expect(sst::floor_sqrt(0) == 0);
    expect(sst::floor_sqrt(1) == 1);
    expect(sst::floor_sqrt(2) == 1);
    expect(sst::floor_sqrt(3) == 1);
    expect(sst::floor_sqrt(4) == 2);
    expect(sst::floor_sqrt(5) == 2);
    expect(sst::floor_sqrt(6) == 2);
    expect(sst::floor_sqrt(7) == 2);
    expect(sst::floor_sqrt(8) == 2);
    expect(sst::floor_sqrt(9) == 3);
    expect(sst::floor_sqrt(10) == 3);
    expect(sst::floor_sqrt(11) == 3);
    expect(sst::floor_sqrt(12) == 3);
    expect(sst::floor_sqrt(13) == 3);
    expect(sst::floor_sqrt(14) == 3);
    expect(sst::floor_sqrt(15) == 3);
    expect(sst::floor_sqrt(16) == 4);
    expect(sst::floor_sqrt(17) == 4);
    expect(sst::floor_sqrt(18) == 4);
    expect(sst::floor_sqrt(19) == 4);

    int const n = (std::numeric_limits<int>::digits - 1) / 2 * 2;
    expect(sst::floor_sqrt((1 << n) - 1) == (1 << (n / 2)) - 1);
    expect(sst::floor_sqrt((1 << n) + 0) == (1 << (n / 2)) + 0);
    expect(sst::floor_sqrt((1 << n) + 1) == (1 << (n / 2)) + 0);

  } catch (fail const &) {
    return TEST_EXIT_FAIL;
  } catch (...) {
    return TEST_EXIT_ERROR;
  }
  return TEST_EXIT_PASS;
}
