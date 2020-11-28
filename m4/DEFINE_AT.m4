dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_AT], [[{

#
# The block that contains this comment is the expansion of the DEFINE_AT
# macro.
#]dnl
m4_ifdef(
  [DEFINE_AT_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_AT has already been called
  ])],
  [m4_define([DEFINE_AT_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_AT requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl
[

]AC_REQUIRE([GATBPS_DEFINE_AT])[

:;}]])[]dnl
