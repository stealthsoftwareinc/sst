dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN_ONCE([DEFINE_HAVE_LIB_CRYPTO], [[{

]AC_BEFORE([$0], [DEFINE_LIBS])[

]dnl begin_prerequisites
[

]AC_REQUIRE([DEFINE_CFLAGS])[
]AC_REQUIRE([DEFINE_CPPFLAGS])[
]GATBPS_SOFT_REQUIRE([[DEFINE_WITH_OPENSSL_CRYPTO]])[

]dnl end_prerequisites
[

old_LIBS=$LIBS

LIBS="-lcrypto $LIBS"

]AC_LANG_PUSH([C])[
]GATBPS_CHECK_LINK(
  [-lcrypto],
  [HAVE_LIB_CRYPTO],
  [[
    #include <openssl/bn.h>
  ]],
  [[
    (void)BN_new();
  ]],
  [
    ]GATBPS_SOFT_VAR_DEP([[WITH_OPENSSL_CRYPTO]])[
  ])[
]AC_LANG_POP([C])[

case $HAVE_LIB_CRYPTO in
  0)
    LIBS=$old_LIBS
  ;;
esac

:;}]])
