//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#include <TEST_EXIT.h>
#include <climits>
#include <iostream>
#include <limits>
#include <sst/bit.h>
#include <sst/integer.h>
#include <sst/rep/to_hex.h>
#include <string>
#include <type_traits>
#include <vector>

namespace {

struct fail {};

// Checks for agreement across all q,r.
template<class X, class R>
bool my_get_bit_int(X const x, std::string const & x_type, R const r) {
  bool const ret = sst::get_bit(x, r);
  using UR = typename sst::promote_unsigned<R>::type;
  UR const ur = static_cast<UR>(r);
  constexpr unsigned int cb = static_cast<unsigned int>(CHAR_BIT);
  for (UR q2 = 0; q2 != ur / cb + 1U; ++q2) {
    UR const r2 = ur - q2 * cb;
    X const ret2 = sst::get_bit(x, q2, r2);
    if (ret2 != ret) {
      std::cerr << "sst::get_bit((" << x_type << ")"
                << std::to_string(x) << ", " << std::to_string(r)
                << ") = " << std::to_string(ret)
                << " does not match sst::get_bit((" << x_type << ")"
                << std::to_string(x) << ", " << std::to_string(q2)
                << ", " << std::to_string(r2)
                << ") = " << std::to_string(ret2) << std::endl;
      throw fail();
    }
  }
  return ret;
}

template<class X, class R>
void test_int_2(
    X const x,
    std::string const & x_type,
    R const r,
    bool const expect) {
  bool const actual = my_get_bit_int(x, x_type, r);
  if (actual != expect) {
    std::cerr << "sst::get_bit((" << x_type << ")" << std::to_string(x)
              << ", " << std::to_string(r)
              << ") = " << std::to_string(actual)
              << " is expected to be " << std::to_string(expect)
              << std::endl;
    throw fail();
  }
}

template<class X>
void test_int(std::string const & x_type) {
  constexpr int X_width =
      std::numeric_limits<X>::digits + std::is_signed<X>::value;
  for (int r = 0; r != X_width; ++r) {
    test_int_2(X(0), x_type, r, 0);
  }
  for (int r = 0; r != X_width; ++r) {
    test_int_2(X(-1), x_type, r, 1);
  }
}
#define TEST_INT(X) test_int<X>(#X)

// Checks for agreement across all q,r.
template<class R>
bool my_get_bit_mem(std::vector<unsigned char> const & x, R const r) {
  bool const ret = sst::get_bit(x.data(), r);
  using UR = typename sst::promote_unsigned<R>::type;
  UR const ur = static_cast<UR>(r);
  constexpr unsigned int cb = static_cast<unsigned int>(CHAR_BIT);
  for (UR q2 = 0; q2 != ur / cb + 1U; ++q2) {
    UR const r2 = ur - q2 * cb;
    bool const ret2 = sst::get_bit(x.data(), q2, r2);
    if (ret2 != ret) {
      std::cerr << "sst::get_bit({0x" << sst::rep::to_hex(x) << "}, "
                << std::to_string(r) << ") = " << std::to_string(ret)
                << " does not match sst::get_bit({0x"
                << sst::rep::to_hex(x) << "}, " << std::to_string(q2)
                << ", " << std::to_string(r2)
                << ") = " << std::to_string(ret2) << std::endl;
      throw fail();
    }
  }
  return ret;
}

template<class R>
void test_mem(
    std::vector<unsigned char> const & x,
    R const r,
    bool const expect) {
  bool const actual = my_get_bit_mem(x, r);
  if (actual != expect) {
    std::cerr << "sst::get_bit({0x" << sst::rep::to_hex(x) << "}, "
              << std::to_string(r) << ") = " << std::to_string(actual)
              << " is expected to be " << std::to_string(expect)
              << std::endl;
    throw fail();
  }
}

} // namespace

int main() {
  try {

    TEST_INT(bool);
    TEST_INT(signed char);
    TEST_INT(unsigned char);
    TEST_INT(short);
    TEST_INT(unsigned short);
    TEST_INT(int);
    TEST_INT(unsigned int);
    TEST_INT(long);
    TEST_INT(unsigned long);
    TEST_INT(long long);
    TEST_INT(unsigned long long);

    test_mem({0xAA, 0x55}, CHAR_BIT * 0U + 0, 0);
    test_mem({0xAA, 0x55}, CHAR_BIT * 0U + 1, 1);
    test_mem({0xAA, 0x55}, CHAR_BIT * 0U + 2, 0);
    test_mem({0xAA, 0x55}, CHAR_BIT * 0U + 3, 1);
    test_mem({0xAA, 0x55}, CHAR_BIT * 0U + 4, 0);
    test_mem({0xAA, 0x55}, CHAR_BIT * 0U + 5, 1);
    test_mem({0xAA, 0x55}, CHAR_BIT * 0U + 6, 0);
    test_mem({0xAA, 0x55}, CHAR_BIT * 0U + 7, 1);
    test_mem({0xAA, 0x55}, CHAR_BIT * 1U + 0, 1);
    test_mem({0xAA, 0x55}, CHAR_BIT * 1U + 1, 0);
    test_mem({0xAA, 0x55}, CHAR_BIT * 1U + 2, 1);
    test_mem({0xAA, 0x55}, CHAR_BIT * 1U + 3, 0);
    test_mem({0xAA, 0x55}, CHAR_BIT * 1U + 4, 1);
    test_mem({0xAA, 0x55}, CHAR_BIT * 1U + 5, 0);
    test_mem({0xAA, 0x55}, CHAR_BIT * 1U + 6, 1);
    test_mem({0xAA, 0x55}, CHAR_BIT * 1U + 7, 0);

  } catch (fail const &) {
    return TEST_EXIT_FAIL;
  } catch (...) {
    return TEST_EXIT_ERROR;
  }
  return TEST_EXIT_PASS;
}
