dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_HAVE_NETTLE_CRYPT_FUNC], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_HAVE_NETTLE_CRYPT_FUNC macro.
#]dnl
m4_ifdef(
  [DEFINE_HAVE_NETTLE_CRYPT_FUNC_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_HAVE_NETTLE_CRYPT_FUNC has already been called
  ])],
  [m4_define([DEFINE_HAVE_NETTLE_CRYPT_FUNC_HAS_BEEN_CALLED])])[]dnl
m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_HAVE_NETTLE_CRYPT_FUNC requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[]dnl

AC_REQUIRE([DEFINE_WITH_NETTLE])

AC_REQUIRE([DEFINE_HAVE_NETTLE_CRYPT_FUNC_SIZE_T])
AC_REQUIRE([DEFINE_HAVE_NETTLE_CRYPT_FUNC_UNSIGNED_INT])

h1=""
h1="$[]{h1}$[]{HAVE_NETTLE_CRYPT_FUNC_SIZE_T}"
h1="$[]{h1}$[]{HAVE_NETTLE_CRYPT_FUNC_UNSIGNED_INT}"

case "$[]{h1}" in
  *'1'*)
    h1='1'
  ;;
  *)
    h1='0'
  ;;
esac

GATBPS_CHECK_VARS(
  [nettle_crypt_func],
  [HAVE_NETTLE_CRYPT_FUNC],
  [
    WITH_NETTLE
    h1
  ])

:;}])[]dnl
