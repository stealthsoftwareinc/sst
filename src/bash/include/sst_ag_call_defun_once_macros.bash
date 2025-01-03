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

sst_ag_call_defun_once_macros() {

  declare    x
  declare    xs
  declare    y

  xs=$(sst_grep -l AC_DEFUN_ONCE m4/*.m4)
  readonly xs

  y=m4/CALL_DEFUN_ONCE_MACROS.m4
  readonly y

  sst_expect_not_exist "$y"

  >$y

  sst_ihs <<<'
    dnl
    dnl Copyright (C) 2012-2024 Stealth Software Technologies, Inc.
    dnl
    dnl Permission is hereby granted, free of charge, to any person
    dnl obtaining a copy of this software and associated documentation
    dnl files (the "Software"), to deal in the Software without
    dnl restriction, including without limitation the rights to use,
    dnl copy, modify, merge, publish, distribute, sublicense, and/or
    dnl sell copies of the Software, and to permit persons to whom the
    dnl Software is furnished to do so, subject to the following
    dnl conditions:
    dnl
    dnl The above copyright notice and this permission notice (including
    dnl the next paragraph) shall be included in all copies or
    dnl substantial portions of the Software.
    dnl
    dnl THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    dnl EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    dnl OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    dnl NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    dnl HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    dnl WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    dnl FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    dnl OTHER DEALINGS IN THE SOFTWARE.
    dnl
    dnl SPDX-License-Identifier: MIT
    dnl

    AC_DEFUN_ONCE([CALL_DEFUN_ONCE_MACROS], [[
    ]GATBPS_CALL_COMMENT([$0]m4_if(m4_eval([$# > 0]), [1], [, $@]))[
    { :
  ' >>$y

  sst_push_var IFS

  for x in $xs; do
    x=${x##*/}
    x=${x%.*}
    sst_ihs -2 <<<'
      ]GATBPS_REQUIRE(['"$x"'])[
    ' >>$y
  done

  sst_pop_var IFS

  sst_ihs <<<'
    }]])
  ' >>$y

  sst_ac_append <<<'CALL_DEFUN_ONCE_MACROS'

}; readonly -f sst_ag_call_defun_once_macros
