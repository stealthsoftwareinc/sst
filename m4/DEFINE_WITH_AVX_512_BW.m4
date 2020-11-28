dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN_ONCE([DEFINE_WITH_AVX_512_BW], [[{ :

]GATBPS_ARG_WITH_BOOL(
  [permission to use AVX-512 BW],
  [WITH_AVX_512_BW],
  [avx-512-bw],
  [yes],
  [permit the use of AVX-512 BW],
  [forbid the use of AVX-512 BW])[

}]])
