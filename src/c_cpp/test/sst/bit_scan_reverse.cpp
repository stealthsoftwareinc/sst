//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#include <TEST_EXIT.h>
#include <iostream>
#include <limits>
#include <sst/catalog/bit_scan_reverse.hpp>
#include <sst/catalog/type_max.hpp>
#include <sst/catalog/type_min.hpp>
#include <sst/catalog/value_bits.hpp>
#include <string>

namespace {

struct fail {};

void test2(bool const x, std::string const & x_str) {
  if (x) {
    std::cout << "pass: " << x_str << std::endl;
  } else {
    std::cout << "fail: " << x_str << std::endl;
    throw fail();
  }
}

template<class T>
void test(std::string const & T_str) {
  if (std::is_signed<T>::value) {
    for (T x = sst::type_min<T>::value; x != 0; x /= 2) {
      test2(sst::bit_scan_reverse(x) == sst::value_bits<T>::value,
            "sst::bit_scan_reverse(static_cast<" + T_str + ">("
                + std::to_string(x)
                + ")) == " + std::to_string(sst::value_bits<T>::value));
      test2(sst::_::bit_scan_reverse::fallback(x)
                == sst::value_bits<T>::value,
            "sst::_::bit_scan_reverse::fallback(static_cast<" + T_str
                + ">(" + std::to_string(x)
                + ")) == " + std::to_string(sst::value_bits<T>::value));
    }
  }
  int i = sst::value_bits<T>::value - 1;
  for (T x = sst::type_max<T>::value; x != 0; x /= 2) {
    test2(sst::bit_scan_reverse(x) == i,
          "sst::bit_scan_reverse(static_cast<" + T_str + ">("
              + std::to_string(x) + ")) == " + std::to_string(i));
    test2(sst::_::bit_scan_reverse::fallback(x) == i,
          "sst::_::bit_scan_reverse::fallback(static_cast<" + T_str
              + ">(" + std::to_string(x)
              + ")) == " + std::to_string(i));
    --i;
  }
}

#define TEST(T) test<T>(#T)

} // namespace

int main() {
  try {

    TEST(signed char);
    TEST(unsigned char);
    TEST(short);
    TEST(unsigned short);
    TEST(int);
    TEST(unsigned int);
    TEST(long);
    TEST(unsigned long);
    TEST(long long);
    TEST(unsigned long long);

  } catch (fail const &) {
    return TEST_EXIT_FAIL;
  } catch (...) {
    return TEST_EXIT_ERROR;
  }
  return TEST_EXIT_PASS;
}
