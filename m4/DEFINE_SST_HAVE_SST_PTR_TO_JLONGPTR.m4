dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_SST_HAVE_SST_PTR_TO_JLONGPTR], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_SST_HAVE_SST_PTR_TO_JLONGPTR macro.
#]dnl
m4_ifdef(
  [DEFINE_SST_HAVE_SST_PTR_TO_JLONGPTR_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_SST_HAVE_SST_PTR_TO_JLONGPTR has already been called
  ])],
  [m4_define([DEFINE_SST_HAVE_SST_PTR_TO_JLONGPTR_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_SST_HAVE_SST_PTR_TO_JLONGPTR requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl

AC_REQUIRE([DEFINE_HAVE_INTPTR_T])
AC_REQUIRE([DEFINE_HAVE_STDINT_H])
AC_REQUIRE([DEFINE_SST_HAVE_SST_JLONGPTR])
AC_REQUIRE([DEFINE_WITH_JNI])

GATBPS_CHECK_VARS(
  [sst_ptr_to_jlongptr],
  [SST_HAVE_SST_PTR_TO_JLONGPTR],
  [
    HAVE_INTPTR_T
    HAVE_STDINT_H
    SST_HAVE_SST_JLONGPTR
    WITH_JNI
  ])

:;}])[]dnl
