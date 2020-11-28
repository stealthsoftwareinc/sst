dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN_ONCE([DEFINE_HAVE_CXXFLAG_MSSE], [[{

]AC_BEFORE([$0], [DEFINE_CXXFLAGS])[

]GATBPS_SOFT_REQUIRE([[DEFINE_WITH_SSE]])[

]GATBPS_CHECK_CXXFLAG(
  [CXXFLAGS += -msse (compile 1)],
  [HAVE_CXXFLAG_MSSE_COMPILE_1],
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

old_CXXFLAGS=$CXXFLAGS

CXXFLAGS="$CXXFLAGS -msse"

]AC_LANG_PUSH([C++])[
]GATBPS_CHECK_COMPILE(
  [CXXFLAGS += -msse (compile 2)],
  [HAVE_CXXFLAG_MSSE_COMPILE_2],
  prologue,
  body,
  [
    HAVE_CXXFLAG_MSSE_COMPILE_1
  ])[
]AC_LANG_POP([C++])[

]GATBPS_ARG_WITH_BOOL(
  [CXXFLAGS += -msse (cross)],
  [WITH_CROSS_CXXFLAG_MSSE],
  [cross-cxxflag-msse],
  [no],
  [assume that CXXFLAGS += -msse is available on the host system when cross compiling],
  [assume that CXXFLAGS += -msse is unavailable on the host system when cross compiling])[

]AC_LANG_PUSH([C++])[
]GATBPS_CHECK_RUN(
  [CXXFLAGS += -msse (run)],
  [HAVE_CXXFLAG_MSSE],
  prologue,
  body,
  [gatbps_cv_WITH_CROSS_CXXFLAG_MSSE],
  [
    HAVE_CXXFLAG_MSSE_COMPILE_2
  ])[
]AC_LANG_POP([C++])[

case $HAVE_CXXFLAG_MSSE in
  0)
    CXXFLAGS=$old_CXXFLAGS
  ;;
esac

]m4_popdef([body])[
]m4_popdef([prologue])[

:;}]])
