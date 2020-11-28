dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_SST_HAVE_SST_JLONGPTR], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_SST_HAVE_SST_JLONGPTR macro.
#]dnl
m4_ifdef(
  [DEFINE_SST_HAVE_SST_JLONGPTR_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_SST_HAVE_SST_JLONGPTR has already been called
  ])],
  [m4_define([DEFINE_SST_HAVE_SST_JLONGPTR_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_SST_HAVE_SST_JLONGPTR requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl

AC_REQUIRE([DEFINE_HAVE_INTPTR_MAXVAL])
AC_REQUIRE([DEFINE_HAVE_JLONG])
AC_REQUIRE([DEFINE_HAVE_STDINT_H])
AC_REQUIRE([DEFINE_WITH_JNI])

AC_REQUIRE([DEFINE_CFLAGS])
AC_REQUIRE([DEFINE_CPPFLAGS])

AC_LANG_PUSH([C])
GATBPS_CHECK_COMPILE(
  [sst_jlongptr],
  [SST_HAVE_SST_JLONGPTR],
  [[
    #include <stdint.h>
  ]],
  [[
    /*
     * We don't have to check INTPTR_MIN because C guarantees that
     * T_MIN is either -T_MAX or -T_MAX - 1 for any signed integer
     * type T. In other words, if INTPTR_MAX <= 2^63 - 1, then the
     * range of intptr_t is within 64-bit two's complement range,
     * which is the range of jlong by definition.
     */

    #if (INTPTR_MAX > 9223372036854775807)
    {
      #include <cause_a_compilation_error>
    }
    #endif
  ]],
  [
    HAVE_INTPTR_MAXVAL
    HAVE_JLONG
    HAVE_STDINT_H
    WITH_JNI
  ])
AC_LANG_POP([C])

:;}])[]dnl
