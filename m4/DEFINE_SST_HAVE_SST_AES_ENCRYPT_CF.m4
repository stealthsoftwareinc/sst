dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_SST_HAVE_SST_AES_ENCRYPT_CF], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_SST_HAVE_SST_AES_ENCRYPT_CF macro.
#]dnl
m4_ifdef(
  [DEFINE_SST_HAVE_SST_AES_ENCRYPT_CF_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_SST_HAVE_SST_AES_ENCRYPT_CF has already been called
  ])],
  [m4_define([DEFINE_SST_HAVE_SST_AES_ENCRYPT_CF_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_SST_HAVE_SST_AES_ENCRYPT_CF requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl

AC_REQUIRE([DEFINE_HAVE_AES_ENCRYPT])
AC_REQUIRE([DEFINE_HAVE_NETTLE_AES_H])
AC_REQUIRE([DEFINE_HAVE_NETTLE_NETTLE_TYPES_H])
AC_REQUIRE([DEFINE_HAVE_UINT8_T_IN_NETTLE_NETTLE_TYPES_H])
AC_REQUIRE([DEFINE_SST_HAVE_SST_NETTLE_CIPHER_CTX])
AC_REQUIRE([DEFINE_SST_HAVE_SST_NETTLE_SIZE])
AC_REQUIRE([DEFINE_WITH_NETTLE])

GATBPS_CHECK_VARS(
  [sst_aes_encrypt_cf],
  [SST_HAVE_SST_AES_ENCRYPT_CF],
  [
    HAVE_AES_ENCRYPT
    HAVE_NETTLE_AES_H
    HAVE_NETTLE_NETTLE_TYPES_H
    HAVE_UINT8_T_IN_NETTLE_NETTLE_TYPES_H
    SST_HAVE_SST_NETTLE_CIPHER_CTX
    SST_HAVE_SST_NETTLE_SIZE
    WITH_NETTLE
  ])

:;}])[]dnl
