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

#
# .../docker <target>
#
# Builds a Docker image and pushes it to this project's registry.
#

f() {

  declare -g sst_rundir
  declare -g sst_tmpdir

  local iid_target
  local image_id
  local tar_target
  local x

  sst_expect_argument_count $# 1

  case $1 in *.iid)
    iid_target=$1
    tar_target=
  ;; *.tar)
    iid_target=$1.iid
    tar_target=$1
  ;; *.tar.gz | *.tar.xz)
    iid_target=${1%.*}.iid
    tar_target=$1
  ;; *)
    sst_barf \
      "<target> must end in" \
      ".iid, .tar, .tar.gz, or .tar.xz: $1" \
    ;
  esac
  readonly iid_target
  readonly tar_target

  sst_ubuntu_install_raw \
    gcc \
    git \
    make \
    openssl \
    sshpass \
    wget \
    xz-utils \
  ;

  dist_archive=$sst_rundir/$(sst_find_dist_archive)
  readonly dist_archive

  mkdir "$sst_tmpdir"/dist_archive
  cd "$sst_tmpdir"/dist_archive
  sst_extract_archive "$dist_archive"
  cd *

  ./configure

  make $iid_target
  sst_mkdir_p_only "$sst_rundir/$iid_target"
  cp $iid_target "$sst_rundir/$iid_target"

  image_id=$(cat <"$iid_target")
  readonly image_id

  #
  # Push the image if the registry is enabled for this project.
  #

  if [[ "${CI_REGISTRY_IMAGE-}" ]]; then

    nametags=$(
      docker images \
        --no-trunc \
        --format "{{.ID}} {{.Repository}}:{{.Tag}}" \
      | sed -n "s/^$image_id //p"
    )
    readonly nametags

    local distinct_names=
    for x in $nametags; do
      x=${x%:*}
      if [[ "$distinct_names" != *" $x "* ]]; then
        distinct_names+=" $x "
      fi
    done
    readonly distinct_names

    for x in $distinct_names; do
      x=$CI_REGISTRY_IMAGE/$x:$CI_COMMIT_SHA
      docker tag "$image_id" "$x"
      docker push "$x"
    done

    # Also push the image as <name>:master when running for branch master.
    if [[ "${CI_COMMIT_BRANCH-}" == master ]]; then
      for src in $distinct_names; do
        dst=$CI_REGISTRY_IMAGE/${src%:*}:master
        docker tag $src $dst
        docker push $dst
      done
    fi

    # Also push the image as every nametag when running for a version tag.
    if [[ "${CI_COMMIT_TAG-}" == v* ]]; then
      for src in $nametags; do
        dst=$CI_REGISTRY_IMAGE/$src
        docker tag $src $dst
        docker push $dst
      done
    fi

  fi

  #
  #

  if [[ "$tar_target" ]]; then
    make $tar_target
    cp --parents $tar_target "$rundir"
  fi

}; f "$@"
