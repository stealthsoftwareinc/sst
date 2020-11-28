dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS macro.
#]dnl
m4_ifdef(
  [DEFINE_SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS has already been called
  ])],
  [m4_define([DEFINE_SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS requires exactly 0
    arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl
[

]AC_REQUIRE([DEFINE_SST_ENABLE_INVALID_ARGUMENT_CHECKS])[

]GATBPS_ARG_ENABLE_BOOL(
  [
    permission to enable undefined behavior checks
  ],
  [SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS],
  [undefined-behavior-checks],
  [yes],
  [
    enable undefined behavior checks
  ],
  [
    disable undefined behavior checks
  ])[

case "$][{SST_ENABLE_INVALID_ARGUMENT_CHECKS}" in
  '0')
    case "$][{SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS}" in
      '1')
        ]GATBPS_MSG_ERROR([
          undefined behavior checks must be disabled when invalid
          argument checks are disabled
        ])[
      ;;
    esac
  ;;
esac

:;}]])[]dnl
