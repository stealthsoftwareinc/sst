dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN_ONCE([DEFINE_HAVE_CFLAG_MAVX512BW], [[{ :

]AC_BEFORE([$0], [DEFINE_CFLAGS])[

]GATBPS_SOFT_REQUIRE([[DEFINE_HAVE_CFLAG_MAVX512F]])[
]GATBPS_SOFT_REQUIRE([[DEFINE_WITH_AVX_512_BW]])[
]GATBPS_SOFT_REQUIRE([[DEFINE_WITH_AVX_512_F]])[

]GATBPS_CHECK_CFLAG(
  [CFLAGS += -mavx512bw (compile 1)],
  [HAVE_CFLAG_MAVX512BW_COMPILE_1],
  [-mavx512bw],
  [
    ]GATBPS_SOFT_VAR_DEP([[HAVE_CFLAG_MAVX512F]])[
    ]GATBPS_SOFT_VAR_DEP([[WITH_AVX_512_BW]])[
    ]GATBPS_SOFT_VAR_DEP([[WITH_AVX_512_F]])[
  ])[

]m4_define(
  [HAVE_CFLAG_MAVX512BW_PROLOGUE],
  [[[
    #include <immintrin.h>
  ]]])[

]m4_define(
  [HAVE_CFLAG_MAVX512BW_BODY],
  [[[
    (void)_mm512_abs_epi16(_mm512_setzero_si512());
  ]]])[

old_CFLAGS=$CFLAGS

CFLAGS="$CFLAGS -mavx512bw"

]AC_LANG_PUSH([C])[
]GATBPS_CHECK_COMPILE(
  [CFLAGS += -mavx512bw (compile 2)],
  [HAVE_CFLAG_MAVX512BW_COMPILE_2],
  HAVE_CFLAG_MAVX512BW_PROLOGUE,
  HAVE_CFLAG_MAVX512BW_BODY,
  [
    HAVE_CFLAG_MAVX512BW_COMPILE_1
  ])[
]AC_LANG_POP([C])[

]GATBPS_ARG_WITH_BOOL(
  [CFLAGS += -mavx512bw (cross)],
  [WITH_CROSS_CFLAG_MAVX512BW],
  [cross-cflag-mavx512bw],
  [no],
  [assume that CFLAGS += -mavx512bw is available on the host system when cross compiling],
  [assume that CFLAGS += -mavx512bw is unavailable on the host system when cross compiling])[

]AC_LANG_PUSH([C])[
]GATBPS_CHECK_RUN(
  [CFLAGS += -mavx512bw (run)],
  [HAVE_CFLAG_MAVX512BW],
  HAVE_CFLAG_MAVX512BW_PROLOGUE,
  HAVE_CFLAG_MAVX512BW_BODY,
  [gatbps_cv_WITH_CROSS_CFLAG_MAVX512BW],
  [
    HAVE_CFLAG_MAVX512BW_COMPILE_2
  ])[
]AC_LANG_POP([C])[

case $HAVE_CFLAG_MAVX512BW in
  0)
    CFLAGS=$old_CFLAGS
  ;;
esac

}]])
