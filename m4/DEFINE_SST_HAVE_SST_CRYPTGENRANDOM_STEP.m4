dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_SST_HAVE_SST_CRYPTGENRANDOM_STEP], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_SST_HAVE_SST_CRYPTGENRANDOM_STEP macro.
#]dnl
m4_ifdef(
  [DEFINE_SST_HAVE_SST_CRYPTGENRANDOM_STEP_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_SST_HAVE_SST_CRYPTGENRANDOM_STEP has already been called
  ])],
  [m4_define([DEFINE_SST_HAVE_SST_CRYPTGENRANDOM_STEP_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_SST_HAVE_SST_CRYPTGENRANDOM_STEP requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl

AC_REQUIRE([DEFINE_HAVE_BOOL])
AC_REQUIRE([DEFINE_HAVE_BYTE])
AC_REQUIRE([DEFINE_HAVE_CRYPTGENRANDOM])
AC_REQUIRE([DEFINE_HAVE_DWORD])
AC_REQUIRE([DEFINE_HAVE_HCRYPTPROV])
AC_REQUIRE([DEFINE_HAVE_WINCRYPT_H])
AC_REQUIRE([DEFINE_HAVE_WINDOWS])

GATBPS_CHECK_VARS(
  [sst_CryptGenRandom_step],
  [SST_HAVE_SST_CRYPTGENRANDOM_STEP],
  [
    HAVE_BOOL
    HAVE_BYTE
    HAVE_CRYPTGENRANDOM
    HAVE_DWORD
    HAVE_HCRYPTPROV
    HAVE_WINCRYPT_H
    HAVE_WINDOWS
  ])

:;}])[]dnl
