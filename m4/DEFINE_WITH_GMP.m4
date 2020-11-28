dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN_ONCE([DEFINE_WITH_GMP], [[{

]GATBPS_ARG_WITH_BOOL(
  [permission to use GMP],
  [WITH_GMP],
  [gmp],
  [yes],
  [permit the use of GMP],
  [forbid the use of GMP])[

:;}]])
