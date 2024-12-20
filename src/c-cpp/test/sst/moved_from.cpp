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

#undef SST_COMPILE_TIME_TESTS
#define SST_COMPILE_TIME_TESTS 1

// Include first to test independence.
#include <sst/catalog/moved_from.hpp>
// Include twice to test idempotence.
#include <sst/catalog/moved_from.hpp>
//

#include <utility>

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/test_main.hpp>

int main() {
  return sst::test_main([&] {
    ;

    //------------------------------------------------------------------
    // Constructors
    //------------------------------------------------------------------

    SST_TEST_BOOL(([] {
      sst::guts::debug_moved_from x;
      return !x;
    }()));

    SST_TEST_BOOL(([] {
      sst::guts::debug_moved_from x(false);
      return !x;
    }()));

    SST_TEST_BOOL(([] {
      sst::guts::debug_moved_from x(true);
      return !!x;
    }()));

    //------------------------------------------------------------------
    // Copy constructor
    //------------------------------------------------------------------

    SST_TEST_BOOL(([] {
      sst::guts::debug_moved_from x;
      sst::guts::debug_moved_from y(x);
      return !y;
    }()));

    //------------------------------------------------------------------
    // Copy assignment
    //------------------------------------------------------------------

    SST_TEST_BOOL(([] {
      sst::guts::debug_moved_from x;
      sst::guts::debug_moved_from y(true);
      y = x;
      return !y;
    }()));

    //------------------------------------------------------------------
    // Move constructor
    //------------------------------------------------------------------

    SST_TEST_BOOL(([] {
      sst::guts::debug_moved_from x;
      sst::guts::debug_moved_from y(std::move(x));
      return !!x;
    }()));

    SST_TEST_BOOL(([] {
      sst::guts::debug_moved_from x;
      sst::guts::debug_moved_from y(std::move(x));
      return !y;
    }()));

    //------------------------------------------------------------------
    // Move assignment
    //------------------------------------------------------------------

    SST_TEST_BOOL(([] {
      sst::guts::debug_moved_from x;
      sst::guts::debug_moved_from y(true);
      y = std::move(x);
      return !!x;
    }()));

    SST_TEST_BOOL(([] {
      sst::guts::debug_moved_from x;
      sst::guts::debug_moved_from y(true);
      y = std::move(x);
      return !y;
    }()));

    //------------------------------------------------------------------
    // Assignment from bool
    //------------------------------------------------------------------

    SST_TEST_BOOL(([] {
      sst::guts::debug_moved_from x;
      x = true;
      return !!x;
    }()));

    SST_TEST_BOOL(([] {
      sst::guts::debug_moved_from x(true);
      x = false;
      return !x;
    }()));

    //------------------------------------------------------------------
  });
}
