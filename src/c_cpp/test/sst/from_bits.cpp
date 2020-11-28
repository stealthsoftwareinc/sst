//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#include <TEST_EXIT.h>
#include <climits>
#include <iostream>
#include <limits>
#include <sst/integer.h>
#include <sst/representation.h>
#include <sst/rep/to_hex.h>
#include <string>
#include <type_traits>
#include <vector>

namespace {

struct fail {};

// Checks for agreement across all q,r.
template<
    class Y,
    bool SignExtend = std::is_signed<Y>::value,
    class R,
    class N>
Y my_from_bits(
    std::string const & y_type,
    std::vector<unsigned char> const & x,
    R const r,
    N const n) {
  Y const ret = sst::from_bits<Y, SignExtend>(x.data(), r, n);
  using UR = typename sst::promote_unsigned<R>::type;
  UR const ur = static_cast<UR>(r);
  constexpr unsigned int cb = static_cast<unsigned int>(CHAR_BIT);
  for (UR q2 = 0; q2 != ur / cb + 1U; ++q2) {
    UR const r2 = ur - q2 * cb;
    Y const ret2 = sst::from_bits<Y, SignExtend>(x.data(), q2, r2, n);
    if (ret2 != ret) {
      std::cerr << "sst::from_bits<" << y_type << ", "
                << (SignExtend ? "true" : "false") << ">({0x"
                << sst::rep::to_hex(x) << "}, " << std::to_string(r)
                << ", " << std::to_string(n)
                << ") = " << std::to_string(ret)
                << " does not match sst::from_bits<" << y_type << ", "
                << (SignExtend ? "true" : "false") << ">({0x"
                << sst::rep::to_hex(x) << "}"
                << ", " << std::to_string(q2) << ", "
                << std::to_string(r2) << ", " << std::to_string(n)
                << ") = " << std::to_string(ret2) << std::endl;
      throw fail();
    }
  }
  return ret;
}

template<
    class Y,
    bool SignExtend = std::is_signed<Y>::value,
    class R,
    class N>
void test(
    std::string const & y_type,
    std::vector<unsigned char> const & x,
    R const r,
    N const n,
    Y const expect) {
  Y const actual = my_from_bits<Y, SignExtend>(y_type, x, r, n);
  if (actual != expect) {
    std::cerr << "sst::from_bits<" << y_type << ", "
              << (SignExtend ? "true" : "false") << ">({0x"
              << sst::rep::to_hex(x) << "}, " << std::to_string(r)
              << ", " << std::to_string(n)
              << ") = " << std::to_string(actual)
              << " is expected to be " << std::to_string(expect)
              << std::endl;
    ;
    throw fail();
  }
}

} // namespace

int main() {
  try {

    {
      std::vector<unsigned char> const x = {0, 0};
      for (unsigned int r = 0; r != CHAR_BIT; ++r) {
        for (unsigned int n = 1; n != 9; ++n) {
          test<bool>("bool", x, r, n, 0);
          test<bool, true>("bool", x, r, n, 0);
          test<bool, false>("bool", x, r, n, 0);
          test<int>("int", x, r, n, 0);
          test<int, true>("int", x, r, n, 0);
          test<int, false>("int", x, r, n, 0);
          test<unsigned int>("unsigned int", x, r, n, 0);
          test<unsigned int, true>("unsigned int", x, r, n, 0);
          test<unsigned int, false>("unsigned int", x, r, n, 0);
        }
      }
    }

    {
      std::vector<unsigned char> const x = {UCHAR_MAX, UCHAR_MAX};
      for (unsigned int r = 0; r != CHAR_BIT; ++r) {
        for (unsigned int n = 1; n != 9; ++n) {
          test<bool>("bool", x, r, n, 1);
          test<bool, true>("bool", x, r, n, 1);
          test<bool, false>("bool", x, r, n, 1);
          test<int>("int", x, r, n, -1);
          test<int, true>("int", x, r, n, -1);
          test<int, false>("int", x, r, n, (1 << n) - 1);
          test<unsigned int>("unsigned int", x, r, n, (1U << n) - 1U);
          test<unsigned int, true>("unsigned int", x, r, n, UINT_MAX);
          test<unsigned int, false>(
              "unsigned int", x, r, n, (1U << n) - 1U);
        }
      }
    }

  } catch (fail const &) {
    return TEST_EXIT_FAIL;
  } catch (...) {
    return TEST_EXIT_ERROR;
  }
  return TEST_EXIT_PASS;
}
