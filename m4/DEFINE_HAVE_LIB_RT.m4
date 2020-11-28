dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_HAVE_LIB_RT], [[{

]AC_BEFORE([$0], [DEFINE_LIBS])[

#
# The block that contains this comment is the expansion of the
# DEFINE_HAVE_LIB_RT macro.
#]dnl
m4_ifdef(
  [DEFINE_HAVE_LIB_RT_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_HAVE_LIB_RT has already been called
  ])],
  [m4_define([DEFINE_HAVE_LIB_RT_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_HAVE_LIB_RT requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl

AC_REQUIRE([DEFINE_WITH_POSIX])
AC_REQUIRE([DEFINE_WITH_POSIX])

AC_REQUIRE([DEFINE_CFLAGS])
AC_REQUIRE([DEFINE_CPPFLAGS])

GATBPS_CHECK_LIB(
  [-lrt],
  [HAVE_LIB_RT],
  [-lrt],
  [
    WITH_POSIX
    WITH_POSIX
  ])

case "$[]{HAVE_LIB_RT}" in
  '1')
    LIBS='-lrt '"$[]{LIBS}"
  ;;
esac

:;}])[]dnl
