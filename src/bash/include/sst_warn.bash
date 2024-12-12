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
# This function may be called by sst_install_utility, so we need to be
# careful to only use utilities that are always available and run them
# with "command", and we need to explicitly call sst_err_trap on error
# to handle errexit suspension correctly. errexit suspension will occur
# when the user uses idioms such as "foo || s=$?" or "if foo; then" and
# foo triggers our automatic utility installation system. In this case,
# we want to maintain the behavior expected by the user but still barf
# if the installation of foo fails.
#

sst_warn() {

  # Bash >=4.2: declare -g    CLICOLOR_FORCE
  # Bash >=4.2: declare -g    NO_COLOR

  local    color_start
  local    color_stop
  local    message

  #
  # See [1], [2], and [3] for the basics of color control environment
  # variables. Note that the approach in FreeBSD [3] defaults to color
  # disabled and always requires CLICOLOR to be set to enable color, but
  # the approach in [1] defaults to color enabled in a terminal and does
  # not use CLICOLOR. We use the approach in [1] since we generally want
  # color enabled by default in a terminal.
  #
  # [1] https://bixense.com/clicolors/
  # [2] https://no-color.org/
  # [3] https://stackoverflow.com/q/75625246
  #

  if [[ ! "${NO_COLOR+x}" && ( "${CLICOLOR_FORCE+x}" || -t 2 ) ]]; then
    color_start=$'\x1B[33m'
    color_stop=$'\x1B[0m'
  else
    color_start=
    color_stop=
  fi
  readonly color_start
  readonly color_stop

  message="$color_start$0: Warning: $@$color_stop"
  readonly message

  printf '%s\n' "$message" >&2 || :

}; readonly -f sst_warn
