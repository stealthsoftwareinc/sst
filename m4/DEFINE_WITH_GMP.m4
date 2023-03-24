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

AC_DEFUN_ONCE([DEFINE_WITH_GMP], [[
]GATBPS_CALL_COMMENT([$0]m4_if(m4_eval([$# > 0]), [1], [, $@]))[
{ :

  ]GATBPS_BEFORE([$0], [DEFINE_LIBS])[

  ]GATBPS_REQUIRE([DEFINE_DEDUCE_WYNAS])[
  ]GATBPS_SOFT_REQUIRE([DEFINE_CFLAGS])[
  ]GATBPS_SOFT_REQUIRE([DEFINE_CPPFLAGS])[
  ]GATBPS_SOFT_REQUIRE([DEFINE_CXXFLAGS])[
  ]GATBPS_SOFT_REQUIRE([DEFINE_WITH_BUILD_GROUPS])[

  ]GATBPS_FINISH_WYNA(
    [--with-gmp],
    [WYNA_GMP])[

  ]GATBPS_PUSH_VAR([LIBS], ["-lgmp $][{LIBS-}"])[

  ]m4_pushdef(
    [prologue],
    [[
      #include <gmp.h>
    ]])[

  ]m4_pushdef(
    [body],
    [[
      mpz_t x;
      mpz_init(x);
      mpz_clear(x);
    ]])[

  ]AC_LANG_PUSH([C])[

  ]GATBPS_CHECK_LINK(
    [for the GMP library (C link)],
    [WITH_GMP_C_LINK],
    prologue,
    body,
    [1
      && !WYNA_GMP_IS_NO
      && ]GATBPS_SOFT_VAR([WITH_BUILD_GROUP_C_AUTOTOOLS])[
    ])[

  ]GATBPS_CHECK_RUN(
    [for the GMP library (C run)],
    [WITH_GMP_C_RUN],
    prologue,
    body,
    [yes],
    [WITH_GMP_C_LINK])[

  ]AC_LANG_POP([C])[

  ]AC_LANG_PUSH([C++])[

  ]GATBPS_CHECK_LINK(
    [for the GMP library (C++ link)],
    [WITH_GMP_CPP_LINK],
    prologue,
    body,
    [1
      && !WYNA_GMP_IS_NO
      && ]GATBPS_SOFT_VAR([WITH_BUILD_GROUP_CPP_AUTOTOOLS])[
    ])[

  ]GATBPS_CHECK_RUN(
    [for the GMP library (C++ run)],
    [WITH_GMP_CPP_RUN],
    prologue,
    body,
    [yes],
    [WITH_GMP_CPP_LINK])[

  ]AC_LANG_POP([C++])[

  ]m4_popdef([body])[
  ]m4_popdef([prologue])[

  ]GATBPS_CHECK_EXPR(
    [whether to use the GMP library],
    [WITH_GMP],
    [(1
      ) && (0
        || ]GATBPS_SOFT_VAR([WITH_BUILD_GROUP_C_AUTOTOOLS])[
        || ]GATBPS_SOFT_VAR([WITH_BUILD_GROUP_CPP_AUTOTOOLS])[
      ) && (0
        || !]GATBPS_SOFT_VAR([WITH_BUILD_GROUP_C_AUTOTOOLS])[
        || WITH_GMP_C_RUN
        || (1
          && WYNA_GMP_IS_YES
          && WITH_GMP_C_RUN_is_guess
        )
      ) && (0
        || !]GATBPS_SOFT_VAR([WITH_BUILD_GROUP_CPP_AUTOTOOLS])[
        || WITH_GMP_CPP_RUN
        || (1
          && WYNA_GMP_IS_YES
          && WITH_GMP_CPP_RUN_is_guess
        )
      )
    ])[

  case $][{WYNA_GMP_IS_YES?}$][{WITH_GMP?} in 10)
    ]GATBPS_BARF([
      The GMP library is not available.
    ])[
  esac

  if $][{WITH_GMP_sh?}; then
    ]GATBPS_KEEP_VAR([LIBS])[
  else
    ]GATBPS_POP_VAR([LIBS])[
  fi

}]])
