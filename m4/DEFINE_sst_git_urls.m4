dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN([DEFINE_sst_git_urls], [[{

#
# The block that contains this comment is the expansion of the
# DEFINE_sst_git_urls macro.
#

]m4_ifdef(
  [DEFINE_sst_git_urls_HAS_BEEN_CALLED],
  [gatbps_fatal([
    DEFINE_sst_git_urls has already been called
  ])],
  [m4_define([DEFINE_sst_git_urls_HAS_BEEN_CALLED])])[

]m4_if(
  m4_eval([$# != 0]),
  [1],
  [gatbps_fatal([
    DEFINE_sst_git_urls requires exactly 0 arguments
    ($# ]m4_if([$#], [1], [[was]], [[were]])[ given)
  ])])[

]m4_define(
  [sst_git_urls_default],
  [[ ]dnl
[$][(abs_srcdir)/../sst ]dnl
])[

case $][{sst_git_urls+is_set} in
  "")
    sst_git_urls=']sst_git_urls_default['
  ;;
esac
readonly sst_git_urls

]AC_ARG_VAR(
  [sst_git_urls],
  [
    the URLs from which to fetch the SST Git repository (default:
    sst_git_urls=']sst_git_urls_default[')
  ])[

:;}]])[]dnl
