dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_SST_ENABLE_LIVE_MEMORY_FILLING], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_SST_ENABLE_LIVE_MEMORY_FILLING macro.
#]dnl
m4_ifdef(
  [DEFINE_SST_ENABLE_LIVE_MEMORY_FILLING_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_SST_ENABLE_LIVE_MEMORY_FILLING has already been called
  ])],
  [m4_define([DEFINE_SST_ENABLE_LIVE_MEMORY_FILLING_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_SST_ENABLE_LIVE_MEMORY_FILLING requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl
[

]GATBPS_ARG_ENABLE_BOOL(
  [
    permission to enable live memory filling
  ],
  [SST_ENABLE_LIVE_MEMORY_FILLING],
  [live-memory-filling],
  [yes],
  [
    enable live memory filling
  ],
  [
    disable live memory filling
  ])[

:;}]])[]dnl
