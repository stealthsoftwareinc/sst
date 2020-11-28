dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_HAVE_JLONG_COMPILE], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_HAVE_JLONG_COMPILE macro.
#]dnl
m4_ifdef(
  [DEFINE_HAVE_JLONG_COMPILE_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_HAVE_JLONG_COMPILE has already been called
  ])],
  [m4_define([DEFINE_HAVE_JLONG_COMPILE_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_HAVE_JLONG_COMPILE requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl

AC_REQUIRE([DEFINE_HAVE_C_INCLUDE_JNI_H])
AC_REQUIRE([DEFINE_WITH_JNI])

AC_REQUIRE([DEFINE_CFLAGS])
AC_REQUIRE([DEFINE_CPPFLAGS])

AC_LANG_PUSH([C])
GATBPS_CHECK_COMPILE(
  [jlong],
  [HAVE_JLONG_COMPILE],
  [[
    #include <jni.h>
  ]],
  [[
    jlong x1;
    x1 = 1;
    (void)x1;
    (void)((jlong)1 % 1);
  ]],
  [
    HAVE_C_INCLUDE_JNI_H
    WITH_JNI
  ])
AC_LANG_POP([C])

:;}])[]dnl
