dnl
dnl Copyright (C) 2012-2023 Stealth Software Technologies, Inc.
dnl
dnl Permission is hereby granted, free of charge, to any person
dnl obtaining a copy of this software and associated documentation
dnl files (the "Software"), to deal in the Software without
dnl restriction, including without limitation the rights to use,
dnl copy, modify, merge, publish, distribute, sublicense, and/or
dnl sell copies of the Software, and to permit persons to whom the
dnl Software is furnished to do so, subject to the following
dnl conditions:
dnl
dnl The above copyright notice and this permission notice (including
dnl the next paragraph) shall be included in all copies or
dnl substantial portions of the Software.
dnl
dnl THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
dnl EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
dnl OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
dnl NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
dnl HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
dnl WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
dnl FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
dnl OTHER DEALINGS IN THE SOFTWARE.
dnl
dnl SPDX-License-Identifier: MIT
dnl

AC_DEFUN_ONCE([DEFINE_WITH_NETTY], [[
]GATBPS_CALL_COMMENT([$0]m4_if(m4_eval([$# > 0]), [1], [, $@]))[
{ :

  ]GATBPS_BEFORE([$0], [DEFINE_JARS])[

  ]GATBPS_REQUIRE([DEFINE_DEDUCE_WYNAS])[

  ]GATBPS_FINISH_WYNA(
    [--with-netty],
    [WYNA_NETTY])[

  ]GATBPS_CHECK_JAR(
    [whether to use the Netty library],
    [netty-all-4.1.65.Final.jar],
    [PATH_NETTY],
    [WITH_NETTY],
    [1
      && !WYNA_NETTY_IS_NO
    ])[

  case $][{WYNA_NETTY_IS_YES?}$][{WITH_NETTY?} in 10)
    ]GATBPS_BARF([
      The Netty library is not available.
    ])[
  esac

}]])
