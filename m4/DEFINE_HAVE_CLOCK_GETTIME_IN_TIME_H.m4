dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_HAVE_CLOCK_GETTIME_IN_TIME_H], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_HAVE_CLOCK_GETTIME_IN_TIME_H macro.
#]dnl
m4_ifdef(
  [DEFINE_HAVE_CLOCK_GETTIME_IN_TIME_H_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_HAVE_CLOCK_GETTIME_IN_TIME_H has already been called
  ])],
  [m4_define([DEFINE_HAVE_CLOCK_GETTIME_IN_TIME_H_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_HAVE_CLOCK_GETTIME_IN_TIME_H requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl

AC_REQUIRE([DEFINE_HAVE_CLOCKID_T_IN_TIME_H])
AC_REQUIRE([DEFINE_HAVE_STRUCT_TIMESPEC_IN_TIME_H])
AC_REQUIRE([DEFINE_WITH_POSIX])
AC_REQUIRE([DEFINE_WITH_POSIX])

AC_REQUIRE([DEFINE_CFLAGS])
AC_REQUIRE([DEFINE_CPPFLAGS])
AC_REQUIRE([DEFINE_LIBS])

AC_LANG_PUSH([C])
GATBPS_CHECK_LINK(
  [clock_gettime],
  [HAVE_CLOCK_GETTIME_IN_TIME_H],
  [[
    #include <time.h>
  ]],
  [[
    int const x1 = clock_gettime(
      (clockid_t)1,
      (struct timespec *)0
    );
    (void)x1;
  ]],
  [
    HAVE_CLOCKID_T_IN_TIME_H
    HAVE_STRUCT_TIMESPEC_IN_TIME_H
    WITH_POSIX
    WITH_POSIX
  ])
AC_LANG_POP([C])

:;}])[]dnl
