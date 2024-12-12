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

eval bash_version="${bash_version_q?}"

readonly DOCKER
readonly abs_builddir_q
readonly abs_srcdir_q
readonly bash_version
readonly dist_archive_q

name=sst-test-bash-${bash_version?}
readonly name

c="${DOCKER?} build"
c="${c?} --build-arg sst_bash_version=${bash_version?}"
c="${c?} -q"
c="${c?} -t ${name?}"
c="${c?} ${abs_srcdir_q?}/src/bash/test/docker"
printf '%s\n' "${c?}"
eval " ${c?}" || exit $?

c="${DOCKER?} rm"
c="${c?} -f"
c="${c?} ${name?}"
printf '%s\n' "${c?}"
eval " ${c?}" || exit $?

c="${DOCKER?} run"
c="${c?} --name ${name?}"
c="${c?} -i"
c="${c?} -v ${abs_builddir_q?}/${dist_archive_q?}:/sst.tar.gz"
c="${c?} ${name?}"
printf '%s\n' "${c?}"
eval " ${c?}" || exit $?

c="${DOCKER?} start ${name?}"
printf '%s\n' "${c?}"
eval " ${c?}" || exit $?
