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

AC_DEFUN_ONCE([DEFINE_WITH_NETTLE], [
GATBPS_CALL_COMMENT([$0]m4_if(m4_eval([$# > 0]), [1], [, $@]))
{ :

  GATBPS_BEFORE([$0], [DEFINE_LIBS])

  GATBPS_REQUIRE([DEFINE_CFLAGS], [soft])
  GATBPS_REQUIRE([DEFINE_CPPFLAGS], [soft])
  GATBPS_REQUIRE([DEFINE_CXXFLAGS], [soft])
  GATBPS_REQUIRE([DEFINE_DEDUCE_WYNAS])
  GATBPS_REQUIRE([DEFINE_WITH_BUILD_GROUPS], [soft])

  GATBPS_FINISH_WYNA(
    [--with-nettle],
    [WYNA_NETTLE])

  GATBPS_PUSH_VAR([LIBS], ["-lnettle $][{LIBS-}"])

  m4_pushdef(
    [prologue],
    [[
      #include <nettle/sha1.h>
    ]])

  m4_pushdef(
    [body],
    [[
      struct sha1_ctx ctx;
      sha1_init(&ctx);
    ]])

  AC_LANG_PUSH([C])

  GATBPS_CHECK_LINK(
    [for the Nettle nettle library (C link)],
    [WITH_NETTLE_C_LINK],
    prologue,
    body,
    [1
      && !WYNA_NETTLE_IS_NO
      && ]GATBPS_SOFT_VAR([WITH_BUILD_GROUP_C_AUTOTOOLS])[
    ])

  GATBPS_CHECK_RUN(
    [for the Nettle nettle library (C run)],
    [WITH_NETTLE_C_RUN],
    prologue,
    body,
    [yes],
    [WITH_NETTLE_C_LINK])

  AC_LANG_POP([C])

  AC_LANG_PUSH([C++])

  GATBPS_CHECK_LINK(
    [for the Nettle nettle library (C++ link)],
    [WITH_NETTLE_CPP_LINK],
    prologue,
    body,
    [1
      && !WYNA_NETTLE_IS_NO
      && ]GATBPS_SOFT_VAR([WITH_BUILD_GROUP_CPP_AUTOTOOLS])[
    ])

  GATBPS_CHECK_RUN(
    [for the Nettle nettle library (C++ run)],
    [WITH_NETTLE_CPP_RUN],
    prologue,
    body,
    [yes],
    [WITH_NETTLE_CPP_LINK])

  AC_LANG_POP([C++])

  m4_popdef([body])
  m4_popdef([prologue])

  GATBPS_CHECK_EXPR(
    [for the Nettle nettle library (all)],
    [WITH_NETTLE],
    [(1
      ) && (0
        || ]GATBPS_SOFT_VAR([WITH_BUILD_GROUP_C_AUTOTOOLS])[
        || ]GATBPS_SOFT_VAR([WITH_BUILD_GROUP_CPP_AUTOTOOLS])[
      ) && (0
        || !]GATBPS_SOFT_VAR([WITH_BUILD_GROUP_C_AUTOTOOLS])[
        || WITH_NETTLE_C_RUN
        || (1
          && WYNA_NETTLE_IS_YES
          && WITH_NETTLE_C_RUN_is_guess
        )
      ) && (0
        || !]GATBPS_SOFT_VAR([WITH_BUILD_GROUP_CPP_AUTOTOOLS])[
        || WITH_NETTLE_CPP_RUN
        || (1
          && WYNA_NETTLE_IS_YES
          && WITH_NETTLE_CPP_RUN_is_guess
        )
      )
    ])

  [

    case $][{WYNA_NETTLE_IS_YES?}$][{WITH_NETTLE?} in 10)
      ]GATBPS_BARF([
        The Nettle nettle library is not available.
      ])[
    esac

    if $][{WITH_NETTLE_sh?}; then
      ]GATBPS_KEEP_VAR([LIBS])[
    else
      ]GATBPS_POP_VAR([LIBS])[
    fi

  ]

}])
