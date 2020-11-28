dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

[

]AC_INIT(
  [[SST]],
  m4_esyscmd_s([
    sh build-aux/VERSION.sh
  ])m4_if(m4_sysval, [0], [], [m4_fatal([VERSION.sh failed])]),
  [[sst@stealthsoftwareinc.com]],
  [[sst]])[

]m4_include([build-aux/prelude.ac])[

]gatbps_check_macros[ || exit

]GATBPS_DEFINE_VERSION(
  [AC_],
  [PACKAGE_VERSION])[

]GATBPS_DEFINE_DATE(
  [AC_],
  [PACKAGE_DATE],
  m4_esyscmd_s([
    sh build-aux/DATE.sh
  ])m4_if(m4_sysval, [0], [], [m4_fatal([DATE.sh failed])]))[

]AC_COPYRIGHT(
[[Some parts of this file are from the SST package.

The following copyright notice is generally applicable:

     Copyright (C) Stealth Software Technologies, Inc.

The full copyright information depends on the distribution
of the package. For more information, see the COPYING file.
However, depending on the context in which you are viewing
this file, the COPYING file may not be available.
]])[

]AC_CONFIG_AUX_DIR([build-aux])[
]AC_CONFIG_MACRO_DIR([m4])[
]AC_CONFIG_MACRO_DIRS([m4])[
]AC_CONFIG_SRCDIR([doc/sst.texi])[

]AM_INIT_AUTOMAKE([
  -Wall
  foreign
  nostdinc
  subdir-objects
  tar-ustar
])[

]m4_include([build-aux/autogen.ac])[

]LT_INIT([
  win32-dll
])[

]
AC_CHECK_HEADERS_ONCE([pthread.h])
AC_CHECK_HEADERS_ONCE([windows.h])
[

]dnl begin_includes
[

]m4_include([bin/sst_status_map_generator.ac])[
]m4_include([include/src/sst_status_map.inc.ac])[
]m4_include([rpm/centos-7/x86_64/rpm.ac])[
]m4_include([rpm/rhel-7/x86_64/rpm.ac])[
]m4_include([src/com/stealthsoftwareinc/sst/BuildConfig.java.ac])[
]m4_include([src/com/stealthsoftwareinc/sst/BuildConfig.java.im.ac])[

]dnl end_includes
[
]

GATBPS_CHECK_LINK(
  [CONF_modules_free],
  [HAVE_CONF_MODULES_FREE],
  [[
    #include <openssl/conf.h>
  ]],
  [[
    CONF_modules_free();
  ]]
)

GATBPS_CHECK_LINK(
  [CRYPTO_LOCK],
  [HAVE_CRYPTO_LOCK],
  [[
    #include <openssl/crypto.h>
  ]],
  [[
    int x1 = CRYPTO_LOCK;
    (void)x1;
  ]]
)

GATBPS_CHECK_LINK(
  [CRYPTO_set_add_lock_callback],
  [HAVE_CRYPTO_SET_ADD_LOCK_CALLBACK],
  [[
    #include <openssl/crypto.h>
  ]],
  [[
    CRYPTO_set_add_lock_callback(
      (int (*)(
        int *,
        int,
        int,
        char const *,
        int
      ))0
    );
  ]]
)

GATBPS_CHECK_LINK(
  [CRYPTO_set_dynlock_create_callback],
  [HAVE_CRYPTO_SET_DYNLOCK_CREATE_CALLBACK],
  [[
    #include <openssl/crypto.h>
  ]],
  [[
    CRYPTO_set_dynlock_create_callback(
      (struct CRYPTO_dynlock_value * (*)(
        char const *,
        int
      ))0
    );
  ]]
)

GATBPS_CHECK_LINK(
  [CRYPTO_set_dynlock_destroy_callback],
  [HAVE_CRYPTO_SET_DYNLOCK_DESTROY_CALLBACK],
  [[
    #include <openssl/crypto.h>
  ]],
  [[
    CRYPTO_set_dynlock_destroy_callback(
      (void (*)(
        struct CRYPTO_dynlock_value *,
        char const *,
        int
      ))0
    );
  ]]
)

GATBPS_CHECK_LINK(
  [CRYPTO_set_dynlock_lock_callback],
  [HAVE_CRYPTO_SET_DYNLOCK_LOCK_CALLBACK],
  [[
    #include <openssl/crypto.h>
  ]],
  [[
    CRYPTO_set_dynlock_lock_callback(
      (void (*)(
        int,
        struct CRYPTO_dynlock_value *,
        char const *,
        int
      ))0
    );
  ]]
)

GATBPS_CHECK_LINK(
  [CRYPTO_set_locking_callback],
  [HAVE_CRYPTO_SET_LOCKING_CALLBACK],
  [[
    #include <openssl/crypto.h>
  ]],
  [[
    CRYPTO_set_locking_callback(
      (void (*)(
        int,
        int,
        char const *,
        int
      ))0
    );
  ]]
)

GATBPS_CHECK_LINK(
  [ERR_free_strings],
  [HAVE_ERR_FREE_STRINGS],
  [[
    #include <openssl/err.h>
  ]],
  [[
    ERR_free_strings();
  ]]
)

