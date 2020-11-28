dnl
dnl For the copyright information for this file, please search up the
dnl directory tree for the first COPYING file.
dnl

AC_DEFUN_ONCE([DEFINE_WITH_BUILD_GROUPS], [[{

]GATBPS_ARG_WITH(
  [build-groups],
  [],
  [yes])[

. "$srcdir"/src/sh/fragments/with_build_groups.sh
case $with_build_groups_error in
  sed_failed)
    exit $with_build_groups_error_sed_status
  ;;
  invalid_entry)
    ]GATBPS_MSG_ERROR([
      unknown --with-build-groups entry:
      $with_build_groups_error_invalid_entry
    ])[
  ;;
  ?*)
    exit 1
  ;;
esac

]GATBPS_CHECK_VARS(
  [--with-build-groups += c-autotools],
  [WITH_BUILD_GROUP_C_AUTOTOOLS],
  [WITH_BUILD_GROUP_C_AUTOTOOLS])[

]GATBPS_CHECK_VARS(
  [--with-build-groups += cpp-autotools],
  [WITH_BUILD_GROUP_CPP_AUTOTOOLS],
  [WITH_BUILD_GROUP_CPP_AUTOTOOLS])[

]GATBPS_CHECK_VARS(
  [--with-build-groups += java-gatbps],
  [WITH_BUILD_GROUP_JAVA_GATBPS],
  [WITH_BUILD_GROUP_JAVA_GATBPS])[

]GATBPS_CHECK_VARS(
  [--with-build-groups += java-maven],
  [WITH_BUILD_GROUP_JAVA_MAVEN],
  [WITH_BUILD_GROUP_JAVA_MAVEN])[

:;}]])
