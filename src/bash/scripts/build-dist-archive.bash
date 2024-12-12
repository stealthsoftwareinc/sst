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

  local -a build_depends
  local kv_ASCIIDOCTOR
  local parse_options
  local tag
  local tags

  build_depends=()

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

    sst_barf "operands are forbidden"

  done
  readonly parse_options

  readonly build_depends

  sst_ubuntu_install_raw "${build_depends[@]}"

  #---------------------------------------------------------------------
  #
  # If we're building in a GitLab CI pipeline that wasn't started by a
  # tag, we don't want to produce a tag-like version number, as this
  # tends to cause problems in downstream CI jobs. To ensure this
  # doesn't happen, we delete any tags pointing at HEAD.
  #
  # This situation usually happens when a branch update and a tag that
  # points at the new branch tip are pushed at the same time. The push
  # will start two pipelines: one for the branch, and one for the tag.
  # When the branch pipeline eventually starts its first job, the tag
  # will already be there, causing a version number like 0.19.0 to be
  # generated instead of the desired 0.18.2-286+gb74639261.
  #

  if [[ "${GITLAB_CI-}" && ! "${CI_COMMIT_TAG-}" ]]; then
    tags=$(git tag --points-at HEAD)
    for tag in $tags; do
      git tag -d -- "$tag"
    done
  fi

  #---------------------------------------------------------------------

  ./autogen

  kv_ASCIIDOCTOR=
  if [[ -x build-aux/adock ]]; then
    kv_ASCIIDOCTOR='ASCIIDOCTOR="build-aux/adock"'
  fi

  eval ./configure \
    "$kv_ASCIIDOCTOR" \
  ;

  make dist

}; readonly -f main

main "$@"
