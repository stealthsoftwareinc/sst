dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_WITH_WINDOWS], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_WITH_WINDOWS macro.
#

]m4_ifdef(
  [DEFINE_WITH_WINDOWS_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_WITH_WINDOWS has already been called
  ])],
  [m4_define([DEFINE_WITH_WINDOWS_HAS_BEEN_CALLED])])[

]m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_WITH_WINDOWS requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[

]GATBPS_ARG_WITH_BOOL(
  [permission to use the Windows API],
  [WITH_WINDOWS],
  [windows],
  [yes],
  [permit the use of the Windows API],
  [forbid the use of the Windows API])[

:;}]])[]dnl
