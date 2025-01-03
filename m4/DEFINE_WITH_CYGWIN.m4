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

AC_DEFUN_ONCE([DEFINE_WITH_CYGWIN], [[
]GATBPS_CALL_COMMENT([$0]m4_if(m4_eval([$# > 0]), [1], [, $@]))[
{ :

  ]GATBPS_REQUIRE([DEFINE_CFLAGS], [soft])[
  ]GATBPS_REQUIRE([DEFINE_CPPFLAGS], [soft])[
  ]GATBPS_REQUIRE([DEFINE_CXXFLAGS], [soft])[
  ]GATBPS_REQUIRE([DEFINE_DEDUCE_WYNAS])[
  ]GATBPS_REQUIRE([DEFINE_WITH_BUILD_GROUPS], [soft])[

  ]m4_pushdef(
    [prologue],
    [[
    ]])[

  ]m4_pushdef(
    [body],
    [[
      #ifndef __CYGWIN__
      #include <cause_a_compilation_error>
      #endif
    ]])[

  ]AC_LANG_PUSH([C])[

  ]GATBPS_CHECK_COMPILE(
    [for Cygwin (C compile)],
    [HAVE_CYGWIN_C_COMPILE],
    prologue,
    body,
    [1
      && ]GATBPS_SOFT_VAR([WITH_BUILD_GROUP_C_AUTOTOOLS])[
    ])[

  ]AC_LANG_POP([C])[

  ]AC_LANG_PUSH([C++])[

  ]GATBPS_CHECK_COMPILE(
    [for Cygwin (C++ compile)],
    [HAVE_CYGWIN_CPP_COMPILE],
    prologue,
    body,
    [1
      && ]GATBPS_SOFT_VAR([WITH_BUILD_GROUP_CPP_AUTOTOOLS])[
    ])[

  ]AC_LANG_POP([C++])[

  ]m4_popdef([body])[
  ]m4_popdef([prologue])[

  ]GATBPS_CHECK_EXPR(
    [whether Cygwin is present],
    [HAVE_CYGWIN],
    [(1
      ) && (0
        || ]GATBPS_SOFT_VAR([WITH_BUILD_GROUP_C_AUTOTOOLS])[
        || ]GATBPS_SOFT_VAR([WITH_BUILD_GROUP_CPP_AUTOTOOLS])[
      ) && (0
        || !]GATBPS_SOFT_VAR([WITH_BUILD_GROUP_C_AUTOTOOLS])[
        || HAVE_CYGWIN_C_COMPILE
      ) && (0
        || !]GATBPS_SOFT_VAR([WITH_BUILD_GROUP_CPP_AUTOTOOLS])[
        || HAVE_CYGWIN_CPP_COMPILE
      )
    ])[

  ]GATBPS_FINISH_WYNA(
    [--with-cygwin],
    [WYNA_CYGWIN])[

  ]GATBPS_CHECK_EXPR(
    [whether to use Cygwin],
    [WITH_CYGWIN],
    [1
      && !WYNA_CYGWIN_IS_NO
      && HAVE_CYGWIN
    ])[

  case $][{WYNA_CYGWIN_IS_YES?}$][{WITH_CYGWIN?} in 10)
    ]GATBPS_BARF([
      Cygwin is not available.
    ])[
  esac

}]])
