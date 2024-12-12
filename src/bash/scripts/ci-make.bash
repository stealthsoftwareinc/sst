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

function main {

  local artifact
  local -a build_depends
  local clear_list
  local dist_archive
  local -a operands
  local parse_options
  local v

  if [[ "${GITLAB_CI-}" == '' ]]; then
    sst_barf \
      "This script should only be used by CI jobs. If you're" \
      "working on a development machine, you should simply use make." \
    ;
  fi

  build_depends=()
  operands=()

  parse_options=1
  set x "$@"
  while shift && (($# > 0)); do

    if ((parse_options)); then

      #-----------------------------------------------------------------
      # Options terminator
      #-----------------------------------------------------------------

      sst_parse_opt -- forbidden : "$@"
      eval "$pop"
      if ((got)); then
        parse_options=
        continue
      fi

      #-----------------------------------------------------------------
      # --build-depends
      #-----------------------------------------------------------------

      sst_parse_opt --build-depends : "$@"
      eval "$pop"
      if ((got)); then
        build_depends+=("$arg")
        continue
      fi

      #-----------------------------------------------------------------
      # Unknown options
      #-----------------------------------------------------------------

      sst_unknown_opt "$1"

      #-----------------------------------------------------------------

    fi

    operands+=("$1")

  done
  readonly parse_options

  readonly build_depends
  readonly operands

  sst_ubuntu_install_raw "${build_depends[@]}"

  dist_archive=$sst_rundir/$(sst_find_dist_archive)
  readonly dist_archive

  mkdir -p artifacts
  cp "$dist_archive" artifacts

  cd "$sst_tmpdir"
  sst_extract_archive "$dist_archive"
  cd *
  ./configure

  if [[ -e artifacts ]]; then
    sst_barf \
      "The distribution archive should" \
      "not contain a file or directory named \"artifacts\"." \
    ;
  fi
  mv -f "$sst_rundir"/artifacts .

  clear_list=
  for artifact in artifacts/**; do
    artifact=${artifact%/}
    sst_expect_source_path "$artifact"
    if [[ -f $artifact ]]; then
      v=$(make $artifact/src)
      sst_expect_basic_identifier "$v"
      clear_list+=" $v="
    elif [[ ! -d $artifact ]]; then
      sst_barf \
        "The \"artifacts\" directory should" \
        "only contain regular files and directories." \
      ;
    fi
  done
  readonly clear_list

  make $clear_list "${operands[@]}"

  mv -f artifacts "$sst_rundir"

}; readonly -f main

main "$@"
