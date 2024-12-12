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

AC_DEFUN_ONCE([DEFINE_SST_WITH_SST_BN_BIN2BN_STEP], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_SST_WITH_SST_BN_BIN2BN_STEP macro.
#]dnl
m4_ifdef(
  [DEFINE_SST_WITH_SST_BN_BIN2BN_STEP_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_SST_WITH_SST_BN_BIN2BN_STEP has already been called
  ])],
  [m4_define([DEFINE_SST_WITH_SST_BN_BIN2BN_STEP_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_SST_WITH_SST_BN_BIN2BN_STEP requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl

AC_REQUIRE([DEFINE_WITH_BIGNUM])
AC_REQUIRE([DEFINE_WITH_BN_ADD])
AC_REQUIRE([DEFINE_WITH_BN_BIN2BN])
AC_REQUIRE([DEFINE_WITH_BN_CTX])
AC_REQUIRE([DEFINE_WITH_BN_CTX_END])
AC_REQUIRE([DEFINE_WITH_BN_CTX_GET])
AC_REQUIRE([DEFINE_WITH_BN_CTX_START])
AC_REQUIRE([DEFINE_WITH_BN_FREE])
AC_REQUIRE([DEFINE_WITH_BN_LSHIFT])
AC_REQUIRE([DEFINE_WITH_OPENSSL_BN_H])
AC_REQUIRE([DEFINE_WITH_OPENSSL_CRYPTO])

GATBPS_CHECK_EXPR(
  [sst_BN_bin2bn_step],
  [SST_WITH_SST_BN_BIN2BN_STEP],
  [1
    && WITH_BIGNUM
    && WITH_BN_ADD
    && WITH_BN_BIN2BN
    && WITH_BN_CTX
    && WITH_BN_CTX_END
    && WITH_BN_CTX_GET
    && WITH_BN_CTX_START
    && WITH_BN_FREE
    && WITH_BN_LSHIFT
    && WITH_OPENSSL_BN_H
    && WITH_OPENSSL_CRYPTO
  ])

:;}])[]dnl
