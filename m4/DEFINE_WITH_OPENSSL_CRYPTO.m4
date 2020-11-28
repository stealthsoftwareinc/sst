dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN_ONCE([DEFINE_WITH_OPENSSL_CRYPTO], [[{

]GATBPS_ARG_WITH_BOOL(
  [permission to use OpenSSL's -lcrypto],
  [WITH_OPENSSL_CRYPTO],
  [openssl-crypto],
  [yes],
  [permit the use of OpenSSL's -lcrypto],
  [forbid the use of OpenSSL's -lcrypto])[

:;}]])
