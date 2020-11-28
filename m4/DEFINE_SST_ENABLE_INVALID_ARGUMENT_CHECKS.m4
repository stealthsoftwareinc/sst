dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_SST_ENABLE_INVALID_ARGUMENT_CHECKS], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_SST_ENABLE_INVALID_ARGUMENT_CHECKS macro.
#]dnl
m4_ifdef(
  [DEFINE_SST_ENABLE_INVALID_ARGUMENT_CHECKS_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_SST_ENABLE_INVALID_ARGUMENT_CHECKS has already been called
  ])],
  [m4_define([DEFINE_SST_ENABLE_INVALID_ARGUMENT_CHECKS_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_SST_ENABLE_INVALID_ARGUMENT_CHECKS requires exactly 0
    arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl
[

]GATBPS_ARG_ENABLE_BOOL(
  [
    permission to enable invalid argument checks
  ],
  [SST_ENABLE_INVALID_ARGUMENT_CHECKS],
  [invalid-argument-checks],
  [yes],
  [
    enable invalid argument checks
  ],
  [
    disable invalid argument checks
  ])[

:;}]])[]dnl
