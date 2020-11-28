dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_WITH_WINDOWS_OR_DIE], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_WITH_WINDOWS_OR_DIE macro.
#

]m4_ifdef(
  [DEFINE_WITH_WINDOWS_OR_DIE_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_WITH_WINDOWS_OR_DIE has already been called
  ])],
  [m4_define([DEFINE_WITH_WINDOWS_OR_DIE_HAS_BEEN_CALLED])])[

]m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_WITH_WINDOWS_OR_DIE requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[

]GATBPS_ARG_WITH_BOOL(
  [insistence to use the Windows API],
  [WITH_WINDOWS_OR_DIE],
  [windows-or-die],
  [no],
  [demand the use of the Windows API],
  [ignore the use of the Windows API])[

:;}]])[]dnl
