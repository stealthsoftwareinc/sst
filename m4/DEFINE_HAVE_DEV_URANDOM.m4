dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_HAVE_DEV_URANDOM], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_HAVE_DEV_URANDOM macro.
#]dnl
m4_ifdef(
  [DEFINE_HAVE_DEV_URANDOM_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_HAVE_DEV_URANDOM has already been called
  ])],
  [m4_define([DEFINE_HAVE_DEV_URANDOM_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_HAVE_DEV_URANDOM requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl

AC_REQUIRE([DEFINE_WITH_POSIX])

AC_REQUIRE([DEFINE_CFLAGS])
AC_REQUIRE([DEFINE_CPPFLAGS])
AC_REQUIRE([DEFINE_LIBS])
AC_REQUIRE([DEFINE_WITH_CROSS_DEV_URANDOM])

AC_LANG_PUSH([C])
GATBPS_CHECK_RUN(
  [/dev/urandom],
  [HAVE_DEV_URANDOM],
  [[
    #include <stdio.h>
    #include <stdlib.h>
  ]],
  [[
    FILE * const f = fopen("/dev/urandom", "rb");
    if (f == NULL) {
      return EXIT_FAILURE;
    }
    (void)fclose(f);
  ]],
  [gatbps_cv_WITH_CROSS_DEV_URANDOM],
  [
    WITH_POSIX
  ])
AC_LANG_POP([C])

:;}])[]dnl
