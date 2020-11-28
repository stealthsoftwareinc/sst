dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN_ONCE([DEFINE_HAVE_X86_64], [[{ :

]AC_REQUIRE([DEFINE_HAVE_X86_64_C])[
]GATBPS_SOFT_REQUIRE([[DEFINE_HAVE_X86]])[
]GATBPS_SOFT_REQUIRE([[DEFINE_HAVE_X86_64_CPP]])[
]GATBPS_SOFT_REQUIRE([[DEFINE_WITH_X86_64]])[

]GATBPS_CHECK_VARS(
  [x86_64 CPU features],
  [HAVE_X86_64],
  [
    HAVE_X86_64_C
    ]GATBPS_SOFT_VAR_DEP([[HAVE_X86]])[
    ]GATBPS_SOFT_VAR_DEP([[HAVE_X86_64_CPP]])[
    ]GATBPS_SOFT_VAR_DEP([[WITH_X86_64]])[
  ])[

]GATBPS_ARG_WITH_BOOL(
  [insistence to use x86_64 CPU features],
  [WITH_X86_64_OR_DIE],
  [x86-64-or-die],
  [no],
  [demand the use of x86_64 CPU features],
  [defer to --with-x86-64])[

case $WITH_X86_64_OR_DIE,$HAVE_X86_64 in
  1,0)
    ]GATBPS_MSG_ERROR([
      You specified --with-x86-64-or-die, but x86_64 CPU features are
      not available.
    ])[
  ;;
esac

}]])
