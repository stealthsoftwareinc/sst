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

sst_ajh_gitbundle() {

  local dir
  local x1
  local x2
  local x3
  local x4
  local name
  local commit

  case $# in
    1)
    ;;
    *)
      sst_barf 'invalid argument count: %d' $#
    ;;
  esac

  dir=$1
  readonly dir
  expect_safe_path "$dir"

  for x1 in $dir/**/*.ag.json; do

    sst_expect_ag_json x2 "$x1"
    x3=$(echo $x2 | sed "s|^$dir/||")
    x4=$(sst_underscore_slug $x3)

    commit=$(jq -r .commit $x1 | sed 's/\$/$][/g')

    autogen_ac_append <<EOF

]m4_define(
  [${x4}_commit_default],
  [[$commit]])[

case $][{${x4}_commit+x} in
  "")
    ${x4}_commit=']${x4}_commit_default['
  ;;
esac
readonly ${x4}_commit

]AC_ARG_VAR(
  [${x4}_commit],
  [
    the commit of the $x3 Git repository to use
    (default: ${x4}_commit=']${x4}_commit_default[')
  ])[

]m4_define(
  [${x4}_urls_default],
  [[ ]dnl
[\$][(abs_srcdir)/../$x3 ]dnl
EOF

    jq -r '
      .urls[]
      | gsub("\\$"; "$][$][")
      | "['\'\\\\\'\''" + . + "'\'\\\\\'\'' ]dnl"
    ' $x1 | autogen_ac_append

    autogen_ac_append <<EOF
])[

case $][{${x4}_urls+x} in
  "")
    ${x4}_urls=']${x4}_urls_default['
  ;;
esac
readonly ${x4}_urls

]AC_ARG_VAR(
  [${x4}_urls],
  [
    the URLs from which to fetch the $x3 Git repository
    (default: ${x4}_urls=']${x4}_urls_default[')
  ])[

]GATBPS_GIT_CLONE(
  [$dir-clones/$x3-\$(${x4}_commit)],
  [
    [\$(${x4}_urls)],
  ],
  [clean])[

]GATBPS_GIT_BUNDLE(
  [$x2-\$(${x4}_commit).gitbundle],
  [$dir-clones/$x3-\$(${x4}_commit)],
  [\$(${x4}_commit)],
  [clean])[

]GATBPS_CP(
  [$x2.gitbundle],
  [$x2-\$(${x4}_commit).gitbundle],
  [file],
  [clean])[

EOF

  done

}; readonly -f sst_ajh_gitbundle
