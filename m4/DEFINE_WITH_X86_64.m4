dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN_ONCE([DEFINE_WITH_X86_64], [[{ :

]GATBPS_ARG_WITH_BOOL(
  [permission to use x86_64 CPU features],
  [WITH_X86_64],
  [x86_64],
  [yes],
  [permit the use of x86_64 CPU features],
  [forbid the use of x86_64 CPU features])[

}]])
