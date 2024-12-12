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

AC_INIT(
  [[SST Code Generation]],
  m4_esyscmd_s([
    'cd' '..' && 'sh' '-' 'build-aux/gatbps-gen-version.sh'
  ])m4_if(m4_sysval, [0], [], [m4_fatal([gatbps-gen-version.sh failed])]),
  [[]],
  [[sst-gen]],
  [[]])

[. "$srcdir"/../build-aux/gen-configure.sh]

AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([../m4])
AC_CONFIG_MACRO_DIRS([../m4])
AC_CONFIG_SRCDIR([../build-aux/sst.srcdir])

m4_include([../build-aux/gatbps.ac])

AC_COPYRIGHT(
[[Some parts of this file are from the SST package.

The following copyright notice is generally applicable:

     Copyright (C) Stealth Software Technologies, Inc.

The full copyright information depends on the distribution
of the package. For more information, see the COPYING file.
However, depending on the context in which you are viewing
this file, the COPYING file may not be available.
]])

AM_INIT_AUTOMAKE([
  -Wall
  foreign
  nostdinc
  subdir-objects
  tar-ustar
])

AC_PROG_CC
AC_PROG_RANLIB
AM_PROG_AR

m4_include([bin/sst_status_map_generator.ac])
m4_include([include/src/sst_status_map.inc.ac])

AC_CONFIG_FILES([Makefile])

AC_OUTPUT
