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

#ifndef SST_CATALOG_PARSE_OPT_HPP
#define SST_CATALOG_PARSE_OPT_HPP

#include <cassert>
#include <initializer_list>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

#include <sst/catalog/SST_COMPILES.hpp>
#include <sst/catalog/SST_STATIC_ASSERT.h>
#include <sst/catalog/enable_if.hpp>
#include <sst/catalog/opt_arg.hpp>
#include <sst/catalog/opt_exception.hpp>
#include <sst/catalog/perfect_lt.hpp>
#include <sst/catalog/string_to_string_options.hpp>
#include <sst/catalog/to_string.hpp>
#include <sst/catalog/type_max.hpp>
#include <sst/catalog/type_min.hpp>
#include <sst/catalog/unsigned_le.hpp>

namespace sst {

template<class StringList,
         class Matcher,
         typename sst::enable_if<SST_COMPILES(std::declval<Matcher>()(
             std::declval<StringList>().front()))>::type = 0>
bool parse_opt(StringList & args,
               Matcher const & matcher,
               opt_arg const style = opt_arg::required,
               bool * const has_arg = nullptr) {
  using String = typename StringList::value_type;
  using CharT = typename String::value_type;
  SST_STATIC_ASSERT((std::is_same<decltype(matcher(args.front())),
                                  typename String::size_type>::value));
  assert(args.size() > 0);
  auto const n = matcher(args.front());
  assert(n >= 0);
  if (n == 0) {
    return false;
  }
  assert(sst::unsigned_le(n, args.front().size()));
  assert(args.front()[0] == CharT('-'));
  bool const is_long = n > 1 && args.front()[1] == CharT('-');
  if (is_long) {
    for (decltype(+n) i = 0; i != n; ++i) {
      assert(args.front()[i] != CharT('='));
    }
  } else {
    assert(n == 2);
  }

  if (args.front().size() == n) {
    if (style == opt_arg::required) {
      if (args.size() < 2) {
        throw opt_exception(
            "option requires an argument: "
            + sst::to_string(
                args.front().substr(0, n),
                sst::string_to_string_options().replace_unrepresentable(
                    true)));
      }
      args.pop_front();
      if (has_arg != nullptr) {
        *has_arg = true;
      }
    } else {
      args.front().clear();
      if (has_arg != nullptr) {
        *has_arg = false;
      }
    }
    return true;
  }

  if (is_long) {
    if (args.front()[n] != CharT('=')) {
      return false;
    }
    if (style == opt_arg::forbidden) {
      throw opt_exception(
          "option forbids an argument: "
          + sst::to_string(
              args.front().substr(0, n),
              sst::string_to_string_options().replace_unrepresentable(
                  true)));
    }
    args.front() = args.front().substr(n + 1);
    if (has_arg != nullptr) {
      *has_arg = true;
    }
    return true;
  }

  if (style == opt_arg::forbidden) {
    args.front() = CharT('-') + args.front().substr(2);
    args.emplace_front();
    if (has_arg != nullptr) {
      *has_arg = false;
    }
  } else {
    args.front() = args.front().substr(2);
    if (has_arg != nullptr) {
      *has_arg = true;
    }
  }
  return true;
}

template<class StringList,
         class String,
         typename sst::enable_if<
             SST_COMPILES(std::declval<String>().c_str())>::type = 0>
bool parse_opt(StringList & args,
               String const & opt,
               opt_arg const style = opt_arg::required,
               bool * const has_arg = nullptr) {
  SST_STATIC_ASSERT(
      (std::is_same<String, typename StringList::value_type>::value));
  using CharT = typename String::value_type;
  assert(opt.size() > 0);
  assert(opt[0] == CharT('-'));
  bool const is_long = opt.size() > 1 && opt[1] == CharT('-');
  if (is_long) {
    assert(opt.find(CharT('=')) == opt.npos);
  } else {
    assert(opt.size() == 2);
  }
  return parse_opt(
      args,
      [&](String const & arg) {
        if (arg.rfind(opt, 0) == 0) {
          return opt.size();
        }
        return decltype(opt.size())(0);
      },
      style,
      has_arg);
}

template<class StringList, class CharT>
bool parse_opt(StringList & args,
               CharT const * const opt,
               opt_arg const style = opt_arg::required,
               bool * const has_arg = nullptr) {
  assert(opt != nullptr);
  return parse_opt(args, std::basic_string<CharT>(opt), style, has_arg);
}

template<class StringList, class String1, class String2>
bool parse_opt(StringList & args,
               std::initializer_list<String1> const opts,
               String2 * const parsed_opt = nullptr,
               opt_arg const style = opt_arg::required,
               bool * const has_arg = nullptr) {
  for (auto const & opt : opts) {
    if (parse_opt(args, opt, style, has_arg)) {
      if (parsed_opt != nullptr) {
        *parsed_opt = opt;
      }
      return true;
    }
  }
  return false;
}

template<class StringList, class String>
bool parse_opt(StringList & args,
               std::initializer_list<String> const opts,
               opt_arg const style = opt_arg::required,
               bool * const has_arg = nullptr) {
  return parse_opt(args,
                   opts,
                   static_cast<String *>(nullptr),
                   style,
                   has_arg);
}

} // namespace sst

#endif // #ifndef SST_CATALOG_PARSE_OPT_HPP
