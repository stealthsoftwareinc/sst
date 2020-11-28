dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN_ONCE([DEFINE_HAVE_CFLAG_PTHREAD], [[{

]AC_BEFORE([$0], [DEFINE_CFLAGS])[

]GATBPS_CHECK_CFLAG(
  [CFLAGS += -pthread],
  [HAVE_CFLAG_PTHREAD],
  [-pthread])[

case $HAVE_CFLAG_PTHREAD in
  1)
    CFLAGS="$CFLAGS -pthread"
  ;;
esac

:;}]])
