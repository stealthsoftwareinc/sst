dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_plaintextdir], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_plaintextdir macro.
#]dnl
m4_ifdef(
  [DEFINE_plaintextdir_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_plaintextdir has already been called
  ])],
  [m4_define([DEFINE_plaintextdir_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_plaintextdir requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl
[

]AC_REQUIRE([GATBPS_DEFINE_plaintextdir])[

:;}]])[]dnl
