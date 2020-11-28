dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_HAVE_BIGNUM], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_HAVE_BIGNUM macro.
#]dnl
m4_ifdef(
  [DEFINE_HAVE_BIGNUM_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_HAVE_BIGNUM has already been called
  ])],
  [m4_define([DEFINE_HAVE_BIGNUM_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_HAVE_BIGNUM requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl

AC_REQUIRE([DEFINE_HAVE_OPENSSL_BN_H])
AC_REQUIRE([DEFINE_HAVE_LIB_CRYPTO])

AC_REQUIRE([DEFINE_CFLAGS])
AC_REQUIRE([DEFINE_CPPFLAGS])

AC_LANG_PUSH([C])
GATBPS_CHECK_COMPILE(
  [BIGNUM],
  [HAVE_BIGNUM],
  [[
    #include <openssl/bn.h>
  ]],
  [[
    BIGNUM * x1 = 0;
    (void)x1;
  ]],
  [
    HAVE_OPENSSL_BN_H
    HAVE_LIB_CRYPTO
  ])
AC_LANG_POP([C])

:;}])[]dnl
