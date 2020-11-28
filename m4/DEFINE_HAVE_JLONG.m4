dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_HAVE_JLONG], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_HAVE_JLONG macro.
#]dnl
m4_ifdef(
  [DEFINE_HAVE_JLONG_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_HAVE_JLONG has already been called
  ])],
  [m4_define([DEFINE_HAVE_JLONG_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_HAVE_JLONG requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl

AC_REQUIRE([DEFINE_HAVE_JLONG_COMPILE])
AC_REQUIRE([DEFINE_HAVE_C_INCLUDE_JNI_H])
AC_REQUIRE([DEFINE_WITH_JNI])

AC_REQUIRE([DEFINE_CFLAGS])
AC_REQUIRE([DEFINE_CPPFLAGS])
AC_REQUIRE([DEFINE_LIBS])

AC_LANG_PUSH([C])
GATBPS_CHECK_RUN(
  [jlong],
  [HAVE_JLONG],
  [[
    #include <jni.h>
    #include <stdlib.h>
  ]],
  [[
    if ((jlong)(-1) > 0) {
      return EXIT_FAILURE;
    }
  ]],
  [gatbps_cv_HAVE_JLONG_COMPILE],
  [
    HAVE_JLONG_COMPILE
    HAVE_C_INCLUDE_JNI_H
    WITH_JNI
  ])
AC_LANG_POP([C])

:;}])[]dnl
