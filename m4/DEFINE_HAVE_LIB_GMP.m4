dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN_ONCE([DEFINE_HAVE_LIB_GMP], [[{

]AC_BEFORE([$0], [DEFINE_LIBS])[

]dnl begin_prerequisites
[

]AC_REQUIRE([DEFINE_CFLAGS])[
]AC_REQUIRE([DEFINE_CPPFLAGS])[
]GATBPS_SOFT_REQUIRE([[DEFINE_WITH_GMP]])[

]dnl end_prerequisites
[

old_LIBS=$LIBS

LIBS="-lgmp $LIBS"

]AC_LANG_PUSH([C])[
]GATBPS_CHECK_LINK(
  [-lgmp],
  [HAVE_LIB_GMP],
  [[
    #include <gmp.h>
  ]],
  [[
    mpz_t x;
    mpz_init(x);
  ]],
  [
    ]GATBPS_SOFT_VAR_DEP([[WITH_GMP]])[
  ])[
]AC_LANG_POP([C])[

case $HAVE_LIB_GMP in
  0)
    LIBS=$old_LIBS
  ;;
esac

:;}]])
