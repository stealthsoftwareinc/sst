dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN_ONCE([DEFINE_HAVE_LIB_SSL], [[{

]AC_BEFORE([$0], [DEFINE_LIBS])[

]dnl begin_prerequisites
[

]AC_REQUIRE([DEFINE_CFLAGS])[
]AC_REQUIRE([DEFINE_CPPFLAGS])[
]AC_REQUIRE([DEFINE_HAVE_LIB_CRYPTO])[

]dnl end_prerequisites
[

old_LIBS=$LIBS

LIBS="-lssl $LIBS"

]AC_LANG_PUSH([C])[
]GATBPS_CHECK_LINK(
  [-lssl],
  [HAVE_LIB_SSL],
  [[
    #include <openssl/ssl.h>
  ]],
  [[
    (void)SSL_CTX_new(SSLv23_method());
  ]],
  [
    HAVE_LIB_CRYPTO
  ])[
]AC_LANG_POP([C])[

case $HAVE_LIB_SSL in
  0)
    LIBS=$old_LIBS
  ;;
esac

:;}]])
