//
// Copyright (C) 2012-2023 Stealth Software Technologies, Inc.
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice (including
// the next paragraph) shall be included in all copies or
// substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// SPDX-License-Identifier: MIT
//

#include <TEST_EXIT.h>
#include <sst/config.h>
#include <sst/catalog/bignum.hpp>
#include <sst/catalog/type_max.hpp>
#include <sst/catalog/type_min.hpp>

#if SST_WITH_OPENSSL_CRYPTO

#include <climits>
#include <exception>
#include <iostream>
#include <string>
#include <type_traits>

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

#define TEST(x) test(x, #x)

} // namespace

int main() {
  try {
    std::cout.exceptions(std::cout.badbit | std::cout.failbit);

    sst::bignum x;
    sst::bignum y;

#define GO2(T, v)                                                      \
  TEST(static_cast<T>(sst::bignum(static_cast<T>(v)))                  \
       == static_cast<T>(v));

#define GO(T)                                                          \
  do {                                                                 \
    if (std::is_signed<T>::value) {                                    \
      GO2(T, 0);                                                       \
      GO2(T, 123);                                                     \
      GO2(T, -123);                                                    \
      GO2(T, sst::type_min<T>::value);                                 \
      GO2(T, sst::type_max<T>::value);                                 \
    } else {                                                           \
      GO2(T, 0);                                                       \
      GO2(T, 123);                                                     \
      GO2(T, sst::type_max<T>::value);                                 \
    }                                                                  \
  } while (false)

    GO(bool);
    GO(char);
    GO(signed char);
    GO(unsigned char);
    GO(short);
    GO(unsigned short);
    GO(int);
    GO(unsigned int);
    GO(long);
    GO(unsigned long);
    GO(long long);
    GO(unsigned long long);

#undef GO
#undef GO2

    TEST(sst::bignum(0).to_string() == "0");
    TEST(sst::bignum(123).to_string() == "123");
    TEST(sst::bignum(-123).to_string() == "-123");

    TEST(sst::bignum("0") == 0);
    TEST(sst::bignum("+0") == 0);
    TEST(sst::bignum("-0") == 0);
    TEST(sst::bignum("123") == 123);
    TEST(sst::bignum("+123") == 123);
    TEST(sst::bignum("-123") == -123);
    TEST(sst::bignum("1'23") == 123);
    TEST(sst::bignum("12'3") == 123);
    TEST(sst::bignum("1'2'3") == 123);
    TEST(sst::bignum("+1'23") == 123);
    TEST(sst::bignum("+12'3") == 123);
    TEST(sst::bignum("+1'2'3") == 123);
    TEST(sst::bignum("-1'23") == -123);
    TEST(sst::bignum("-12'3") == -123);
    TEST(sst::bignum("-1'2'3") == -123);

    TEST(sst::bignum("0b0") == 0);
    TEST(sst::bignum("+0b0") == 0);
    TEST(sst::bignum("-0b0") == 0);
    TEST(sst::bignum("0b101") == 5);
    TEST(sst::bignum("+0b101") == 5);
    TEST(sst::bignum("-0b101") == -5);
    TEST(sst::bignum("0b1'01") == 5);
    TEST(sst::bignum("0b10'1") == 5);
    TEST(sst::bignum("0b1'0'1") == 5);
    TEST(sst::bignum("+0b1'01") == 5);
    TEST(sst::bignum("+0b10'1") == 5);
    TEST(sst::bignum("+0b1'0'1") == 5);
    TEST(sst::bignum("-0b1'01") == -5);
    TEST(sst::bignum("-0b10'1") == -5);
    TEST(sst::bignum("-0b1'0'1") == -5);

    TEST(sst::bignum("0B0") == 0);
    TEST(sst::bignum("+0B0") == 0);
    TEST(sst::bignum("-0B0") == 0);
    TEST(sst::bignum("0B101") == 5);
    TEST(sst::bignum("+0B101") == 5);
    TEST(sst::bignum("-0B101") == -5);
    TEST(sst::bignum("0B1'01") == 5);
    TEST(sst::bignum("0B10'1") == 5);
    TEST(sst::bignum("0B1'0'1") == 5);
    TEST(sst::bignum("+0B1'01") == 5);
    TEST(sst::bignum("+0B10'1") == 5);
    TEST(sst::bignum("+0B1'0'1") == 5);
    TEST(sst::bignum("-0B1'01") == -5);
    TEST(sst::bignum("-0B10'1") == -5);
    TEST(sst::bignum("-0B1'0'1") == -5);

    TEST(sst::bignum("0o0") == 0);
    TEST(sst::bignum("+0o0") == 0);
    TEST(sst::bignum("-0o0") == 0);
    TEST(sst::bignum("0o123") == 83);
    TEST(sst::bignum("+0o123") == 83);
    TEST(sst::bignum("-0o123") == -83);
    TEST(sst::bignum("0o1'23") == 83);
    TEST(sst::bignum("0o12'3") == 83);
    TEST(sst::bignum("0o1'2'3") == 83);
    TEST(sst::bignum("+0o1'23") == 83);
    TEST(sst::bignum("+0o12'3") == 83);
    TEST(sst::bignum("+0o1'2'3") == 83);
    TEST(sst::bignum("-0o1'23") == -83);
    TEST(sst::bignum("-0o12'3") == -83);
    TEST(sst::bignum("-0o1'2'3") == -83);

    TEST(sst::bignum("0O0") == 0);
    TEST(sst::bignum("+0O0") == 0);
    TEST(sst::bignum("-0O0") == 0);
    TEST(sst::bignum("0O123") == 83);
    TEST(sst::bignum("+0O123") == 83);
    TEST(sst::bignum("-0O123") == -83);
    TEST(sst::bignum("0O1'23") == 83);
    TEST(sst::bignum("0O12'3") == 83);
    TEST(sst::bignum("0O1'2'3") == 83);
    TEST(sst::bignum("+0O1'23") == 83);
    TEST(sst::bignum("+0O12'3") == 83);
    TEST(sst::bignum("+0O1'2'3") == 83);
    TEST(sst::bignum("-0O1'23") == -83);
    TEST(sst::bignum("-0O12'3") == -83);
    TEST(sst::bignum("-0O1'2'3") == -83);

    TEST(sst::bignum("0x0") == 0);
    TEST(sst::bignum("+0x0") == 0);
    TEST(sst::bignum("-0x0") == 0);
    TEST(sst::bignum("0x123") == 291);
    TEST(sst::bignum("+0x123") == 291);
    TEST(sst::bignum("-0x123") == -291);
    TEST(sst::bignum("0x1'23") == 291);
    TEST(sst::bignum("0x12'3") == 291);
    TEST(sst::bignum("0x1'2'3") == 291);
    TEST(sst::bignum("+0x1'23") == 291);
    TEST(sst::bignum("+0x12'3") == 291);
    TEST(sst::bignum("+0x1'2'3") == 291);
    TEST(sst::bignum("-0x1'23") == -291);
    TEST(sst::bignum("-0x12'3") == -291);
    TEST(sst::bignum("-0x1'2'3") == -291);

    TEST(sst::bignum("0X0") == 0);
    TEST(sst::bignum("+0X0") == 0);
    TEST(sst::bignum("-0X0") == 0);
    TEST(sst::bignum("0X123") == 291);
    TEST(sst::bignum("+0X123") == 291);
    TEST(sst::bignum("-0X123") == -291);
    TEST(sst::bignum("0X1'23") == 291);
    TEST(sst::bignum("0X12'3") == 291);
    TEST(sst::bignum("0X1'2'3") == 291);
    TEST(sst::bignum("+0X1'23") == 291);
    TEST(sst::bignum("+0X12'3") == 291);
    TEST(sst::bignum("+0X1'2'3") == 291);
    TEST(sst::bignum("-0X1'23") == -291);
    TEST(sst::bignum("-0X12'3") == -291);
    TEST(sst::bignum("-0X1'2'3") == -291);

    TEST((x = 1, x++ == 1 && x == 2));
    TEST((x = 1, ++x == 2 && x == 2));
    TEST((x = 1, x-- == 1 && x == 0));
    TEST((x = 1, --x == 0 && x == 0));
    TEST((x = 1, +x == 1));
    TEST((x = 1, -x == -1));
    TEST((x = 1,
          std::is_same<decltype(!x), bool>::value && !x == false));
    TEST((x = 1,
          std::is_same<decltype(!!x), bool>::value && !!x == true));

    TEST((x = 17, y = 3, x * y == 51 && x == 17 && y == 3));
    TEST((x = 17, y = 3, (x *= y) == 51 && x == 51 && y == 3));
    TEST((x = -17, y = 3, x * y == -51 && x == -17 && y == 3));
    TEST((x = -17, y = 3, (x *= y) == -51 && x == -51 && y == 3));
    TEST((x = 17, y = -3, x * y == -51 && x == 17 && y == -3));
    TEST((x = 17, y = -3, (x *= y) == -51 && x == -51 && y == -3));
    TEST((x = -17, y = -3, x * y == 51 && x == -17 && y == -3));
    TEST((x = -17, y = -3, (x *= y) == 51 && x == 51 && y == -3));

    TEST((x = 17, y = 3, x / y == 5 && x == 17 && y == 3));
    TEST((x = 17, y = 3, (x /= y) == 5 && x == 5 && y == 3));
    TEST((x = -17, y = 3, x / y == -5 && x == -17 && y == 3));
    TEST((x = -17, y = 3, (x /= y) == -5 && x == -5 && y == 3));
    TEST((x = 17, y = -3, x / y == -5 && x == 17 && y == -3));
    TEST((x = 17, y = -3, (x /= y) == -5 && x == -5 && y == -3));
    TEST((x = -17, y = -3, x / y == 5 && x == -17 && y == -3));
    TEST((x = -17, y = -3, (x /= y) == 5 && x == 5 && y == -3));

    TEST((x = 17, y = 3, x % y == 2 && x == 17 && y == 3));
    TEST((x = 17, y = 3, (x %= y) == 2 && x == 2 && y == 3));
    TEST((x = -17, y = 3, x % y == -2 && x == -17 && y == 3));
    TEST((x = -17, y = 3, (x %= y) == -2 && x == -2 && y == 3));
    TEST((x = 17, y = -3, x % y == 2 && x == 17 && y == -3));
    TEST((x = 17, y = -3, (x %= y) == 2 && x == 2 && y == -3));
    TEST((x = -17, y = -3, x % y == -2 && x == -17 && y == -3));
    TEST((x = -17, y = -3, (x %= y) == -2 && x == -2 && y == -3));

    TEST((x = 17, y = 3, x + y == 20 && x == 17 && y == 3));
    TEST((x = 17, y = 3, (x += y) == 20 && x == 20 && y == 3));
    TEST((x = -17, y = 3, x + y == -14 && x == -17 && y == 3));
    TEST((x = -17, y = 3, (x += y) == -14 && x == -14 && y == 3));
    TEST((x = 17, y = -3, x + y == 14 && x == 17 && y == -3));
    TEST((x = 17, y = -3, (x += y) == 14 && x == 14 && y == -3));
    TEST((x = -17, y = -3, x + y == -20 && x == -17 && y == -3));
    TEST((x = -17, y = -3, (x += y) == -20 && x == -20 && y == -3));

    TEST((x = 17, y = 3, x - y == 14 && x == 17 && y == 3));
    TEST((x = 17, y = 3, (x -= y) == 14 && x == 14 && y == 3));
    TEST((x = -17, y = 3, x - y == -20 && x == -17 && y == 3));
    TEST((x = -17, y = 3, (x -= y) == -20 && x == -20 && y == 3));
    TEST((x = 17, y = -3, x - y == 20 && x == 17 && y == -3));
    TEST((x = 17, y = -3, (x -= y) == 20 && x == 20 && y == -3));
    TEST((x = -17, y = -3, x - y == -14 && x == -17 && y == -3));
    TEST((x = -17, y = -3, (x -= y) == -14 && x == -14 && y == -3));

    TEST((x = 17, (x << 2) == 68 && x == 17));
    TEST((x = 17, (x <<= 2) == 68 && x == 68));

    TEST((x = 17, (x << sst::bignum(2)) == 68 && x == 17));
    TEST((x = 17, (x <<= sst::bignum(2)) == 68 && x == 68));

    TEST((x = 17, (x >> 2) == 4 && x == 17));
    TEST((x = 17, (x >>= 2) == 4 && x == 4));

    TEST((x = 17, (x >> sst::bignum(2)) == 4 && x == 17));
    TEST((x = 17, (x >>= sst::bignum(2)) == 4 && x == 4));

    TEST((sst::bignum("0x100000000000000000000000000000") >> 116) == 1);
    TEST(((sst::bignum(1) << 1234) >> 1230) == 16);
    TEST((sst::bignum(1) >> INT_MAX) == 0);

    TEST(sst::bignum(std::vector<unsigned char>{0}) == 0);
    TEST(sst::bignum(std::vector<unsigned char>{0, 0}) == 0);
    TEST(sst::bignum(std::vector<unsigned char>{1, 0}) == 1);
    TEST(sst::bignum(std::vector<unsigned char>{0, 1})
         == sst::bignum(UCHAR_MAX) + 1);
    TEST(sst::bignum(std::vector<unsigned char>{UCHAR_MAX}) == -1);
    TEST(sst::bignum(std::vector<unsigned char>{UCHAR_MAX - 1}) == -2);
    TEST(sst::bignum(std::vector<unsigned char>{UCHAR_MAX},
                     sst::integer_rep::pure_unsigned())
         == UCHAR_MAX);

    TEST(~sst::bignum(-8) == 7);
    TEST(~sst::bignum(-7) == 6);
    TEST(~sst::bignum(-6) == 5);
    TEST(~sst::bignum(-5) == 4);
    TEST(~sst::bignum(-4) == 3);
    TEST(~sst::bignum(-3) == 2);
    TEST(~sst::bignum(-2) == 1);
    TEST(~sst::bignum(-1) == 0);
    TEST(~sst::bignum(0) == -1);
    TEST(~sst::bignum(1) == -2);
    TEST(~sst::bignum(2) == -3);
    TEST(~sst::bignum(3) == -4);
    TEST(~sst::bignum(4) == -5);
    TEST(~sst::bignum(5) == -6);
    TEST(~sst::bignum(6) == -7);
    TEST(~sst::bignum(7) == -8);

    TEST((sst::bignum(0) & 0) == 0);
    TEST((sst::bignum(1) & 0) == 0);
    TEST((sst::bignum(-1) & 0) == 0);
    TEST((sst::bignum(UCHAR_MAX) & 0) == 0);
    TEST((sst::bignum(SCHAR_MIN) & 0) == 0);

    TEST((sst::bignum(0) & 1) == 0);
    TEST((sst::bignum(1) & 1) == 1);
    TEST((sst::bignum(-1) & 1) == 1);
    TEST((sst::bignum(UCHAR_MAX) & 1) == 1);
    TEST((sst::bignum(SCHAR_MIN) & 1) == 0);

    TEST((sst::bignum(0) ^ 1) == 1);
    TEST((sst::bignum(1) ^ 1) == 0);
    TEST((sst::bignum(-1) ^ 1) == -2);
    TEST((sst::bignum(UCHAR_MAX) ^ 1) == UCHAR_MAX - 1);
    TEST((sst::bignum(SCHAR_MIN) ^ 1) == SCHAR_MIN + 1);

    TEST((sst::bignum(0) | 0) == 0);
    TEST((sst::bignum(1) | 0) == 1);
    TEST((sst::bignum(-1) | 0) == -1);
    TEST((sst::bignum(UCHAR_MAX) | 0) == UCHAR_MAX);
    TEST((sst::bignum(SCHAR_MIN) | 0) == SCHAR_MIN);

    TEST((sst::bignum(0) | 1) == 1);
    TEST((sst::bignum(1) | 1) == 1);
    TEST((sst::bignum(-1) | 1) == -1);
    TEST((sst::bignum(UCHAR_MAX) | 1) == UCHAR_MAX);
    TEST((sst::bignum(SCHAR_MIN) | 1) == SCHAR_MIN + 1);

    //
    // Test that converting to unsigned integer types is modular.
    //

    TEST(static_cast<unsigned char>(sst::bignum(UCHAR_MAX) + 1) == 0);
    TEST(static_cast<unsigned char>(sst::bignum(UCHAR_MAX) + 2) == 1);
    TEST(static_cast<unsigned char>(sst::bignum(UCHAR_MAX) + 3) == 2);
    TEST(static_cast<unsigned char>(sst::bignum(-1)) == UCHAR_MAX);
    TEST(static_cast<unsigned char>(sst::bignum(-2)) == UCHAR_MAX - 1);
    TEST(static_cast<unsigned char>(sst::bignum(-3)) == UCHAR_MAX - 2);

    TEST(static_cast<unsigned int>(sst::bignum(UINT_MAX) + 1) == 0);
    TEST(static_cast<unsigned int>(sst::bignum(UINT_MAX) + 2) == 1);
    TEST(static_cast<unsigned int>(sst::bignum(UINT_MAX) + 3) == 2);
    TEST(static_cast<unsigned int>(sst::bignum(-1)) == UINT_MAX);
    TEST(static_cast<unsigned int>(sst::bignum(-2)) == UINT_MAX - 1);
    TEST(static_cast<unsigned int>(sst::bignum(-3)) == UINT_MAX - 2);

    //------------------------------------------------------------------
    // sst::bignum::pow_mod
    //------------------------------------------------------------------

#define X(a, b, m, r)                                                  \
  ([&]() {                                                             \
    TEST(sst::bignum::pow_mod((a), (b), (m)) == (r));                  \
    TEST(sst::bignum((a)).pow_mod((b), (m)) == (r));                   \
    TEST(pow_mod(sst::bignum((a)), (b), (m)) == (r));                  \
  })()

    X(1, 0, 1, 0);
    X(1, 1, 1, 0);
    X(1, 2, 1, 0);
    X(1, 0, 1, 0);
    X(1, 1, 1, 0);
    X(1, 2, 1, 0);
    X(2, 0, 1, 0);
    X(2, 1, 1, 0);
    X(2, 2, 1, 0);
    X(1, 0, 2, 1);
    X(1, 1, 2, 1);
    X(1, 2, 2, 1);
    X(2, 0, 2, 1);
    X(2, 1, 2, 0);
    X(2, 2, 2, 0);
    X(1, 0, 3, 1);
    X(1, 1, 3, 1);
    X(1, 2, 3, 1);
    X(2, 0, 3, 1);
    X(2, 1, 3, 2);
    X(2, 2, 3, 1);

    X(2, 3, 7, 1);

#undef X

    //------------------------------------------------------------------

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

#else // !SST_WITH_OPENSSL_CRYPTO

#include <sst/catalog/test_skip.hpp>

int main() {
  return sst::test_skip();
}

#endif // !SST_WITH_OPENSSL_CRYPTO
