#
# Copyright (C) 2012-2024 Stealth Software Technologies, Inc.
#
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without
# restriction, including without limitation the rights to use,
# copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following
# conditions:
#
# The above copyright notice and this permission notice (including
# the next paragraph) shall be included in all copies or
# substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
# OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.
#
# SPDX-License-Identifier: MIT
#

#
# This portable shell fragment parses $with_build_groups into
# $WITH_BUILD_GROUP_*. $with_build_groups should usually already be set
# to the user-provided --with-build-groups value. If $with_build_groups
# is unset, it will be implicitly taken to be "default".
#
# $with_build_groups_values will be set and exported such that it can be
# given to the eval command to restore the resulting $WITH_BUILD_GROUP_*
# variables. This will also set $with_build_groups_option to be a
# --with-build-groups option that will parse to the same result.
#
# If the fragment succeeds, then $with_build_groups_error will be set to
# the empty string. Otherwise, $with_build_groups_error will be set to a
# nonempty string indicating the type of error.
#
# If $with_build_groups_error is sed_failed, then the fragment failed
# because a sed command failed, and the exit status of the failed sed
# command is stored in $with_build_groups_error_sed_status.
#
# If $with_build_groups_error is invalid_entry, then the fragment failed
# because the user provided an invalid --with-build-groups entry, which
# is stored in $with_build_groups_error_invalid_entry.
#
# Other errors may be possible, so you should always check for success
# by checking that $with_build_groups_error is empty.
#

with_build_groups_error=
with_build_groups_option=

with_build_groups_entries=`sed "s/,/ /g" <<EOF
${with_build_groups-default}
EOF
` || {
  with_build_groups_error_sed_status=$?
  with_build_groups_error=sed_failed
}

case $with_build_groups_error in
  "")
    for with_build_groups_entry in no $with_build_groups_entries; do

      case $with_build_groups_entry in

        no)
          WITH_BUILD_GROUP_BASH=0
          WITH_BUILD_GROUP_C_AUTOTOOLS=0
          WITH_BUILD_GROUP_CPP_AUTOTOOLS=0
          WITH_BUILD_GROUP_JAVA_GATBPS=0
          WITH_BUILD_GROUP_JAVA_MAVEN=0
        ;;

        +default | default | yes)
          WITH_BUILD_GROUP_BASH=1
          WITH_BUILD_GROUP_C_AUTOTOOLS=1
          WITH_BUILD_GROUP_CPP_AUTOTOOLS=1
          WITH_BUILD_GROUP_JAVA_GATBPS=1
        ;;
        -default)
          WITH_BUILD_GROUP_BASH=0
          WITH_BUILD_GROUP_C_AUTOTOOLS=0
          WITH_BUILD_GROUP_CPP_AUTOTOOLS=0
          WITH_BUILD_GROUP_JAVA_GATBPS=0
          WITH_BUILD_GROUP_JAVA_MAVEN=0
        ;;

        +bash | bash)
          WITH_BUILD_GROUP_BASH=1
        ;;
        -bash)
          WITH_BUILD_GROUP_BASH=0
        ;;

        +c | c)
          WITH_BUILD_GROUP_C_AUTOTOOLS=1
        ;;
        -c)
          WITH_BUILD_GROUP_C_AUTOTOOLS=0
          WITH_BUILD_GROUP_CPP_AUTOTOOLS=0
        ;;

        +c-autotools | c-autotools)
          WITH_BUILD_GROUP_C_AUTOTOOLS=1
        ;;
        -c-autotools)
          WITH_BUILD_GROUP_C_AUTOTOOLS=0
          WITH_BUILD_GROUP_CPP_AUTOTOOLS=0
        ;;

        +cpp | cpp)
          WITH_BUILD_GROUP_C_AUTOTOOLS=1
          WITH_BUILD_GROUP_CPP_AUTOTOOLS=1
        ;;
        -cpp)
          WITH_BUILD_GROUP_CPP_AUTOTOOLS=0
        ;;

        +cpp-autotools | cpp-autotools)
          WITH_BUILD_GROUP_C_AUTOTOOLS=1
          WITH_BUILD_GROUP_CPP_AUTOTOOLS=1
        ;;
        -cpp-autotools)
          WITH_BUILD_GROUP_CPP_AUTOTOOLS=0
        ;;

        +java | java)
          WITH_BUILD_GROUP_JAVA_GATBPS=1
        ;;
        -java)
          WITH_BUILD_GROUP_JAVA_GATBPS=0
          WITH_BUILD_GROUP_JAVA_MAVEN=0
        ;;

        +java-gatbps | java-gatbps)
          WITH_BUILD_GROUP_JAVA_GATBPS=1
        ;;
        -java-gatbps)
          WITH_BUILD_GROUP_JAVA_GATBPS=0
        ;;

        +java-maven | java-maven)
          WITH_BUILD_GROUP_JAVA_MAVEN=1
        ;;
        -java-maven)
          WITH_BUILD_GROUP_JAVA_MAVEN=0
        ;;

        *)
          with_build_groups_error=invalid_entry
          with_build_groups_error_invalid_entry=$with_build_groups_entry
          break
        ;;

      esac

      case $with_build_groups_option in
        "")
          with_build_groups_option=--with-build-groups=$with_build_groups_entry
        ;;
        *)
          with_build_groups_option=$with_build_groups_option,$with_build_groups_entry
        ;;
      esac

    done
  ;;
esac

export with_build_groups_values="

WITH_BUILD_GROUP_BASH=$WITH_BUILD_GROUP_BASH
WITH_BUILD_GROUP_C_AUTOTOOLS=$WITH_BUILD_GROUP_C_AUTOTOOLS
WITH_BUILD_GROUP_CPP_AUTOTOOLS=$WITH_BUILD_GROUP_CPP_AUTOTOOLS
WITH_BUILD_GROUP_JAVA_GATBPS=$WITH_BUILD_GROUP_JAVA_GATBPS
WITH_BUILD_GROUP_JAVA_MAVEN=$WITH_BUILD_GROUP_JAVA_MAVEN

with_build_groups_option=$with_build_groups_option

"
