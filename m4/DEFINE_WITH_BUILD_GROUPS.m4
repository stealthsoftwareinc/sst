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

AC_DEFUN_ONCE([DEFINE_WITH_BUILD_GROUPS], [[{

]GATBPS_ARG_WITH(
  [build-groups],
  [],
  [yes])[

. "$srcdir"/src/sh/fragments/with_build_groups.sh
case $with_build_groups_error in
  sed_failed)
    exit $with_build_groups_error_sed_status
  ;;
  invalid_entry)
    ]GATBPS_BARF([
      unknown --with-build-groups entry:
      $with_build_groups_error_invalid_entry
    ])[
  ;;
  ?*)
    exit 1
  ;;
esac

x=$WITH_BUILD_GROUP_BASH
]GATBPS_CHECK_EXPR(
  [--with-build-groups += bash],
  [WITH_BUILD_GROUP_BASH],
  [x])[

x=$WITH_BUILD_GROUP_C_AUTOTOOLS
]GATBPS_CHECK_EXPR(
  [--with-build-groups += c-autotools],
  [WITH_BUILD_GROUP_C_AUTOTOOLS],
  [x])[

x=$WITH_BUILD_GROUP_CPP_AUTOTOOLS
]GATBPS_CHECK_EXPR(
  [--with-build-groups += cpp-autotools],
  [WITH_BUILD_GROUP_CPP_AUTOTOOLS],
  [x])[

x=$WITH_BUILD_GROUP_JAVA_GATBPS
]GATBPS_CHECK_EXPR(
  [--with-build-groups += java-gatbps],
  [WITH_BUILD_GROUP_JAVA_GATBPS],
  [x])[

x=$WITH_BUILD_GROUP_JAVA_MAVEN
]GATBPS_CHECK_EXPR(
  [--with-build-groups += java-maven],
  [WITH_BUILD_GROUP_JAVA_MAVEN],
  [x])[

:;}]])
