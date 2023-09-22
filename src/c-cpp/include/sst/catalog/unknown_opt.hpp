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

#ifndef SST_CATALOG_UNKNOWN_OPT_HPP
#define SST_CATALOG_UNKNOWN_OPT_HPP

#include <cassert>

#include <sst/catalog/opt_exception.hpp>
#include <sst/catalog/string_to_string_options.hpp>
#include <sst/catalog/to_string.hpp>

namespace sst {

template<class StringList>
void unknown_opt(StringList const & args) {
  using String = typename StringList::value_type;
  using CharT = typename String::value_type;
  assert(args.size() > 0);
  String const & arg = args.front();
  auto n = arg.size();
  if (n > 1 && arg[0] == CharT('-')) {
    if (arg[1] == CharT('-')) {
      n = arg.find(CharT('='));
    } else {
      n = 2;
    }
    throw opt_exception(
        "unknown option: "
        + sst::to_string(
            arg.substr(0, n),
            sst::string_to_string_options().replace_unrepresentable(
                true)));
  }
}

} // namespace sst

#endif // SST_CATALOG_UNKNOWN_OPT_HPP