GATBPS_CHECK_LINK(
  [ERR_load_crypto_strings],
  [HAVE_ERR_LOAD_CRYPTO_STRINGS],
  [[
    #include <openssl/err.h>
  ]],
  [[
    ERR_load_crypto_strings();
  ]]
)

GATBPS_CHECK_LINK(
  [EVP_cleanup],
  [HAVE_EVP_CLEANUP],
  [[
    #include <openssl/evp.h>
  ]],
  [[
    EVP_cleanup();
  ]]
)

GATBPS_CHECK_LINK(
  [OPENSSL_config],
  [HAVE_OPENSSL_CONFIG],
  [[
    #include <openssl/conf.h>
  ]],
  [[
    OPENSSL_config(
      (char const *)0
    );
  ]]
)

GATBPS_CHECK_LINK(
  [OpenSSL_add_all_algorithms],
  [HAVE_OPENSSL_ADD_ALL_ALGORITHMS],
  [[
    #include <openssl/evp.h>
  ]],
  [[
    OpenSSL_add_all_algorithms();
  ]]
)

AC_ARG_ENABLE(
  [mutex],
  [
AS_HELP_STRING([--disable-mutex],
               [equivalent to --enable-mutex=no])
AS_HELP_STRING([--enable-mutex],
               [equivalent to --enable-mutex=yes (default)])
AS_HELP_STRING([--enable-mutex=no],
               [use the null mutex implementation])
AS_HELP_STRING([--enable-mutex=yes],
               [use the inferred mutex implementation])
AS_HELP_STRING([--enable-mutex=posix],
               [use the POSIX mutex implementation])
AS_HELP_STRING([--enable-mutex=windows],
               [use the Windows mutex implementation])],
  [],
  [
    enable_mutex='yes'
  ]
)

case "${enable_mutex}" in
  'no')
    :
  ;;
  'posix')
    case "${ac_cv_header_pthread_h}" in
      'no')
        AC_MSG_ERROR([--enable-mutex=posix requires pthread.h], [1])
      ;;
    esac
  ;;
  'windows')
    case "${ac_cv_header_windows_h}" in
      'no')
        AC_MSG_ERROR([--enable-mutex=windows requires windows.h], [1])
      ;;
    esac
  ;;
  'yes')
    case "${ac_cv_header_pthread_h},${ac_cv_header_windows_h}" in
      'yes,'*)
        enable_mutex='posix'
      ;;
      'no,yes')
        enable_mutex='windows'
      ;;
      *)
        enable_mutex='no'
      ;;
    esac
  ;;
  *)
    AC_MSG_ERROR([invalid --enable-mutex value], [1])
  ;;
esac

case "${enable_mutex}" in
  'no')
    SST_MUTEX_IMP='SST_MUTEX_IMP_NULL'
  ;;
  'posix')
    SST_MUTEX_IMP='SST_MUTEX_IMP_POSIX'
  ;;
  'windows')
    SST_MUTEX_IMP='SST_MUTEX_IMP_WINDOWS'
  ;;
  *)
    AC_MSG_ERROR([the --enable-mutex code is broken], [1])
  ;;
esac

AC_SUBST([SST_MUTEX_IMP])

GATBPS_CONFIG_FILE([build-aux/INPUT_FILTER.sh])
GATBPS_CONFIG_FILE([build-aux/PACKAGE_STRING.df])
GATBPS_CONFIG_FILE([doc/dox/dox.df])
GATBPS_CONFIG_FILE([doc/texi/PACKAGEDATE.texi], [doc/texi/PACKAGEDATE.texi.in], [maintainer-clean])
GATBPS_CONFIG_FILE([doc/texi/PACKAGEVERSION.texi], [doc/texi/PACKAGEVERSION.texi.in], [maintainer-clean])
GATBPS_CONFIG_FILE([pom.xml])
GATBPS_CONFIG_FILE([sst-java/pom.xml])
GATBPS_CONFIG_FILE([sst-maven-parent/pom.xml])

[

]GATBPS_CONFIG_FILE_SUBST[
]GATBPS_CONFIG_LATER_SUBST[
]GATBPS_CP_SUBST[
]GATBPS_DOCKER_BUILD_SUBST[
]GATBPS_GIT_ARCHIVE_SUBST[
]GATBPS_GIT_BUNDLE_SUBST[
]GATBPS_GIT_CLONE_SUBST[
]GATBPS_JAVA_CLASS_SUBST[
]GATBPS_JAVA_SUBST[
]GATBPS_M4_SUBST[
]GATBPS_TAR_SUBST[
]GATBPS_WGET_SUBST[
]GATBPS_XZ_SUBST[

]AC_CONFIG_FILES([Makefile])[
]AC_CONFIG_HEADERS([src/c_cpp/lib/sst/config_private_raw.h])[

]AC_CONFIG_SUBDIRS([
  gen
])[

#
# Restore the normal Libtool behavior on systems that prefer to set
# `link_all_deplibs=no`, as this generally causes problems with our
# workflow. See <https://stackoverflow.com/q/11802727>.
#

link_all_deplibs=yes
link_all_deplibs_CXX=yes

#
#

]AC_OUTPUT[

]
