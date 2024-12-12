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

AC_DEFUN_ONCE([DEFINE_WITH_LIB_HOGWEED], [[{

]GATBPS_BEFORE([$0], [DEFINE_LIBS])[

]dnl begin_prerequisites
[

]GATBPS_REQUIRE([DEFINE_CFLAGS], [soft])[
]GATBPS_REQUIRE([DEFINE_CPPFLAGS], [soft])[
]AC_REQUIRE([DEFINE_WITH_GMP])[
]AC_REQUIRE([DEFINE_WITH_NETTLE])[

]dnl end_prerequisites
[

old_LIBS=$LIBS

LIBS="-lhogweed $LIBS"

]AC_LANG_PUSH([C])[
]GATBPS_CHECK_LINK(
  [-lhogweed],
  [WITH_LIB_HOGWEED],
  [
    #include <nettle/rsa.h>
  ],
  [
    struct rsa_public_key pub;
    rsa_public_key_init(&pub);
  ],
  [1
    && WITH_GMP
    && WITH_NETTLE
  ])[
]AC_LANG_POP([C])[

case $WITH_LIB_HOGWEED in
  0)
    LIBS=$old_LIBS
  ;;
esac

:;}]])
