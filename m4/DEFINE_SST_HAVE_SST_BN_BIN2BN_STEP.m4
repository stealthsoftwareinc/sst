dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_SST_HAVE_SST_BN_BIN2BN_STEP], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_SST_HAVE_SST_BN_BIN2BN_STEP macro.
#]dnl
m4_ifdef(
  [DEFINE_SST_HAVE_SST_BN_BIN2BN_STEP_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_SST_HAVE_SST_BN_BIN2BN_STEP has already been called
  ])],
  [m4_define([DEFINE_SST_HAVE_SST_BN_BIN2BN_STEP_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_SST_HAVE_SST_BN_BIN2BN_STEP requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl

AC_REQUIRE([DEFINE_HAVE_BIGNUM])
AC_REQUIRE([DEFINE_HAVE_BN_ADD])
AC_REQUIRE([DEFINE_HAVE_BN_BIN2BN])
AC_REQUIRE([DEFINE_HAVE_BN_CTX])
AC_REQUIRE([DEFINE_HAVE_BN_CTX_END])
AC_REQUIRE([DEFINE_HAVE_BN_CTX_GET])
AC_REQUIRE([DEFINE_HAVE_BN_CTX_START])
AC_REQUIRE([DEFINE_HAVE_BN_FREE])
AC_REQUIRE([DEFINE_HAVE_BN_LSHIFT])
AC_REQUIRE([DEFINE_HAVE_OPENSSL_BN_H])
AC_REQUIRE([DEFINE_HAVE_LIB_CRYPTO])

GATBPS_CHECK_VARS(
  [sst_BN_bin2bn_step],
  [SST_HAVE_SST_BN_BIN2BN_STEP],
  [
    HAVE_BIGNUM
    HAVE_BN_ADD
    HAVE_BN_BIN2BN
    HAVE_BN_CTX
    HAVE_BN_CTX_END
    HAVE_BN_CTX_GET
    HAVE_BN_CTX_START
    HAVE_BN_FREE
    HAVE_BN_LSHIFT
    HAVE_OPENSSL_BN_H
    HAVE_LIB_CRYPTO
  ])

:;}])[]dnl
