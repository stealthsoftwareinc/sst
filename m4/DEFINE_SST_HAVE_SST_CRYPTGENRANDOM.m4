dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_SST_HAVE_SST_CRYPTGENRANDOM], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_SST_HAVE_SST_CRYPTGENRANDOM macro.
#]dnl
m4_ifdef(
  [DEFINE_SST_HAVE_SST_CRYPTGENRANDOM_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_SST_HAVE_SST_CRYPTGENRANDOM has already been called
  ])],
  [m4_define([DEFINE_SST_HAVE_SST_CRYPTGENRANDOM_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_SST_HAVE_SST_CRYPTGENRANDOM requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl

AC_REQUIRE([DEFINE_HAVE_BOOL])
AC_REQUIRE([DEFINE_HAVE_BYTE])
AC_REQUIRE([DEFINE_HAVE_HCRYPTPROV])
AC_REQUIRE([DEFINE_HAVE_WINCRYPT_H])
AC_REQUIRE([DEFINE_HAVE_WINDOWS])
AC_REQUIRE([DEFINE_SST_HAVE_SST_CRYPTGENRANDOM_STEP])

GATBPS_CHECK_VARS(
  [sst_CryptGenRandom],
  [SST_HAVE_SST_CRYPTGENRANDOM],
  [
    HAVE_BOOL
    HAVE_BYTE
    HAVE_HCRYPTPROV
    HAVE_WINCRYPT_H
    HAVE_WINDOWS
    SST_HAVE_SST_CRYPTGENRANDOM_STEP
  ])

:;}])[]dnl
