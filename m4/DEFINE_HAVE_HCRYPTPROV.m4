dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_HAVE_HCRYPTPROV], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_HAVE_HCRYPTPROV macro.
#]dnl
m4_ifdef(
  [DEFINE_HAVE_HCRYPTPROV_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_HAVE_HCRYPTPROV has already been called
  ])],
  [m4_define([DEFINE_HAVE_HCRYPTPROV_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_HAVE_HCRYPTPROV requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl

AC_REQUIRE([DEFINE_HAVE_WINCRYPT_H])
AC_REQUIRE([DEFINE_HAVE_WINDOWS])
AC_REQUIRE([DEFINE_WITH_WINDOWS])

AC_REQUIRE([DEFINE_CFLAGS])
AC_REQUIRE([DEFINE_CPPFLAGS])

AC_LANG_PUSH([C])
GATBPS_CHECK_COMPILE(
  [HCRYPTPROV],
  [HAVE_HCRYPTPROV],
  [[
    #include <windows.h>
    #include <wincrypt.h>
  ]],
  [[
    HCRYPTPROV x1 = {0};
    (void)x1;
  ]],
  [
    HAVE_WINCRYPT_H
    HAVE_WINDOWS
    WITH_WINDOWS
  ])
AC_LANG_POP([C])

:;}])[]dnl
