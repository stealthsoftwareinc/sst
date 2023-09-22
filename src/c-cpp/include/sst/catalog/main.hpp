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

#ifndef SST_CATALOG_MAIN_HPP
#define SST_CATALOG_MAIN_HPP

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <utility>

#include <sst/catalog/invoke.hpp>
#include <sst/catalog/what.hpp>

namespace sst {

// TODO: Call set_terminate and set_unexpected so they can use
//       sst::what()? The user can still call them to set them
//       themselves, so this shouldn't cause any problems?

// TODO: Print out something nice for sst::tracing_exception? What even
//       currently happens?

// TODO: Support func returning int.

template<class Func, class... Args>
int main(int const argc,
         char * const * const argv,
         Func && func,
         Args &&... args) noexcept {
  try {
    // func might modify argv, so we immediately make a copy of argv[0]
    // to use in error messages. For example, if func modifies argv[0]
    // and then throws an exception, trying to read argv[0] at that
    // point might be wrong.
    bool const have_argv0 = argc > 0;
    std::string argv0;
    if (have_argv0) {
      argv0 = argv[0];
    }
    try {
      std::cout.exceptions(std::cout.badbit | std::cout.failbit);
      static_cast<void>(sst::invoke(std::forward<Func>(func),
                                    std::forward<Args>(args)...));
      std::cout.flush();
      return EXIT_SUCCESS;
    } catch (...) {
      try {
        if (have_argv0) {
          std::cerr << argv0 << ": ";
        }
        std::cerr << "Error: ";
        std::cerr << sst::what() << "\n";
      } catch (...) {
      }
      return EXIT_FAILURE;
    }
  } catch (...) {
    // Something went wrong initializing the argv0 string. We know that
    // we haven't called func yet, so argv must be unchanged and we can
    // safely fall back to reading argv[0].
    try {
      if (argv[0] != nullptr) {
        std::cerr << argv[0] << ": ";
      }
      std::cerr << "Error: ";
      std::cerr << sst::what() << "\n";
    } catch (...) {
    }
    return EXIT_FAILURE;
  }
}

} // namespace sst

#endif // SST_CATALOG_MAIN_HPP
