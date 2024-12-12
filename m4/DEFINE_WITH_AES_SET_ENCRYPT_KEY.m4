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

AC_DEFUN_ONCE([DEFINE_WITH_AES_SET_ENCRYPT_KEY], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_WITH_AES_SET_ENCRYPT_KEY macro.
#]dnl
m4_ifdef(
  [DEFINE_WITH_AES_SET_ENCRYPT_KEY_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_WITH_AES_SET_ENCRYPT_KEY has already been called
  ])],
  [m4_define([DEFINE_WITH_AES_SET_ENCRYPT_KEY_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_WITH_AES_SET_ENCRYPT_KEY requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl

AC_REQUIRE([DEFINE_WITH_AES_CTX])
AC_REQUIRE([DEFINE_WITH_NETTLE_AES_H])
AC_REQUIRE([DEFINE_WITH_NETTLE_NETTLE_TYPES_H])
AC_REQUIRE([DEFINE_WITH_UINT8_T_IN_NETTLE_NETTLE_TYPES_H])
AC_REQUIRE([DEFINE_WITH_NETTLE])

GATBPS_REQUIRE([DEFINE_CFLAGS], [soft])
GATBPS_REQUIRE([DEFINE_CPPFLAGS], [soft])
AC_REQUIRE([DEFINE_WITH_NETTLE_CRYPT_FUNC_SIZE_T])
GATBPS_REQUIRE([DEFINE_LIBS], [soft])

AC_LANG_PUSH([C])
GATBPS_CHECK_LINK(
  [aes_set_encrypt_key],
  [WITH_AES_SET_ENCRYPT_KEY],
  [
    #include <nettle/aes.h>
    #include <nettle/nettle-types.h>
    #include <stddef.h>
  ],
  [
    #if (WITH_NETTLE_CRYPT_FUNC_SIZE_T)
    {
      aes_set_encrypt_key(
        (struct aes_ctx *)0,
        (size_t)1,
        (uint8_t const *)0
      );
    }
    #else
    {
      aes_set_encrypt_key(
        (struct aes_ctx *)0,
        (unsigned int)1,
        (uint8_t const *)0
      );
    }
    #endif
  ],
  [1
    && WITH_AES_CTX
    && WITH_NETTLE_AES_H
    && WITH_NETTLE_NETTLE_TYPES_H
    && WITH_UINT8_T_IN_NETTLE_NETTLE_TYPES_H
    && WITH_NETTLE
  ])
AC_LANG_POP([C])

:;}])[]dnl
