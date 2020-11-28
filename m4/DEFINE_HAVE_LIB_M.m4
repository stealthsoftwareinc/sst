dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_HAVE_LIB_M], [[{

]AC_BEFORE([$0], [DEFINE_LIBS])[

#
# The block that contains this comment is the expansion of the
# DEFINE_HAVE_LIB_M macro.
#]dnl
m4_ifdef(
  [DEFINE_HAVE_LIB_M_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_HAVE_LIB_M has already been called
  ])],
  [m4_define([DEFINE_HAVE_LIB_M_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_HAVE_LIB_M requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl

AC_REQUIRE([DEFINE_CFLAGS])
AC_REQUIRE([DEFINE_CPPFLAGS])

GATBPS_CHECK_LIB(
  [-lm],
  [HAVE_LIB_M],
  [-lm],
  [
  ])

case "$[]{HAVE_LIB_M}" in
  '1')
    LIBS='-lm '"$[]{LIBS}"
  ;;
esac

:;}])[]dnl
