dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_WITH_POSIX], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_WITH_POSIX macro.
#

]m4_ifdef(
  [DEFINE_WITH_POSIX_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_WITH_POSIX has already been called
  ])],
  [m4_define([DEFINE_WITH_POSIX_HAS_BEEN_CALLED])])[

]m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_WITH_POSIX requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[

]GATBPS_ARG_WITH_BOOL(
  [permission to use POSIX],
  [WITH_POSIX],
  [posix],
  [yes],
  [permit the use of POSIX],
  [forbid the use of POSIX])[

:;};]])
