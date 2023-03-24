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

dnl---------------------------------------------------------------------

AC_INIT(
  [[SST]],
  m4_esyscmd_s([
    sh build-aux/gatbps-gen-version.sh
  ])m4_if(m4_sysval, 0, [], [
    m4_fatal([gatbps-gen-version.sh failed.])
  ]),
  [[sst@stealthsoftwareinc.com]],
  [[sst]])

dnl---------------------------------------------------------------------

AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_MACRO_DIRS([m4])
AC_CONFIG_SRCDIR([build-aux/sst.srcdir])

AM_INIT_AUTOMAKE([
  -Wall
  foreign
  nostdinc
  subdir-objects
  tar-ustar
])

dnl---------------------------------------------------------------------

m4_include([build-aux/gatbps.ac])

dnl---------------------------------------------------------------------
dnl srcdir_q
dnl---------------------------------------------------------------------

srcdir_q=`gatbps_quote "${srcdir?}"` || exit $?

dnl---------------------------------------------------------------------

[

x=build-aux/configure.started
y=build-aux/configure.success

if test -f $x; then
  if test -f $y; then
    :
  else
    :
    ]AC_MSG_ERROR([[Refusing to run because $x exists without $y.]])[
  fi
fi

rm -f $y || exit $?
mkdir -p build-aux || exit $?
>$x || exit $?

]

dnl---------------------------------------------------------------------
dnl Program checks
dnl---------------------------------------------------------------------

GATBPS_PROG_ASCIIDOCTOR
GATBPS_PROG_AWK
GATBPS_PROG_CURL
GATBPS_PROG_DOCKER
GATBPS_PROG_GIT
GATBPS_PROG_GREP
GATBPS_PROG_GUNZIP
GATBPS_PROG_JAVA
GATBPS_PROG_JAVAC
GATBPS_PROG_JDEPS
GATBPS_PROG_LN_S
GATBPS_PROG_MKDIR_P
GATBPS_PROG_OPENSSL
GATBPS_PROG_SED
GATBPS_PROG_TAR
GATBPS_PROG_WGET
GATBPS_PROG_XZ
GATBPS_PROG_ZIP

dnl---------------------------------------------------------------------

[

]gatbps_check_macros[ || exit

]GATBPS_DEFINE_VERSION(
  [AC_],
  [PACKAGE_VERSION])[

]GATBPS_DEFINE_DATE(
  [AC_],
  [PACKAGE_DATE],
  m4_esyscmd_s([
    sh build-aux/gatbps-gen-date.sh
  ])m4_if(m4_sysval, 0, [], [
    m4_fatal([gatbps-gen-date.sh failed])
  ]))[

]AC_COPYRIGHT(
[[Some parts of this file are from the SST package.

The following copyright notice is generally applicable:

     Copyright (C) Stealth Software Technologies, Inc.

The full copyright information depends on the distribution
of the package. For more information, see the COPYING file.
However, depending on the context in which you are viewing
this file, the COPYING file may not be available.
]])

dnl---------------------------------------------------------------------
dnl CPPFLAGS
dnl---------------------------------------------------------------------

x=
x=${x?}" -I src/c-cpp/lib"
x=${x?}" -I ${srcdir_q?}/src/c-cpp/lib"
x=${x?}" -I src/c-cpp/include"
x=${x?}" -I ${srcdir_q?}/src/c-cpp/include"
x=${x?}" -I include"
x=${x?}" -I ${srcdir_q?}/include"

CPPFLAGS="${x?} ${CPPFLAGS-}"

unset x

dnl---------------------------------------------------------------------

m4_include([build-aux/autogen.ac])[

]

LT_INIT([
  disable-static
  shared
  win32-dll
])

dnl---------------------------------------------------------------------
dnl SUBSET_LIBRARY
dnl---------------------------------------------------------------------

[
  case $][{SUBSET_LIBRARY-0} in 1)
    SUBSET_LIBRARY='*/1/*'
  ;; 0)
    SUBSET_LIBRARY='*/0/*'
  ;; *)
    ]GATBPS_BARF([
      Invalid SUBSET_LIBRARY value.
    ])[
  esac
  readonly SUBSET_LIBRARY
]

