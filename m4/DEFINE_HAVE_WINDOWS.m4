dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_HAVE_WINDOWS], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_HAVE_WINDOWS macro.
#

]m4_ifdef(
  [DEFINE_HAVE_WINDOWS_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_HAVE_WINDOWS has already been called
  ])],
  [m4_define([DEFINE_HAVE_WINDOWS_HAS_BEEN_CALLED])])[

]m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_HAVE_WINDOWS requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[

]AC_REQUIRE([DEFINE_CFLAGS])[
]AC_REQUIRE([DEFINE_CPPFLAGS])[
]AC_REQUIRE([DEFINE_WITH_WINDOWS])[

]AC_LANG_PUSH([C])[

]GATBPS_CHECK_HEADER(
  [Windows],
  [HAVE_WINDOWS],
  [[
    #include <windows.h>
    #include <windows.h>
  ]],
  [
    WITH_WINDOWS
  ])[

]AC_LANG_POP([C])[

case $][HAVE_WINDOWS$][WITH_WINDOWS_OR_DIE in
  01)
    ]GATBPS_MSG_ERROR([
      --with-windows-or-die triggered
    ])[
  ;;
esac

:;}]])[]dnl
