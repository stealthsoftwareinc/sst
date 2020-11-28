dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN_ONCE([DEFINE_WITH_SSE], [[{

]GATBPS_ARG_WITH_BOOL(
  [permission to use SSE],
  [WITH_SSE],
  [sse],
  [yes],
  [permit the use of SSE],
  [forbid the use of SSE])[

:;}]])
