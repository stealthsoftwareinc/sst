dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_HAVE_OBSTACK_H], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_HAVE_OBSTACK_H macro.
#]dnl
m4_ifdef(
  [DEFINE_HAVE_OBSTACK_H_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_HAVE_OBSTACK_H has already been called
  ])],
  [m4_define([DEFINE_HAVE_OBSTACK_H_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_HAVE_OBSTACK_H requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl

AC_REQUIRE([DEFINE_CFLAGS])
AC_REQUIRE([DEFINE_CPPFLAGS])

AC_LANG_PUSH([C])
GATBPS_CHECK_HEADER(
  [obstack.h],
  [HAVE_OBSTACK_H],
  [[
    #include <obstack.h>
    #include <obstack.h>
  ]],
  [
  ])
AC_LANG_POP([C])

:;}])[]dnl
