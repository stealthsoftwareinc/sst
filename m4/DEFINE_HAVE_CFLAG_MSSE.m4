dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN_ONCE([DEFINE_HAVE_CFLAG_MSSE], [[{

]AC_BEFORE([$0], [DEFINE_CFLAGS])[

]GATBPS_SOFT_REQUIRE([[DEFINE_WITH_SSE]])[

]GATBPS_CHECK_CFLAG(
  [CFLAGS += -msse (compile 1)],
  [HAVE_CFLAG_MSSE_COMPILE_1],
  [-msse],
  [
    ]GATBPS_SOFT_VAR_DEP([[WITH_SSE]])[
  ])[

]m4_pushdef(
  [prologue],
  [[[
    #include <xmmintrin.h>
  ]]])[

]m4_pushdef(
  [body],
  [[[
    _mm_sfence();
  ]]])[

old_CFLAGS=$CFLAGS

CFLAGS="$CFLAGS -msse"

]AC_LANG_PUSH([C])[
]GATBPS_CHECK_COMPILE(
  [CFLAGS += -msse (compile 2)],
  [HAVE_CFLAG_MSSE_COMPILE_2],
  prologue,
  body,
  [
    HAVE_CFLAG_MSSE_COMPILE_1
  ])[
]AC_LANG_POP([C])[

]GATBPS_ARG_WITH_BOOL(
  [CFLAGS += -msse (cross)],
  [WITH_CROSS_CFLAG_MSSE],
  [cross-cflag-msse],
  [no],
  [assume that CFLAGS += -msse is available on the host system when cross compiling],
  [assume that CFLAGS += -msse is unavailable on the host system when cross compiling])[

]AC_LANG_PUSH([C])[
]GATBPS_CHECK_RUN(
  [CFLAGS += -msse (run)],
  [HAVE_CFLAG_MSSE],
  prologue,
  body,
  [gatbps_cv_WITH_CROSS_CFLAG_MSSE],
  [
    HAVE_CFLAG_MSSE_COMPILE_2
  ])[
]AC_LANG_POP([C])[

case $HAVE_CFLAG_MSSE in
  0)
    CFLAGS=$old_CFLAGS
  ;;
esac

]m4_popdef([body])[
]m4_popdef([prologue])[

:;}]])
