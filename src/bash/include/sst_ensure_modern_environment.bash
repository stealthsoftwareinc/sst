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

sst_ensure_modern_environment() {

  # Bash >=4.2: declare -g    SST_MODERN_ENVIRONMENT
  # Bash >=4.2: declare -g    sst_distro

  declare    cmd
  declare    x

  if [[ ! "${SST_MODERN_ENVIRONMENT+x}" ]]; then
    sst_get_distro
    case $sst_distro in '')
    ;; centos)
      sst_get_distro_version
      case $sst_distro_version in '')

      #-----------------------------------------------------------------
      # centos 7
      #-----------------------------------------------------------------
      ;; 7)

        sst_centos_install_raw centos-release-scl
        sst_centos_install_raw devtoolset-11
        cmd=
        for x; do
          cmd+=${cmd:+ }$(sst_quote "$x")
        done
        export SST_MODERN_ENVIRONMENT=
        sst_exec scl enable devtoolset-11 "$cmd"

      #-----------------------------------------------------------------
      esac
    esac
  fi

}; readonly -f sst_ensure_modern_environment
