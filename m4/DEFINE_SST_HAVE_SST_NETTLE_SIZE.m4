dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_SST_HAVE_SST_NETTLE_SIZE], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_SST_HAVE_SST_NETTLE_SIZE macro.
#]dnl
m4_ifdef(
  [DEFINE_SST_HAVE_SST_NETTLE_SIZE_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_SST_HAVE_SST_NETTLE_SIZE has already been called
  ])],
  [m4_define([DEFINE_SST_HAVE_SST_NETTLE_SIZE_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_SST_HAVE_SST_NETTLE_SIZE requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl

AC_REQUIRE([DEFINE_HAVE_NETTLE_NETTLE_TYPES_H])
AC_REQUIRE([DEFINE_WITH_NETTLE])

GATBPS_CHECK_VARS(
  [sst_nettle_size],
  [SST_HAVE_SST_NETTLE_SIZE],
  [
    HAVE_NETTLE_NETTLE_TYPES_H
    WITH_NETTLE
  ])

:;}])[]dnl
