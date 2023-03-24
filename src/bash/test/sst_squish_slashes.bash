#! /bin/sh -

#
# Copyright (C) 2012-2023 Stealth Software Technologies, Inc.
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
# This script uses the SST Bash library to bootstrap from /bin/sh into
# bash. See the Bash library > Bootstrapping section of the SST manual
# for more information.
#

readonly SST_BARF_STATUS=99

#-----------------------------------------------------------------------
# Include the SST Bash library
#-----------------------------------------------------------------------
#
# Include the first sst.bash file found by searching up the directory
# tree starting from the location of this script file. If no such file
# is found, fall back to including plain sst.bash with PATH resolution.
#
# This section is written in portable shell to ensure it works properly
# in any shell.
#

case ${SST_SEARCH_UP_X-} in '')
  case $0 in /*)
    SST_SEARCH_UP_X=$0
  ;; *)
    SST_SEARCH_UP_X=./$0
  esac
  SST_SEARCH_UP_R='\(.*/\)'
  SST_SEARCH_UP_X=`
    expr "x${SST_SEARCH_UP_X?}" : "x${SST_SEARCH_UP_R?}"
  `. || exit $?
  unset SST_SEARCH_UP_R
  SST_SEARCH_UP_X=`
    cd "${SST_SEARCH_UP_X?}" || exit $?
    while :; do
      if test -f sst.bash; then
        case ${PWD?} in *[!/]*)
          printf '%s\n' "${PWD?}"/ || exit $?
        ;; *)
          printf '%s\n' "${PWD?}" || exit $?
        esac
        exit
      fi
      case ${PWD?} in *[!/]*)
        cd ..
      ;; *)
        exit
      esac
    done
  ` || exit $?
  export SST_SEARCH_UP_X
esac
set -e || exit $?
. "${SST_SEARCH_UP_X?}"sst.bash
unset SST_SEARCH_UP_X

#-----------------------------------------------------------------------

go() {

  declare    q1
  declare    q2

  q1=$(sst_quote "$1")
  q2=$(sst_quote "$2")

  sst_test '
    x=$(sst_squish_slashes '"$q1"' | sst_csf);
    sst_csf x;
  ' '[[ "$x" == '"$q2"' ]]' '$x'

}; readonly -f go

#-----------------------------------------------------------------------

go '' ''
go '/ ' '/ '
go '/ /' '/ /'
go '/ //' '/ /'
go '/ ///' '/ /'
go '/' '/'
go '// ' '// '
go '// /' '// /'
go '// //' '// /'
go '// ///' '// /'
go '//' '//'
go '/// ' '/ '
go '/// /' '/ /'
go '/// //' '/ /'
go '/// ///' '/ /'
go '///' '/'
go '//// ' '/ '
go '//// /' '/ /'
go '//// //' '/ /'
go '//// ///' '/ /'
go '////' '/'
go '////x' '/x'
go '////x/' '/x/'
go '////x//' '/x/'
go '////x///' '/x/'
go '///x' '/x'
go '///x/' '/x/'
go '///x//' '/x/'
go '///x///' '/x/'
go '//x' '//x'
go '//x/' '//x/'
go '//x//' '//x/'
go '//x///' '//x/'
go '/x' '/x'
go '/x/' '/x/'
go '/x//' '/x/'
go '/x///' '/x/'
