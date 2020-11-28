dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_HAVE_BN_LSHIFT], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_HAVE_BN_LSHIFT macro.
#]dnl
m4_ifdef(
  [DEFINE_HAVE_BN_LSHIFT_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_HAVE_BN_LSHIFT has already been called
  ])],
  [m4_define([DEFINE_HAVE_BN_LSHIFT_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_HAVE_BN_LSHIFT requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl

AC_REQUIRE([DEFINE_HAVE_BIGNUM])
AC_REQUIRE([DEFINE_HAVE_OPENSSL_BN_H])
AC_REQUIRE([DEFINE_HAVE_LIB_CRYPTO])

AC_REQUIRE([DEFINE_CFLAGS])
AC_REQUIRE([DEFINE_CPPFLAGS])
AC_REQUIRE([DEFINE_LIBS])

AC_LANG_PUSH([C])
GATBPS_CHECK_LINK(
  [BN_lshift],
  [HAVE_BN_LSHIFT],
  [[
    #include <openssl/bn.h>
  ]],
  [[
    int x1 = BN_lshift(
      (BIGNUM *)0,
      (BIGNUM const *)0,
      (int)1
    );
    (void)x1;
  ]],
  [
    HAVE_BIGNUM
    HAVE_OPENSSL_BN_H
    HAVE_LIB_CRYPTO
  ])
AC_LANG_POP([C])

:;}])[]dnl
