dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_HAVE_CRYPTGENRANDOM], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_HAVE_CRYPTGENRANDOM macro.
#]dnl
m4_ifdef(
  [DEFINE_HAVE_CRYPTGENRANDOM_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_HAVE_CRYPTGENRANDOM has already been called
  ])],
  [m4_define([DEFINE_HAVE_CRYPTGENRANDOM_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_HAVE_CRYPTGENRANDOM requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl

AC_REQUIRE([DEFINE_HAVE_BOOL])
AC_REQUIRE([DEFINE_HAVE_BYTE])
AC_REQUIRE([DEFINE_HAVE_DWORD])
AC_REQUIRE([DEFINE_HAVE_HCRYPTPROV])
AC_REQUIRE([DEFINE_HAVE_WINCRYPT_H])
AC_REQUIRE([DEFINE_HAVE_WINDOWS])
AC_REQUIRE([DEFINE_WITH_WINDOWS])

AC_REQUIRE([DEFINE_CFLAGS])
AC_REQUIRE([DEFINE_CPPFLAGS])
AC_REQUIRE([DEFINE_LIBS])

AC_LANG_PUSH([C])
GATBPS_CHECK_LINK(
  [CryptGenRandom],
  [HAVE_CRYPTGENRANDOM],
  [[
    #include <windows.h>
    #include <wincrypt.h>
  ]],
  [[
    HCRYPTPROV x1 = {0};
    BOOL x2 = CryptGenRandom(
      x1,
      (DWORD)1,
      (BYTE *)0
    );
    (void)x2;
  ]],
  [
    HAVE_BOOL
    HAVE_BYTE
    HAVE_DWORD
    HAVE_HCRYPTPROV
    HAVE_WINCRYPT_H
    HAVE_WINDOWS
    WITH_WINDOWS
  ])
AC_LANG_POP([C])

:;}])[]dnl
