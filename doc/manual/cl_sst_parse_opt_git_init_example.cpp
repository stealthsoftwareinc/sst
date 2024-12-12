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

#include <cstdlib>
#include <exception>
#include <iostream>
#include <list>
#include <link:{repo_browser_url}/src/c-cpp/include/sst/catalog/opt_arg.hpp[sst/catalog/opt_arg.hpp,window=_blank]>
#include <link:{repo_browser_url}/src/c-cpp/include/sst/catalog/parse_opt.hpp[sst/catalog/parse_opt.hpp,window=_blank]>
#include <link:{repo_browser_url}/src/c-cpp/include/sst/catalog/unknown_opt.hpp[sst/catalog/unknown_opt.hpp,window=_blank]>
#include <stdexcept>
#include <string>
#include <utility>

int main(int const argc, char ** const argv) {
  char const * const argv0 = argc > 0 ? argv[0] : "example";
  try {
    std::list<std::string> args(argv, argv + argc);
    if (args.empty()) {
      throw std::runtime_error("argc is zero");
    }
    bool parse_options = true;
    std::string directory = ".";
    bool directory_given = false;
    while (args.pop_front(), !args.empty()) {
      if (parse_options) {
        bool has_arg;
        if (sst::parse_opt(args, "--", sst::opt_arg::forbidden)) {
          parse_options = false;
          continue;
        }
        if (sst::parse_opt(args,
                           {"-q", "--quiet"},
                           sst::opt_arg::forbidden)) {
          // ...
          continue;
        }
        if (sst::parse_opt(args, "--bare", sst::opt_arg::forbidden)) {
          // ...
          continue;
        }
        if (sst::parse_opt(args, "--object-format")) {
          std::string & arg = args.front();
          // ...
          continue;
        }
        if (sst::parse_opt(args, "--template")) {
          std::string & arg = args.front();
          // ...
          continue;
        }
        if (sst::parse_opt(args, "--separate-git-dir")) {
          std::string & arg = args.front();
          // ...
          continue;
        }
        if (sst::parse_opt(args, {"-b", "--initial-branch"})) {
          std::string & arg = args.front();
          // ...
          continue;
        }
        if (sst::parse_opt(args,
                           "--shared",
                           sst::opt_arg::permitted,
                           &has_arg)) {
          std::string arg = has_arg ? std::move(args.front()) : "group";
          // ...
          continue;
        }
        sst::unknown_opt(args);
      }
      if (directory_given) {
        throw std::runtime_error("directory given twice");
      }
      directory = std::move(args.front());
      directory_given = true;
    }
    std::cout << "ok\n";
  } catch (std::exception const & e) {
    try {
      std::cerr << argv0 << ": " << e.what() << "\n";
    } catch (...) {
    }
    return EXIT_FAILURE;
  } catch (...) {
    try {
      std::cerr << argv0 << ": unknown error\n";
    } catch (...) {
    }
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
