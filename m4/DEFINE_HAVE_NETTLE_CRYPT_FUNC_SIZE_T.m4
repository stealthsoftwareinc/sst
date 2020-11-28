dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_HAVE_NETTLE_CRYPT_FUNC_SIZE_T], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_HAVE_NETTLE_CRYPT_FUNC_SIZE_T macro.
#]dnl
m4_ifdef(
  [DEFINE_HAVE_NETTLE_CRYPT_FUNC_SIZE_T_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_HAVE_NETTLE_CRYPT_FUNC_SIZE_T has already been called
  ])],
  [m4_define([DEFINE_HAVE_NETTLE_CRYPT_FUNC_SIZE_T_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_HAVE_NETTLE_CRYPT_FUNC_SIZE_T requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl

AC_REQUIRE([DEFINE_HAVE_NETTLE_NETTLE_TYPES_H])
AC_REQUIRE([DEFINE_HAVE_UINT8_T_IN_NETTLE_NETTLE_TYPES_H])
AC_REQUIRE([DEFINE_WITH_NETTLE])

AC_REQUIRE([DEFINE_CFLAGS])
AC_REQUIRE([DEFINE_CPPFLAGS])

AC_LANG_PUSH([C])
GATBPS_CHECK_COMPILE(
  [nettle_crypt_func (size_t)],
  [HAVE_NETTLE_CRYPT_FUNC_SIZE_T],
  [[
    #include <nettle/nettle-types.h>
    #include <stddef.h>
  ]],
  [[
    nettle_crypt_func x1;
    void x1(
      void *,
      size_t,
      uint8_t *,
      uint8_t const *
    );
  ]],
  [
    HAVE_NETTLE_NETTLE_TYPES_H
    HAVE_UINT8_T_IN_NETTLE_NETTLE_TYPES_H
    WITH_NETTLE
  ])
AC_LANG_POP([C])

:;}])[]dnl
