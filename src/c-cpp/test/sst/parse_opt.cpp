//
// Copyright (C) 2012-2024 Stealth Software Technologies, Inc.
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
#include <iostream>
#include <list>
#include <sst/catalog/parse_opt.hpp>
#include <string>
#include <type_traits>

namespace {

struct fail {};

void test3(bool const x, std::string const & x_str) {
  if (x) {
    std::cout << "pass: " << x_str << std::endl;
  } else {
    std::cout << "fail: " << x_str << std::endl;
    throw fail();
  }
}

#define TEST2(x) (test3((x), #x))

#define TEST(args2,                                                    \
             opt,                                                      \
             style,                                                    \
             expected_ret,                                             \
             expected_args,                                            \
             expected_has_arg)                                         \
  ([&]() {                                                             \
    bool ret;                                                          \
    decltype(args2) args;                                              \
    bool has_arg = false;                                              \
    TEST2((ret = sst::parse_opt(args = args2, opt, style, &has_arg),   \
           ret == expected_ret && args == expected_args                \
               && has_arg == expected_has_arg));                       \
  }())

#define THROWS(x, e)                                                   \
  ([&]() {                                                             \
    try {                                                              \
      (x);                                                             \
    } catch (e const &) {                                              \
      return true;                                                     \
    }                                                                  \
    return false;                                                      \
  }())

#define TEST_THROWS(args2, opt, style, e)                              \
  ([&]() {                                                             \
    decltype(args2) args;                                              \
    TEST2(THROWS(sst::parse_opt(args = args2, opt, style), e));        \
  }())

} // namespace

//
// The following sections of code are similar:
//
//     * The main function in <src/c-cpp/test/sst/parse_opt.cpp>.
//
//     * The testParseOpt method in
//       <src/java/com/stealthsoftwareinc/test/sst/ArgsTest.java>.
//
// If you edit one of these, you may need to edit the other.
//

int main() {
  try {

    //------------------------------------------------------------------
    // Match with required argument
    //------------------------------------------------------------------

    TEST(std::list<std::string>({"--x", "y"}),
         "--x",
         sst::opt_arg::required,
         true,
         std::list<std::string>({"y"}),
         true);

    TEST(std::list<std::string>({"--x=y"}),
         "--x",
         sst::opt_arg::required,
         true,
         std::list<std::string>({"y"}),
         true);

    TEST_THROWS(std::list<std::string>({"--x"}),
                "--x",
                sst::opt_arg::required,
                sst::opt_exception);

    TEST(std::list<std::string>({"-x", "y"}),
         "-x",
         sst::opt_arg::required,
         true,
         std::list<std::string>({"y"}),
         true);

    TEST(std::list<std::string>({"-xy"}),
         "-x",
         sst::opt_arg::required,
         true,
         std::list<std::string>({"y"}),
         true);

    TEST_THROWS(std::list<std::string>({"-x"}),
                "-x",
                sst::opt_arg::required,
                sst::opt_exception);

    //------------------------------------------------------------------
    // Match with permitted argument
    //------------------------------------------------------------------

    TEST(std::list<std::string>({"--x", "y"}),
         "--x",
         sst::opt_arg::permitted,
         true,
         std::list<std::string>({"", "y"}),
         false);

    TEST(std::list<std::string>({"--x=y"}),
         "--x",
         sst::opt_arg::permitted,
         true,
         std::list<std::string>({"y"}),
         true);

    TEST(std::list<std::string>({"--x"}),
         "--x",
         sst::opt_arg::permitted,
         true,
         std::list<std::string>({""}),
         false);

    TEST(std::list<std::string>({"-x", "y"}),
         "-x",
         sst::opt_arg::permitted,
         true,
         std::list<std::string>({"", "y"}),
         false);

    TEST(std::list<std::string>({"-xy"}),
         "-x",
         sst::opt_arg::permitted,
         true,
         std::list<std::string>({"y"}),
         true);

    TEST(std::list<std::string>({"-x"}),
         "-x",
         sst::opt_arg::permitted,
         true,
         std::list<std::string>({""}),
         false);

    //------------------------------------------------------------------
    // Match with forbidden argument
    //------------------------------------------------------------------

    TEST(std::list<std::string>({"--x", "y"}),
         "--x",
         sst::opt_arg::forbidden,
         true,
         std::list<std::string>({"", "y"}),
         false);

    TEST_THROWS(std::list<std::string>({"--x=y"}),
                "--x",
                sst::opt_arg::forbidden,
                sst::opt_exception);

    TEST(std::list<std::string>({"--x"}),
         "--x",
         sst::opt_arg::forbidden,
         true,
         std::list<std::string>({""}),
         false);

    TEST(std::list<std::string>({"-x", "y"}),
         "-x",
         sst::opt_arg::forbidden,
         true,
         std::list<std::string>({"", "y"}),
         false);

    TEST(std::list<std::string>({"-xy"}),
         "-x",
         sst::opt_arg::forbidden,
         true,
         std::list<std::string>({"", "-y"}),
         false);

    TEST(std::list<std::string>({"-x"}),
         "-x",
         sst::opt_arg::forbidden,
         true,
         std::list<std::string>({""}),
         false);

    //------------------------------------------------------------------
    // Mismatch
    //------------------------------------------------------------------

    TEST(std::list<std::string>({"--x", "y"}),
         "--z",
         sst::opt_arg::permitted,
         false,
         std::list<std::string>({"--x", "y"}),
         false);

    TEST(std::list<std::string>({"--x"}),
         "--z",
         sst::opt_arg::permitted,
         false,
         std::list<std::string>({"--x"}),
         false);

    TEST(std::list<std::string>({"--x=y"}),
         "--z",
         sst::opt_arg::permitted,
         false,
         std::list<std::string>({"--x=y"}),
         false);

    TEST(std::list<std::string>({"-x", "y"}),
         "-z",
         sst::opt_arg::permitted,
         false,
         std::list<std::string>({"-x", "y"}),
         false);

    TEST(std::list<std::string>({"-x"}),
         "-z",
         sst::opt_arg::permitted,
         false,
         std::list<std::string>({"-x"}),
         false);

    TEST(std::list<std::string>({"-xy"}),
         "-z",
         sst::opt_arg::permitted,
         false,
         std::list<std::string>({"-xy"}),
         false);

    TEST(std::list<std::string>({"--x", "y"}),
         "-x",
         sst::opt_arg::permitted,
         false,
         std::list<std::string>({"--x", "y"}),
         false);

    TEST(std::list<std::string>({"--x"}),
         "-x",
         sst::opt_arg::permitted,
         false,
         std::list<std::string>({"--x"}),
         false);

    TEST(std::list<std::string>({"--x=y"}),
         "-x",
         sst::opt_arg::permitted,
         false,
         std::list<std::string>({"--x=y"}),
         false);

    TEST(std::list<std::string>({"-x", "y"}),
         "--x",
         sst::opt_arg::permitted,
         false,
         std::list<std::string>({"-x", "y"}),
         false);

    TEST(std::list<std::string>({"-x"}),
         "--x",
         sst::opt_arg::permitted,
         false,
         std::list<std::string>({"-x"}),
         false);

    TEST(std::list<std::string>({"-xy"}),
         "--x",
         sst::opt_arg::permitted,
         false,
         std::list<std::string>({"-xy"}),
         false);

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
