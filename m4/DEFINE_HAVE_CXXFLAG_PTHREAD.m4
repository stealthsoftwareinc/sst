dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN_ONCE([DEFINE_HAVE_CXXFLAG_PTHREAD], [[{

]AC_BEFORE([$0], [DEFINE_CXXFLAGS])[

]GATBPS_CHECK_CXXFLAG(
  [CXXFLAGS += -pthread],
  [HAVE_CXXFLAG_PTHREAD],
  [-pthread])[

case $HAVE_CXXFLAG_PTHREAD in
  1)
    CXXFLAGS="$CXXFLAGS -pthread"
  ;;
esac

:;}]])
