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

function main {

  local commit
  local -r github_ssh_regex='^(ssh://)?([^@]+@)?(([^:]+\.)?github\.[^:]+):(.*)\.git$'
  local -r gitlab_ssh_regex='^(ssh://)?([^@]+@)?(([^:]+\.)?gitlab\.[^:]+):(.*)\.git$'

  sst_expect_argument_count $# 1

  if [[ "$1" == '{'* ]]; then
    args=$tmpdir/args.json
    cat <<<"$1" >"$args"
  else
    args=$1
  fi
  readonly args

  #
  # Parse .gitbundle from the arguments.
  #

  sst_jq_get_string_or_null .gitbundle "$args" gitbundle
  if [[ "$gitbundle" == "" ]]; then
    gitbundle=preview.gitbundle
  fi
  readonly gitbundle

  #
  # Parse .push_repo from the arguments.
  #

  unset push_repo
  unset error
  x=$(jq -r '
    .push_repo
    | if type == "array" then
        if length == 0 then
          "error+=(\": Expected a nonempty string"
                   + " or a nonempty array of nonempty strings.\")"
        else
          .[]
          | if type != "string" or . == "" then
              "error+=(\"[]: Expected a nonempty string.\")"
            else
              "push_repo+=(" + (. | @sh) + ")"
            end
        end
      elif type != "string" or . == "" then
        "error+=(\": Expected a nonempty string"
                 + " or a nonempty array of nonempty strings.\")"
      else
        "push_repo+=(" + (. | @sh) + ")"
      end
  ' "$args")
  eval "$x"
  readonly push_repo
  if [[ "${error-}" != "" ]]; then
    sst_barf '%s: .push_repo%s' "$args" "$error"
  fi

  #
  #

  git clone -- "$gitbundle" "$tmpdir/repo"
  cd "$tmpdir/repo"

  #
  # Get the branch name of the gitbundle.
  #

  n=$(git rev-list --branches | awk 'END { print NR }')
  if ((n == 0)); then
    sst_barf '%s: expected exactly one branch' "$gitbundle"
  fi
  branch=$(git show-ref --heads | awk '{ print $2 }')
  readonly branch
  if [[ "$branch" == *$'\n'* ]]; then
    sst_barf '%s: expected exactly one branch' "$gitbundle"
  fi

  commit=$(git rev-parse "$branch")
  readonly commit

  #
  # Push the branch and all tags to every push repo.
  #
  # Pushing the tags as a separate step generally helps with triggering
  # CI jobs. For example, we have observed GitHub.com fail to trigger a
  # tag-based CI job during an initial push to an empty repository that
  # pushed the master branch and a tag at the same time. We then deleted
  # the remote copy of the tag and pushed it again, and it triggered the
  # CI job successfully.
  #

  view_urls=()

  for url in ${push_repo[@]+"${push_repo[@]}"}; do

    git push -- "$url" "$branch:$branch"
    git push --follow-tags -- "$url" "$branch:$branch"

    if [[ "$url" =~ $github_ssh_regex ]]; then
      view_urls+=("https://${BASH_REMATCH[3]}/${BASH_REMATCH[5]}/tree/$commit")
    elif [[ "$url" =~ $gitlab_ssh_regex ]]; then
      view_urls+=("https://${BASH_REMATCH[3]}/${BASH_REMATCH[5]}/-/tree/$commit")
    fi

  done

  readonly view_urls

  printf '\n'
  m='The commit and all reachable annotated tags were pushed to all '
  m+='.push_repo entries. You can view it at the following URLs'
  m+=':'
  printf '%s\n\n' "$m"
  printf '   %s\n' "${view_urls[@]}"
  printf '\n'

}; readonly -f main

main "$@"
