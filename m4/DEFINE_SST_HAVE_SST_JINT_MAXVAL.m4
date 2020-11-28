dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_SST_HAVE_SST_JINT_MAXVAL], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_SST_HAVE_SST_JINT_MAXVAL macro.
#]dnl
m4_ifdef(
  [DEFINE_SST_HAVE_SST_JINT_MAXVAL_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_SST_HAVE_SST_JINT_MAXVAL has already been called
  ])],
  [m4_define([DEFINE_SST_HAVE_SST_JINT_MAXVAL_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_SST_HAVE_SST_JINT_MAXVAL requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl

AC_REQUIRE([DEFINE_HAVE_C_INCLUDE_JNI_H])
AC_REQUIRE([DEFINE_WITH_JNI])

GATBPS_CHECK_VARS(
  [SST_JINT_MAXVAL],
  [SST_HAVE_SST_JINT_MAXVAL],
  [
    HAVE_C_INCLUDE_JNI_H
    WITH_JNI
  ])

:;}])[]dnl
