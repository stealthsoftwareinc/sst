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

AC_DEFUN_ONCE([DEFINE_WITH_WINDOWS_WS2_32], [
GATBPS_CALL_COMMENT([$0]m4_if(m4_eval([$# > 0]), [1], [, $@]))
{ :

  GATBPS_BEFORE([$0], [DEFINE_LIBS])

  GATBPS_REQUIRE([DEFINE_CFLAGS], [soft])
  GATBPS_REQUIRE([DEFINE_CPPFLAGS], [soft])
  GATBPS_REQUIRE([DEFINE_CXXFLAGS], [soft])
  GATBPS_REQUIRE([DEFINE_DEDUCE_WYNAS])
  GATBPS_REQUIRE([DEFINE_WITH_CYGWIN], [soft])
  GATBPS_REQUIRE([DEFINE_WITH_WINDOWS], [soft])
  GATBPS_REQUIRE([DEFINE_WITH_WINDOWS_KERNEL32], [soft])
  GATBPS_REQUIRE([DEFINE_WITH_BUILD_GROUPS], [soft])

  GATBPS_FINISH_WYNA(
    [--with-windows-ws2-32],
    [WYNA_WINDOWS_WS2_32])

  GATBPS_PUSH_VAR([LIBS], ["-lws2_32 $][{LIBS-}"])

  m4_pushdef(
    [prologue],
    [[
      #include <winsock2.h>
      #include <windows.h>
    ]])

  m4_pushdef(
    [body],
    [[
      (void)WSAGetLastError();
    ]])

  AC_LANG_PUSH([C])

  GATBPS_CHECK_LINK(
    [for the Windows ws2_32 API (C link)],
    [WITH_WINDOWS_WS2_32_C_LINK],
    prologue,
    body,
    [1
      && ]GATBPS_SOFT_VAR([WITH_BUILD_GROUP_C_AUTOTOOLS])[
      && ]GATBPS_SOFT_VAR([WITH_WINDOWS])[
      && ]GATBPS_SOFT_VAR([WITH_WINDOWS_KERNEL32])[
      && !]GATBPS_SOFT_VAR([HAVE_CYGWIN])[
      && !WYNA_WINDOWS_WS2_32_IS_NO
    ])

  GATBPS_CHECK_RUN(
    [for the Windows ws2_32 API (C run)],
    [WITH_WINDOWS_WS2_32_C_RUN],
    prologue,
    body,
    [yes],
    [WITH_WINDOWS_WS2_32_C_LINK])

  AC_LANG_POP([C])

  AC_LANG_PUSH([C++])

  GATBPS_CHECK_LINK(
    [for the Windows ws2_32 API (C++ link)],
    [WITH_WINDOWS_WS2_32_CPP_LINK],
    prologue,
    body,
    [1
      && ]GATBPS_SOFT_VAR([WITH_BUILD_GROUP_CPP_AUTOTOOLS])[
      && ]GATBPS_SOFT_VAR([WITH_WINDOWS])[
      && ]GATBPS_SOFT_VAR([WITH_WINDOWS_KERNEL32])[
      && !]GATBPS_SOFT_VAR([HAVE_CYGWIN])[
      && !WYNA_WINDOWS_WS2_32_IS_NO
    ])

  GATBPS_CHECK_RUN(
    [for the Windows ws2_32 API (C++ run)],
    [WITH_WINDOWS_WS2_32_CPP_RUN],
    prologue,
    body,
    [yes],
    [WITH_WINDOWS_WS2_32_CPP_LINK])

  AC_LANG_POP([C++])

  m4_popdef([body])
  m4_popdef([prologue])

  GATBPS_CHECK_EXPR(
    [whether to use the Windows ws2_32 API],
    [WITH_WINDOWS_WS2_32],
    [(1
      ) && (0
        || ]GATBPS_SOFT_VAR([WITH_BUILD_GROUP_C_AUTOTOOLS])[
        || ]GATBPS_SOFT_VAR([WITH_BUILD_GROUP_CPP_AUTOTOOLS])[
      ) && (0
        || !]GATBPS_SOFT_VAR([WITH_BUILD_GROUP_C_AUTOTOOLS])[
        || WITH_WINDOWS_WS2_32_C_RUN
        || (1
          && WYNA_WINDOWS_WS2_32_IS_YES
          && WITH_WINDOWS_WS2_32_C_RUN_is_guess
        )
      ) && (0
        || !]GATBPS_SOFT_VAR([WITH_BUILD_GROUP_CPP_AUTOTOOLS])[
        || WITH_WINDOWS_WS2_32_CPP_RUN
        || (1
          && WYNA_WINDOWS_WS2_32_IS_YES
          && WITH_WINDOWS_WS2_32_CPP_RUN_is_guess
        )
      )
    ])

  [

    case $][{WYNA_WINDOWS_WS2_32_IS_YES?}$][{WITH_WINDOWS_WS2_32?} in 10)
      ]GATBPS_BARF([
        The Windows ws2_32 API is not available.
      ])[
    esac

    if $][{WITH_WINDOWS_WS2_32_sh?}; then
      ]GATBPS_KEEP_VAR([LIBS])[
    else
      ]GATBPS_POP_VAR([LIBS])[
    fi

  ]

}])
