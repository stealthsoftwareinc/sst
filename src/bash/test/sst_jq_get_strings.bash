#! /bin/sh -

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
# This script uses the SST Bash library to bootstrap from /bin/sh into
# bash. See the Bash library > Bootstrapping section of the SST manual
# for more information.
#

#-----------------------------------------------------------------------

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

declare actual
declare expected

go2() {

  local actual_str
  local cmp
  local code
  local expected_str
  local x

  code=$(cat)
  readonly code

  eval " $code"

  expected_str=
  for x in ${expected[@]+"${expected[@]}"}; do
    expected_str+=${expected_str:+ }$(sst_quote "$x")
  done
  readonly expected_str

  actual_str=
  for x in ${actual[@]+"${actual[@]}"}; do
    actual_str+=${actual_str:+ }$(sst_quote "$x")
  done
  readonly actual_str

  cmp=$(sst_array_cmp actual expected)
  readonly cmp

  if ((cmp == 0)); then
    printf \
      'pass: { %s; } produces actual=(%s)\n' \
      "$code" \
      "$expected_str" \
    ;
  else
    printf \
      'fail: { %s; } produces actual=(%s): got actual=(%s)\n' \
      "$code" \
      "$expected_str" \
      "$actual_str" \
    ;
    exit 1
  fi

}; readonly -f go2

go() {

  local filter
  local json

  json=$(sst_quote "$1")
  readonly json

  filter=$(sst_quote "$2")
  readonly filter

  printf '%s\n' "$1" >"$sst_tmpdir"/json

  go2 <<<"sst_jq_get_strings $json $filter actual"
  go2 <<<"sst_jq_get_strings - $filter actual <<<$json"
  go2 <<<"sst_jq_get_strings \"\$sst_tmpdir\"/json $filter actual"

}; readonly -f go

#-----------------------------------------------------------------------

expected=('')
go ' null' .

expected=('')
go ' ""' .

expected=('')
go ' []' .

expected=('')
go ' [null]' .

expected=('')
go ' [""]' .

expected=('foo' 'bar')
go ' ["foo", "bar"]' .

expected=('foo' 'bar')
go ' [["foo", "bar"]]' '.[0]'

expected=('')
go ' {}' '.foo'
