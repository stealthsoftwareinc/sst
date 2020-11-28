dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_SST_HAVE_SST_WALL_CLOCK_CLOCK_MONOTONIC], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_SST_HAVE_SST_WALL_CLOCK_CLOCK_MONOTONIC macro.
#]dnl
m4_ifdef(
  [DEFINE_SST_HAVE_SST_WALL_CLOCK_CLOCK_MONOTONIC_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_SST_HAVE_SST_WALL_CLOCK_CLOCK_MONOTONIC has already been
    called
  ])],
  [m4_define([DEFINE_SST_HAVE_SST_WALL_CLOCK_CLOCK_MONOTONIC_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_SST_HAVE_SST_WALL_CLOCK_CLOCK_MONOTONIC requires exactly 0
    arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl

AC_REQUIRE([DEFINE_HAVE_CLOCK_GETTIME_IN_TIME_H])
AC_REQUIRE([DEFINE_HAVE_CLOCK_MONOTONIC])
AC_REQUIRE([DEFINE_HAVE_STRUCT_TIMESPEC_IN_TIME_H])
AC_REQUIRE([DEFINE_WITH_POSIX])
AC_REQUIRE([DEFINE_WITH_POSIX])

GATBPS_CHECK_VARS(
  [sst_wall_time_CLOCK_MONOTONIC],
  [SST_HAVE_SST_WALL_CLOCK_CLOCK_MONOTONIC],
  [
    HAVE_CLOCK_GETTIME_IN_TIME_H
    HAVE_CLOCK_MONOTONIC
    HAVE_STRUCT_TIMESPEC_IN_TIME_H
    WITH_POSIX
    WITH_POSIX
  ])

:;}])[]dnl
