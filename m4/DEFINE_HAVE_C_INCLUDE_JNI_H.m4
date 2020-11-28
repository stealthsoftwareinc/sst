dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN_ONCE([DEFINE_HAVE_C_INCLUDE_JNI_H], [[{

]AC_REQUIRE([DEFINE_CFLAGS])[
]AC_REQUIRE([DEFINE_CPPFLAGS])[

]AC_LANG_PUSH([C])[
]GATBPS_CHECK_HEADER(
  [#include <jni.h> (C)],
  [HAVE_C_INCLUDE_JNI_H],
  [[#include <jni.h>]])[
]AC_LANG_POP([C])[

:;}]])
