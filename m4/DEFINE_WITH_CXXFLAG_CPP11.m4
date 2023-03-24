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

AC_DEFUN_ONCE([DEFINE_WITH_CXXFLAG_CPP11], [[
]GATBPS_CALL_COMMENT([$0]m4_if(m4_eval([$# > 0]), [1], [, $@]))[
{ :

  ]GATBPS_BEFORE([$0], [DEFINE_CXXFLAGS])[
  ]GATBPS_SOFT_REQUIRE([DEFINE_CPPFLAGS])[
  ]GATBPS_SOFT_REQUIRE([DEFINE_WITH_BUILD_GROUPS])[

  ]AC_LANG_PUSH([C++])[

  ]GATBPS_CHECK_COMPILE(
    [whether C++11 is enabled (1)],
    [WITH_CXXFLAG_CPP11_1],
    [],
    [
      #if __cplusplus < 201103L
        #include <cause_a_compilation_error>
      #endif
    ],
    [1
      && ]GATBPS_SOFT_VAR([WITH_BUILD_GROUP_CPP_AUTOTOOLS])[
    ])[

  ]AC_LANG_POP([C++])[

  if $][{WITH_CXXFLAG_CPP11_1_sh?}; then

    ]GATBPS_CHECK_EXPR(
      [whether C++11 is enabled (2)],
      [WITH_CXXFLAG_CPP11_2],
      [1])[

  else

    ]GATBPS_PUSH_VAR([CXXFLAGS], ["-std=c++11 $][{CXXFLAGS-}"])[

    ]AC_LANG_PUSH([C++])[

    ]GATBPS_CHECK_COMPILE(
      [whether C++11 is enabled (2)],
      [WITH_CXXFLAG_CPP11_2],
      [],
      [
        #if __cplusplus < 201103L
          #include <cause_a_compilation_error>
        #endif
      ],
      [1
        && ]GATBPS_SOFT_VAR([WITH_BUILD_GROUP_CPP_AUTOTOOLS])[
      ])[

    ]AC_LANG_POP([C++])[

    if $][{WITH_CXXFLAG_CPP11_2_sh?}; then
      :
    else
      ]GATBPS_BARF([
        C++11 is not available.
      ])[
    fi

    ]GATBPS_KEEP_VAR([CXXFLAGS])[

  fi

  ]GATBPS_CHECK_EXPR(
    [whether C++11 is enabled (3)],
    [WITH_CXXFLAG_CPP11],
    [WITH_CXXFLAG_CPP11_2])[

}]])
