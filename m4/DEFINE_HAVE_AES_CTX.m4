dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_HAVE_AES_CTX], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_HAVE_AES_CTX macro.
#]dnl
m4_ifdef(
  [DEFINE_HAVE_AES_CTX_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_HAVE_AES_CTX has already been called
  ])],
  [m4_define([DEFINE_HAVE_AES_CTX_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_HAVE_AES_CTX requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl

AC_REQUIRE([DEFINE_HAVE_NETTLE_AES_H])
AC_REQUIRE([DEFINE_WITH_NETTLE])

AC_REQUIRE([DEFINE_CFLAGS])
AC_REQUIRE([DEFINE_CPPFLAGS])

AC_LANG_PUSH([C])
GATBPS_CHECK_COMPILE(
  [aes_ctx],
  [HAVE_AES_CTX],
  [[
    #include <nettle/aes.h>
  ]],
  [[
    struct aes_ctx x1 = {0};
    (void)x1;
  ]],
  [
    HAVE_NETTLE_AES_H
    WITH_NETTLE
  ])
AC_LANG_POP([C])

:;}])[]dnl