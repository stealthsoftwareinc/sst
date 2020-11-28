dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_HAVE_AES_ENCRYPT], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_HAVE_AES_ENCRYPT macro.
#]dnl
m4_ifdef(
  [DEFINE_HAVE_AES_ENCRYPT_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_HAVE_AES_ENCRYPT has already been called
  ])],
  [m4_define([DEFINE_HAVE_AES_ENCRYPT_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_HAVE_AES_ENCRYPT requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl

AC_REQUIRE([DEFINE_HAVE_AES_CTX])
AC_REQUIRE([DEFINE_HAVE_NETTLE_AES_H])
AC_REQUIRE([DEFINE_HAVE_NETTLE_NETTLE_TYPES_H])
AC_REQUIRE([DEFINE_HAVE_UINT8_T_IN_NETTLE_NETTLE_TYPES_H])
AC_REQUIRE([DEFINE_WITH_NETTLE])

AC_REQUIRE([DEFINE_CFLAGS])
AC_REQUIRE([DEFINE_CPPFLAGS])
AC_REQUIRE([DEFINE_HAVE_NETTLE_CRYPT_FUNC_SIZE_T])
AC_REQUIRE([DEFINE_LIBS])

AC_LANG_PUSH([C])
GATBPS_CHECK_LINK(
  [aes_encrypt],
  [HAVE_AES_ENCRYPT],
  [[
    #include <nettle/aes.h>
    #include <nettle/nettle-types.h>
    #include <stddef.h>
  ]],
  [[
    #if (HAVE_NETTLE_CRYPT_FUNC_SIZE_T)
    {
      aes_encrypt(
        (struct aes_ctx *)0,
        (size_t)1,
        (uint8_t *)0,
        (uint8_t const *)0
      );
    }
    #else
    {
      aes_encrypt(
        (struct aes_ctx *)0,
        (unsigned int)1,
        (uint8_t *)0,
        (uint8_t const *)0
      );
    }
    #endif
  ]],
  [
    HAVE_AES_CTX
    HAVE_NETTLE_AES_H
    HAVE_NETTLE_NETTLE_TYPES_H
    HAVE_UINT8_T_IN_NETTLE_NETTLE_TYPES_H
    WITH_NETTLE
  ])
AC_LANG_POP([C])

:;}])[]dnl
