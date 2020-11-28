dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN_ONCE([DEFINE_HAVE_AVX_512_BW], [[{ :

]AC_REQUIRE([DEFINE_HAVE_CFLAG_MAVX512BW])[
]GATBPS_SOFT_REQUIRE([[DEFINE_HAVE_CFLAG_MAVX512F]])[
]GATBPS_SOFT_REQUIRE([[DEFINE_HAVE_CXXFLAG_MAVX512BW]])[
]GATBPS_SOFT_REQUIRE([[DEFINE_HAVE_CXXFLAG_MAVX512F]])[
]GATBPS_SOFT_REQUIRE([[DEFINE_WITH_AVX_512_BW]])[
]GATBPS_SOFT_REQUIRE([[DEFINE_WITH_AVX_512_F]])[

]GATBPS_CHECK_VARS(
  [AVX-512 BW],
  [HAVE_AVX_512_BW],
  [
    HAVE_CFLAG_MAVX512BW
    ]GATBPS_SOFT_VAR_DEP([[HAVE_CFLAG_MAVX512F]])[
    ]GATBPS_SOFT_VAR_DEP([[HAVE_CXXFLAG_MAVX512BW]])[
    ]GATBPS_SOFT_VAR_DEP([[HAVE_CXXFLAG_MAVX512F]])[
    ]GATBPS_SOFT_VAR_DEP([[WITH_AVX_512_BW]])[
    ]GATBPS_SOFT_VAR_DEP([[WITH_AVX_512_F]])[
  ])[

]GATBPS_ARG_WITH_BOOL(
  [insistence to use AVX-512 BW],
  [WITH_AVX_512_BW_OR_DIE],
  [avx-512-bw-or-die],
  [no],
  [demand the use of AVX-512 BW],
  [defer to --with-avx-512-bw])[

case $WITH_AVX_512_BW_OR_DIE,$HAVE_AVX_512_BW in
  1,0)
    ]GATBPS_MSG_ERROR([
      You specified --with-avx-512-bw-or-die, but AVX-512 BW is not available.
    ])[
  ;;
esac

}]])
