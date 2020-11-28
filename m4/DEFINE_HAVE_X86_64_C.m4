dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN_ONCE([DEFINE_HAVE_X86_64_C], [[{ :

]GATBPS_SOFT_REQUIRE([[DEFINE_WITH_X86_64]])[

]m4_define(
  [HAVE_X86_64_C_PROLOGUE],
  [[[
  ]]])[

]m4_define(
  [HAVE_X86_64_C_BODY],
  [[[

    /*
     * See <https://sourceforge.net/p/predef/wiki/Architectures/>.
     */

    #if !(0 \
      || defined(_M_AMD64) \
      || defined(_M_X64) \
      || defined(__amd64) \
      || defined(__amd64__) \
      || defined(__x86_64) \
      || defined(__x86_64__) \
    )

      #include <cause_a_compilation_error>

    #endif

  ]]])[

]AC_LANG_PUSH([C])[
]GATBPS_CHECK_COMPILE(
  [x86_64 (C)],
  [HAVE_X86_64_C],
  HAVE_X86_64_C_PROLOGUE,
  HAVE_X86_64_C_BODY,
  [
    ]GATBPS_SOFT_VAR_DEP([[WITH_X86_64]])[
  ])[
]AC_LANG_POP([C])[

}]])
