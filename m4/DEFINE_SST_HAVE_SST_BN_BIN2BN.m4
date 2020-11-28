dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_SST_HAVE_SST_BN_BIN2BN], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_SST_HAVE_SST_BN_BIN2BN macro.
#]dnl
m4_ifdef(
  [DEFINE_SST_HAVE_SST_BN_BIN2BN_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_SST_HAVE_SST_BN_BIN2BN has already been called
  ])],
  [m4_define([DEFINE_SST_HAVE_SST_BN_BIN2BN_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_SST_HAVE_SST_BN_BIN2BN requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl

AC_REQUIRE([DEFINE_HAVE_BIGNUM])
AC_REQUIRE([DEFINE_HAVE_BN_CTX])
AC_REQUIRE([DEFINE_HAVE_OPENSSL_BN_H])
AC_REQUIRE([DEFINE_SST_HAVE_SST_BN_BIN2BN_STEP])
AC_REQUIRE([DEFINE_HAVE_LIB_CRYPTO])

GATBPS_CHECK_VARS(
  [sst_BN_bin2bn],
  [SST_HAVE_SST_BN_BIN2BN],
  [
    HAVE_BIGNUM
    HAVE_BN_CTX
    HAVE_OPENSSL_BN_H
    SST_HAVE_SST_BN_BIN2BN_STEP
    HAVE_LIB_CRYPTO
  ])

:;}])[]dnl
