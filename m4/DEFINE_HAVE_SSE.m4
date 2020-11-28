dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN_ONCE([DEFINE_HAVE_SSE], [[{

]AC_REQUIRE([DEFINE_HAVE_CFLAG_MSSE])[
]AC_REQUIRE([DEFINE_WITH_SSE])[
]GATBPS_SOFT_REQUIRE([[DEFINE_HAVE_CXXFLAG_MSSE]])[

]GATBPS_CHECK_VARS(
  [SSE],
  [HAVE_SSE],
  [
    HAVE_CFLAG_MSSE
    WITH_SSE
    ]GATBPS_SOFT_VAR_DEP([[HAVE_CXXFLAG_MSSE]])[
  ])[

]GATBPS_ARG_WITH_BOOL(
  [insistence to use SSE],
  [WITH_SSE_OR_DIE],
  [sse-or-die],
  [no],
  [demand the use of SSE],
  [defer to --with-sse])[

case $WITH_SSE_OR_DIE,$HAVE_SSE in
  1,0)
    ]GATBPS_MSG_ERROR([
      You specified --with-sse-or-die, but SSE is not available.
    ])[
  ;;
esac

:;}]])
