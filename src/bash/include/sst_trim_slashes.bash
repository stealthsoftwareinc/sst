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

sst_trim_slashes() {

  declare    path
  declare    x

  if (($# == 0)); then
    path=$(cat | sst_csf) || sst_err_trap "$sst_last_command"
    sst_csf path || sst_err_trap "$sst_last_command"
  elif (($# == 1)); then
    path=$1
  else
    sst_expect_argument_count $# 0-1
  fi
  readonly path

  x=${path%%+(/)}
  if [[ ! "$x" ]]; then
    if [[ "$path" == // ]]; then
      x=//
    elif [[ "$path" == /* ]]; then
      x=/
    fi
  fi
  readonly x

  printf '%s\n' "$x" || sst_err_trap "$sst_last_command"

}; readonly -f sst_trim_slashes
