dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_SST_HAVE_SST_NETTLE_CIPHER_CTX], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_SST_HAVE_SST_NETTLE_CIPHER_CTX macro.
#]dnl
m4_ifdef(
  [DEFINE_SST_HAVE_SST_NETTLE_CIPHER_CTX_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_SST_HAVE_SST_NETTLE_CIPHER_CTX has already been called
  ])],
  [m4_define([DEFINE_SST_HAVE_SST_NETTLE_CIPHER_CTX_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_SST_HAVE_SST_NETTLE_CIPHER_CTX requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl

AC_REQUIRE([DEFINE_HAVE_NETTLE_CIPHER_OR_CRYPT_FUNC])
AC_REQUIRE([DEFINE_HAVE_NETTLE_NETTLE_TYPES_H])
AC_REQUIRE([DEFINE_WITH_NETTLE])

GATBPS_CHECK_VARS(
  [sst_nettle_cipher_ctx],
  [SST_HAVE_SST_NETTLE_CIPHER_CTX],
  [
    HAVE_NETTLE_CIPHER_OR_CRYPT_FUNC
    HAVE_NETTLE_NETTLE_TYPES_H
    WITH_NETTLE
  ])

:;}])[]dnl
