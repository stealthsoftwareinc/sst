dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_EXE_LDFLAGS], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_EXE_LDFLAGS macro.
#

]m4_ifdef(
  [DEFINE_EXE_LDFLAGS_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_EXE_LDFLAGS has already been called
  ])],
  [m4_define([DEFINE_EXE_LDFLAGS_HAS_BEEN_CALLED])])[

]m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_EXE_LDFLAGS requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[

]AC_REQUIRE([GATBPS_DEFINE_EXE_LDFLAGS])[

:;}]])[]dnl
