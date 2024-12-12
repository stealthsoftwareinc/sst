dnl#
dnl# Copyright (C) 2012-2024 Stealth Software Technologies, Inc.
dnl#
dnl# Permission is hereby granted, free of charge, to any person
dnl# obtaining a copy of this software and associated documentation
dnl# files (the "Software"), to deal in the Software without
dnl# restriction, including without limitation the rights to use,
dnl# copy, modify, merge, publish, distribute, sublicense, and/or
dnl# sell copies of the Software, and to permit persons to whom the
dnl# Software is furnished to do so, subject to the following
dnl# conditions:
dnl#
dnl# The above copyright notice and this permission notice (including
dnl# the next paragraph) shall be included in all copies or
dnl# substantial portions of the Software.
dnl#
dnl# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
dnl# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
dnl# OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
dnl# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
dnl# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
dnl# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
dnl# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
dnl# OTHER DEALINGS IN THE SOFTWARE.
dnl#
dnl# SPDX-License-Identifier: MIT
dnl#

AC_DEFUN_ONCE([DEFINE_WITH_NLOHMANN_JSON], [[
]GATBPS_CALL_COMMENT([$0]m4_if(m4_eval([$# > 0]), [1], [, $@]))[
{ :

  ]GATBPS_REQUIRE([DEFINE_DEDUCE_WYNAS])[
  ]GATBPS_REQUIRE([DEFINE_CPPFLAGS], [soft])[
  ]GATBPS_REQUIRE([DEFINE_CXXFLAGS], [soft])[
  ]GATBPS_REQUIRE([DEFINE_WITH_BUILD_GROUPS], [soft])[

  ]GATBPS_FINISH_WYNA(
    [--with-nlohmann-json],
    [WYNA_NLOHMANN_JSON])[

  ]m4_pushdef(
    [prologue],
    [[
      #include <nlohmann/json.hpp>
    ]])[

  ]m4_pushdef(
    [body],
    [[
      nlohmann::json j;
      (void)j;
    ]])[

  ]AC_LANG_PUSH([C++])[

  ]GATBPS_CHECK_COMPILE(
    [for the JSON for Modern C++ library (C++ compile)],
    [WITH_NLOHMANN_JSON_CPP_COMPILE],
    prologue,
    body,
    [(1
      && !WYNA_NLOHMANN_JSON_IS_NO
      && ]GATBPS_SOFT_VAR([WITH_BUILD_GROUP_CPP_AUTOTOOLS])[
    )])[

  ]AC_LANG_POP([C++])[

  ]m4_popdef([body])[
  ]m4_popdef([prologue])[

  ]GATBPS_CHECK_EXPR(
    [whether to use the JSON for Modern C++ library],
    [WITH_NLOHMANN_JSON],
    [(1
      && ]GATBPS_SOFT_VAR([WITH_BUILD_GROUP_CPP_AUTOTOOLS])[
      && WITH_NLOHMANN_JSON_CPP_COMPILE
    )])[

  x=
  x=$][{x?}$][{WYNA_NLOHMANN_JSON_IS_YES?}
  x=$][{x?}$][{WITH_NLOHMANN_JSON?}
  case $][{x?} in 10)
    ]GATBPS_BARF([
      The JSON for Modern C++ library is not available.
    ])[
  esac

}]])
