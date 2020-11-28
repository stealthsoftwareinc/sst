dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl
[

]AC_INIT(
  [[SST Code Generation]],
  m4_esyscmd_s([
    'cd' '..' && 'sh' '-' 'build-aux/VERSION.sh'
  ])m4_if(m4_sysval, [0], [], [m4_fatal([VERSION.sh failed])]),
  [[]],
  [[sst-gen]],
  [[]])[

'.' "${srcdir}"'/../build-aux/gen-configure.sh'

]AC_COPYRIGHT(
[[Some parts of this file are from the SST package.

The following copyright notice is generally applicable:

     Copyright (C) Stealth Software Technologies, Inc.

The full copyright information depends on the distribution
of the package. For more information, see the COPYING file.
However, depending on the context in which you are viewing
this file, the COPYING file may not be available.
]])[

]AC_CONFIG_AUX_DIR([../build-aux])[
]AC_CONFIG_MACRO_DIR([../m4])[
]AC_CONFIG_MACRO_DIRS([../m4])[
]AC_CONFIG_SRCDIR([../doc/sst.texi])[

]AM_INIT_AUTOMAKE([
  -Wall
  foreign
  nostdinc
  subdir-objects
  tar-ustar
])[

]AC_PROG_CC[
]AC_PROG_RANLIB[
]AM_PROG_AR[

]dnl begin_includes
[

]m4_include([bin/sst_status_map_generator.ac])[
]m4_include([include/src/sst_status_map.inc.ac])[

]dnl end_includes
[

]AC_CONFIG_FILES([Makefile])[

]AC_OUTPUT[

]