AC_SUBST([SUBSET_LIBRARY])

dnl---------------------------------------------------------------------

[

]
AC_CHECK_HEADERS_ONCE([pthread.h])
AC_CHECK_HEADERS_ONCE([windows.h])
[

]dnl begin_includes
[

]m4_include([bin/sst_status_map_generator.ac])[
]m4_include([include/src/sst_status_map.inc.ac])[

]dnl end_includes
[
]

AC_ARG_ENABLE(
  [mutex],
  [
AS_HELP_STRING([--disable-mutex],
               [equivalent to --enable-mutex=no])
AS_HELP_STRING([--enable-mutex],
               [equivalent to --enable-mutex=yes (default)])
AS_HELP_STRING([--enable-mutex=no],
               [use the null mutex implementation])
AS_HELP_STRING([--enable-mutex=yes],
               [use the inferred mutex implementation])
AS_HELP_STRING([--enable-mutex=posix],
               [use the POSIX mutex implementation])
AS_HELP_STRING([--enable-mutex=windows],
               [use the Windows mutex implementation])],
  [],
  [
    enable_mutex='yes'
  ]
)

case "${enable_mutex}" in
  'no')
    :
  ;;
  'posix')
    case "${ac_cv_header_pthread_h}" in
      'no')
        AC_MSG_ERROR([--enable-mutex=posix requires pthread.h], [1])
      ;;
    esac
  ;;
  'windows')
    case "${ac_cv_header_windows_h}" in
      'no')
        AC_MSG_ERROR([--enable-mutex=windows requires windows.h], [1])
      ;;
    esac
  ;;
  'yes')
    case "${ac_cv_header_pthread_h},${ac_cv_header_windows_h}" in
      'yes,'*)
        enable_mutex='posix'
      ;;
      'no,yes')
        enable_mutex='windows'
      ;;
      *)
        enable_mutex='no'
      ;;
    esac
  ;;
  *)
    AC_MSG_ERROR([invalid --enable-mutex value], [1])
  ;;
esac

case "${enable_mutex}" in
  'no')
    SST_MUTEX_IMP='SST_MUTEX_IMP_NULL'
  ;;
  'posix')
    SST_MUTEX_IMP='SST_MUTEX_IMP_POSIX'
  ;;
  'windows')
    SST_MUTEX_IMP='SST_MUTEX_IMP_WINDOWS'
  ;;
  *)
    AC_MSG_ERROR([the --enable-mutex code is broken], [1])
  ;;
esac

AC_SUBST([SST_MUTEX_IMP])

GATBPS_CONFIG_FILE([build-aux/PACKAGE_STRING.df])
GATBPS_CONFIG_FILE([pom.xml])
GATBPS_CONFIG_FILE([sst-java/pom.xml])
GATBPS_CONFIG_FILE([sst-maven-parent/pom.xml])

GATBPS_CP([artifacts/$(distdir).tar.gz], [$(artifacts_dist_archive_src)])

[

]GATBPS_CONFIG_FILE_SUBST[
]GATBPS_CONFIG_LATER_SUBST[
]GATBPS_CP_SUBST[
]GATBPS_GIT_ARCHIVE_SUBST[
]GATBPS_GIT_BUNDLE_SUBST[
]GATBPS_GIT_CLONE_SUBST[
]GATBPS_WGET_SUBST[

]AC_CONFIG_FILES([Makefile])[
]AC_CONFIG_HEADERS([src/c-cpp/lib/sst/config_private_raw.h])[

]AC_CONFIG_SUBDIRS([
  gen
])

[

#
# Restore the normal Libtool behavior on systems that prefer to set
# link_all_deplibs=no, as this generally causes problems with our
# workflow. See <https://stackoverflow.com/q/11802727>.
#

link_all_deplibs=yes
link_all_deplibs_CXX=yes

]

dnl---------------------------------------------------------------------

AC_OUTPUT

dnl---------------------------------------------------------------------
[

>build-aux/configure.success || exit $?

]
