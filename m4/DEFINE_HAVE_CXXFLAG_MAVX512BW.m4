dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN_ONCE([DEFINE_HAVE_CXXFLAG_MAVX512BW], [[{ :

]AC_BEFORE([$0], [DEFINE_CXXFLAGS])[

]AC_REQUIRE([DEFINE_HAVE_CFLAG_MAVX512BW])[
]GATBPS_SOFT_REQUIRE([[DEFINE_HAVE_CXXFLAG_MAVX512F]])[
]GATBPS_SOFT_REQUIRE([[DEFINE_WITH_AVX_512_BW]])[
]GATBPS_SOFT_REQUIRE([[DEFINE_WITH_AVX_512_F]])[

]GATBPS_CHECK_CXXFLAG(
  [CXXFLAGS += -mavx512bw (compile 1)],
  [HAVE_CXXFLAG_MAVX512BW_COMPILE_1],
  [-mavx512bw],
  [
    ]GATBPS_SOFT_VAR_DEP([[HAVE_CXXFLAG_MAVX512F]])[
    ]GATBPS_SOFT_VAR_DEP([[WITH_AVX_512_BW]])[
    ]GATBPS_SOFT_VAR_DEP([[WITH_AVX_512_F]])[
  ])[

old_CXXFLAGS=$CXXFLAGS

CXXFLAGS="$CXXFLAGS -mavx512bw"

]AC_LANG_PUSH([C++])[
]GATBPS_CHECK_COMPILE(
  [CXXFLAGS += -mavx512bw (compile 2)],
  [HAVE_CXXFLAG_MAVX512BW_COMPILE_2],
  HAVE_CFLAG_MAVX512BW_PROLOGUE,
  HAVE_CFLAG_MAVX512BW_BODY,
  [
    HAVE_CXXFLAG_MAVX512BW_COMPILE_1
  ])[
]AC_LANG_POP([C++])[

]GATBPS_ARG_WITH_BOOL(
  [CXXFLAGS += -mavx512bw (cross)],
  [WITH_CROSS_CXXFLAG_MAVX512BW],
  [cross-cxxflag-mavx512bw],
  [no],
  [assume that CXXFLAGS += -mavx512bw is available on the host system when cross compiling],
  [assume that CXXFLAGS += -mavx512bw is unavailable on the host system when cross compiling])[

]AC_LANG_PUSH([C++])[
]GATBPS_CHECK_RUN(
  [CXXFLAGS += -mavx512bw (run)],
  [HAVE_CXXFLAG_MAVX512BW],
  HAVE_CFLAG_MAVX512BW_PROLOGUE,
  HAVE_CFLAG_MAVX512BW_BODY,
  [gatbps_cv_WITH_CROSS_CXXFLAG_MAVX512BW],
  [
    HAVE_CXXFLAG_MAVX512BW_COMPILE_2
  ])[
]AC_LANG_POP([C++])[

case $HAVE_CXXFLAG_MAVX512BW in
  0)
    CXXFLAGS=$old_CXXFLAGS
  ;;
esac

}]])
