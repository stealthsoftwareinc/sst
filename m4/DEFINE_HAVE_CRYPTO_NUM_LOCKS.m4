dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_HAVE_CRYPTO_NUM_LOCKS], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_HAVE_CRYPTO_NUM_LOCKS macro.
#]dnl
m4_ifdef(
  [DEFINE_HAVE_CRYPTO_NUM_LOCKS_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_HAVE_CRYPTO_NUM_LOCKS has already been called
  ])],
  [m4_define([DEFINE_HAVE_CRYPTO_NUM_LOCKS_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_HAVE_CRYPTO_NUM_LOCKS requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl

AC_REQUIRE([DEFINE_HAVE_OPENSSL_CRYPTO_H])
AC_REQUIRE([DEFINE_HAVE_LIB_CRYPTO])

AC_REQUIRE([DEFINE_CFLAGS])
AC_REQUIRE([DEFINE_CPPFLAGS])
AC_REQUIRE([DEFINE_LIBS])

AC_LANG_PUSH([C])
GATBPS_CHECK_LINK(
  [CRYPTO_num_locks],
  [HAVE_CRYPTO_NUM_LOCKS],
  [[
    #include <openssl/crypto.h>
  ]],
  [[
    int x1 = CRYPTO_num_locks();
    (void)x1;
  ]],
  [
    HAVE_OPENSSL_CRYPTO_H
    HAVE_LIB_CRYPTO
  ])
AC_LANG_POP([C])

:;}])[]dnl
