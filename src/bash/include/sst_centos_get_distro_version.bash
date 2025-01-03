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

sst_centos_get_distro_version() {

  local version

  if ((SST_DEBUG)); then
    if (($# != 0)); then
      sst_expect_argument_count $# 0
    fi
  fi

  version=

  if [[ -f /etc/system-release ]]; then
    version=$(sed -n '
      1 {
        s/^CentOS release 6\..*/6/p
        s/^CentOS Linux release 7\..*/7/p
        s/^CentOS Linux release 8\..*/8/p
        q
      }
    ' /etc/system-release)
  fi

  printf '%s\n' "$version"

}; readonly -f sst_centos_get_distro_version
