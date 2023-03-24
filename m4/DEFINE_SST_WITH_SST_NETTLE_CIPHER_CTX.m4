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

AC_DEFUN_ONCE([DEFINE_SST_WITH_SST_NETTLE_CIPHER_CTX], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_SST_WITH_SST_NETTLE_CIPHER_CTX macro.
#]dnl
m4_ifdef(
  [DEFINE_SST_WITH_SST_NETTLE_CIPHER_CTX_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_SST_WITH_SST_NETTLE_CIPHER_CTX has already been called
  ])],
  [m4_define([DEFINE_SST_WITH_SST_NETTLE_CIPHER_CTX_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_SST_WITH_SST_NETTLE_CIPHER_CTX requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl

AC_REQUIRE([DEFINE_WITH_NETTLE_CIPHER_OR_CRYPT_FUNC])
AC_REQUIRE([DEFINE_WITH_NETTLE_NETTLE_TYPES_H])
AC_REQUIRE([DEFINE_WITH_NETTLE])

GATBPS_CHECK_EXPR(
  [sst_nettle_cipher_ctx],
  [SST_WITH_SST_NETTLE_CIPHER_CTX],
  [1
    && WITH_NETTLE_CIPHER_OR_CRYPT_FUNC
    && WITH_NETTLE_NETTLE_TYPES_H
    && WITH_NETTLE
  ])

:;}])[]dnl
