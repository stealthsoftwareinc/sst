dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN_ONCE([DEFINE_HAVE_LIB_HOGWEED], [[{

]AC_BEFORE([$0], [DEFINE_LIBS])[

]dnl begin_prerequisites
[

]AC_REQUIRE([DEFINE_CFLAGS])[
]AC_REQUIRE([DEFINE_CPPFLAGS])[
]AC_REQUIRE([DEFINE_HAVE_LIB_GMP])[
]AC_REQUIRE([DEFINE_HAVE_LIB_NETTLE])[
]GATBPS_SOFT_REQUIRE([[DEFINE_WITH_NETTLE]])[

]dnl end_prerequisites
[

old_LIBS=$LIBS

LIBS="-lhogweed $LIBS"

]AC_LANG_PUSH([C])[
]GATBPS_CHECK_LINK(
  [-lhogweed],
  [HAVE_LIB_HOGWEED],
  [[
    #include <nettle/rsa.h>
  ]],
  [[
    struct rsa_public_key pub;
    rsa_public_key_init(&pub);
  ]],
  [
    HAVE_LIB_GMP
    HAVE_LIB_NETTLE
    ]GATBPS_SOFT_VAR_DEP([[WITH_NETTLE]])[
  ])[
]AC_LANG_POP([C])[

case $HAVE_LIB_HOGWEED in
  0)
    LIBS=$old_LIBS
  ;;
esac

:;}]])
