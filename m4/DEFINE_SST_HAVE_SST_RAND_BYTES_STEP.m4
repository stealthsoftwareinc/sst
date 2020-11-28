dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_SST_HAVE_SST_RAND_BYTES_STEP], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_SST_HAVE_SST_RAND_BYTES_STEP macro.
#]dnl
m4_ifdef(
  [DEFINE_SST_HAVE_SST_RAND_BYTES_STEP_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_SST_HAVE_SST_RAND_BYTES_STEP has already been called
  ])],
  [m4_define([DEFINE_SST_HAVE_SST_RAND_BYTES_STEP_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_SST_HAVE_SST_RAND_BYTES_STEP requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl

AC_REQUIRE([DEFINE_HAVE_OPENSSL_RAND_H])
AC_REQUIRE([DEFINE_HAVE_RAND_BYTES])
AC_REQUIRE([DEFINE_HAVE_LIB_CRYPTO])

GATBPS_CHECK_VARS(
  [sst_RAND_bytes_step],
  [SST_HAVE_SST_RAND_BYTES_STEP],
  [
    HAVE_OPENSSL_RAND_H
    HAVE_RAND_BYTES
    HAVE_LIB_CRYPTO
  ])

:;}])[]dnl
