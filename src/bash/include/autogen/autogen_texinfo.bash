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

autogen_texinfo() {

  local dd
  local x1
  local x2
  local x3
  local y1
  local y2
  local y2s

  case $# in
    0 | 1)
      sst_barf 'invalid argument count: %d' $#
    ;;
  esac

  x1=$1
  readonly x1
  expect_safe_path "$x1"
  case $x1 in
    *.texi)
    ;;
    *)
      sst_barf '$1 must end in .texi: %s' $x1
    ;;
  esac
  shift

  x2=$(echo $x1 | sed 's/\.texi$//')
  readonly x2

  x3=$(echo $x2 | sed 's/[^0-9A-Z_a-z]/_/g')
  readonly x3

  cat >$x2.am <<EOF
${x3}_TEXINFOS =
EOF

  for dd; do

    expect_safe_path "$dd"

    y2s=:

    for y1 in \
      $dd/*.css \
      $dd/*.texi \
      $dd/*.texi.in \
    ; do

      expect_safe_path "$y1"

      if [[ $y1 == $x1 ]]; then
        continue
      fi

      case $y1 in
        *.texi.in)
          y2=$(echo $y1 | sed 's/\.in$//')
        ;;
        *)
          y2=$y1
        ;;
      esac

      case $y2s in
        *:$y2:*)
          continue
        ;;
      esac

      printf '%s_TEXINFOS += %s\n' $x3 $y2 >>$x2.am

      y2s=$y2s$y2:

    done

  done

  sst_am_include $x2.am

}; readonly -f autogen_texinfo
