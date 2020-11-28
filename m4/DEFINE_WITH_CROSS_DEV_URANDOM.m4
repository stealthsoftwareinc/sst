dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_WITH_CROSS_DEV_URANDOM], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_WITH_CROSS_DEV_URANDOM macro.
#]dnl
m4_ifdef(
  [DEFINE_WITH_CROSS_DEV_URANDOM_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_WITH_CROSS_DEV_URANDOM has already been called
  ])],
  [m4_define([DEFINE_WITH_CROSS_DEV_URANDOM_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_WITH_CROSS_DEV_URANDOM requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl

GATBPS_ARG_WITH_BOOL(
  [permission to assume that /dev/urandom is available on the host system when cross-compiling],
  [WITH_CROSS_DEV_URANDOM],
  [cross-dev-urandom],
  [no],
  [assume that /dev/urandom is available on the host system when cross-compiling],
  [assume that /dev/urandom is not available on the host system when cross-compiling])

:;}])[]dnl
