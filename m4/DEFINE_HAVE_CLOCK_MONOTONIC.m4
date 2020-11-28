dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_HAVE_CLOCK_MONOTONIC], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_HAVE_CLOCK_MONOTONIC macro.
#]dnl
m4_ifdef(
  [DEFINE_HAVE_CLOCK_MONOTONIC_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_HAVE_CLOCK_MONOTONIC has already been called
  ])],
  [m4_define([DEFINE_HAVE_CLOCK_MONOTONIC_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_HAVE_CLOCK_MONOTONIC requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl

AC_REQUIRE([DEFINE_HAVE_CLOCKID_T_IN_TIME_H])
AC_REQUIRE([DEFINE_WITH_POSIX])
AC_REQUIRE([DEFINE_WITH_POSIX])

AC_REQUIRE([DEFINE_CFLAGS])
AC_REQUIRE([DEFINE_CPPFLAGS])
AC_REQUIRE([DEFINE_LIBS])

AC_LANG_PUSH([C])
GATBPS_CHECK_LINK(
  [CLOCK_MONOTONIC],
  [HAVE_CLOCK_MONOTONIC],
  [[
    #include <time.h>
  ]],
  [[
    clockid_t x1 = CLOCK_MONOTONIC;
    (void)x1;
  ]],
  [
    HAVE_CLOCKID_T_IN_TIME_H
    WITH_POSIX
    WITH_POSIX
  ])
AC_LANG_POP([C])

:;}])[]dnl
