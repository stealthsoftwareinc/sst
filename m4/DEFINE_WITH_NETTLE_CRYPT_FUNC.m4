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

AC_DEFUN_ONCE([DEFINE_WITH_NETTLE_CRYPT_FUNC], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_WITH_NETTLE_CRYPT_FUNC macro.
#]dnl
m4_ifdef(
  [DEFINE_WITH_NETTLE_CRYPT_FUNC_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_WITH_NETTLE_CRYPT_FUNC has already been called
  ])],
  [m4_define([DEFINE_WITH_NETTLE_CRYPT_FUNC_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_WITH_NETTLE_CRYPT_FUNC requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl

AC_REQUIRE([DEFINE_WITH_NETTLE])

AC_REQUIRE([DEFINE_WITH_NETTLE_CRYPT_FUNC_SIZE_T])
AC_REQUIRE([DEFINE_WITH_NETTLE_CRYPT_FUNC_UNSIGNED_INT])

h1=""
h1="$[]{h1}$[]{WITH_NETTLE_CRYPT_FUNC_SIZE_T}"
h1="$[]{h1}$[]{WITH_NETTLE_CRYPT_FUNC_UNSIGNED_INT}"

case "$[]{h1}" in
  *'1'*)
    h1='1'
  ;;
  *)
    h1='0'
  ;;
esac

GATBPS_CHECK_EXPR(
  [nettle_crypt_func],
  [WITH_NETTLE_CRYPT_FUNC],
  [1
    && WITH_NETTLE
    && h1
  ])

:;}])[]dnl
