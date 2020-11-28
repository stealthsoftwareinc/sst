dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_HAVE_POSIX], [[{ :

]AC_REQUIRE([DEFINE_CFLAGS])[
]AC_REQUIRE([DEFINE_CPPFLAGS])[
]AC_REQUIRE([DEFINE_WITH_POSIX])[
]AC_REQUIRE([DEFINE_WITH_POSIX_OR_DIE])[

]AC_LANG_PUSH([C])[
]GATBPS_CHECK_COMPILE(
  [POSIX],
  [HAVE_POSIX],
  [[
    #define _POSIX_C_SOURCE 200112L
    #include <unistd.h>
  ]],
  [[
    #if _POSIX_VERSION < 200112L
    #include <cause_a_compilation_error>
    #endif
  ]],
  [
    WITH_POSIX
  ])[
]AC_LANG_POP([C])[

case $][HAVE_POSIX$][WITH_POSIX_OR_DIE in
  01)
    ]GATBPS_MSG_ERROR([
      --with-posix-or-die triggered
    ])[
  ;;
esac

};]])
