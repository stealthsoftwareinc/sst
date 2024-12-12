#! /bin/sh -
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

eval ASCIIDOCTOR_FLAGS='${ASCIIDOCTOR_FLAGS?}'
eval MAKE='${MAKE:?}'
eval SED='${SED:?}'
eval TSUF=${TSUF:?}
eval adoc=${adoc:?}
eval dst=${dst:?}
eval imagesdir=${imagesdir:?}
eval pdf=${pdf:?}
eval prefix=${prefix:?}
eval slug=${slug:?}
eval srcdir=${srcdir:?}

readonly ASCIIDOCTOR_FLAGS
readonly MAKE
readonly SED
readonly TSUF
readonly adoc
readonly dst
readonly imagesdir
readonly pdf
readonly prefix
readonly slug
readonly srcdir

tmp=${dst?}${TSUF?}999
readonly tmp

if test -f ${adoc?}; then
  cp ${adoc?} ${tmp?}.adoc || exit $?
else
  cp ${srcdir?}/${adoc?} ${tmp?}.adoc || exit $?
fi

af=
af="${af?} -a imagesdir=${imagesdir?}"
af="${af?} ${ASCIIDOCTOR_FLAGS?}"
readonly af

eval " ${MAKE?}"' \
  ASCIIDOCTOR_FLAGS="${af?}" \
  ${tmp?}.html \
' || exit $?

#---------------------------------------------------------------
# KaTeX installation
#---------------------------------------------------------------

if test -d ${prefix?}katex; then

  mv -f ${tmp?}.html ${dst?}${TSUF?}1 || exit $?

  x='
    /<script.*[Mm]ath[Jj]ax.*\.js/ d
  '
  eval " ${SED?}"' \
    "${x?}" \
    <${dst?}${TSUF?}1 \
    >${dst?}${TSUF?}2 \
  ' || exit $?

  mv -f ${dst?}${TSUF?}2 ${tmp?}.html || exit $?

fi

#---------------------------------------------------------------
# Fonts installation
#---------------------------------------------------------------
#
# TODO: This used to have some code to download Google fonts
#       locally, but it was removed because it was too brittle
#       (??). The code here now seems silly because all it does
#       is remove any <link>'d Google fonts (??). Maybe we
#       should revisit the downloading idea, but with a soft
#       failure approach, so that if downloading fails for
#       whatever reason then the fonts are just skipped.
#

if test -d ${prefix?}fonts; then

  mv -f ${tmp?}.html ${dst?}${TSUF?}1 || exit $?

  x='
    /<link.*fonts\.googleapis\.com/ d
  '
  eval " ${SED?}"' \
    "${x?}" \
    <${dst?}${TSUF?}1 \
    >${dst?}${TSUF?}2 \
  ' || exit $?

  mv -f ${dst?}${TSUF?}2 ${tmp?}.html || exit $?

fi

#---------------------------------------------------------------

eval " ${MAKE?}"' \
  ASCIIDOCTOR_FLAGS="${af?}" \
  ${tmp?}.pdf \
' || exit $?

#---------------------------------------------------------------

mv -f ${tmp?}.html ${dst?} || exit $?
mv -f ${tmp?}.pdf ${pdf?} || exit $?

#---------------------------------------------------------------
