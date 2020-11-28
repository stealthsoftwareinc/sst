dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_SST_HAVE_SST_JSIZE_MINVAL], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_SST_HAVE_SST_JSIZE_MINVAL macro.
#]dnl
m4_ifdef(
  [DEFINE_SST_HAVE_SST_JSIZE_MINVAL_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_SST_HAVE_SST_JSIZE_MINVAL has already been called
  ])],
  [m4_define([DEFINE_SST_HAVE_SST_JSIZE_MINVAL_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_SST_HAVE_SST_JSIZE_MINVAL requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl

AC_REQUIRE([DEFINE_SST_HAVE_SST_JINT_MINVAL])

GATBPS_CHECK_VARS(
  [SST_JSIZE_MINVAL],
  [SST_HAVE_SST_JSIZE_MINVAL],
  [
    SST_HAVE_SST_JINT_MINVAL
  ])

:;}])[]dnl
