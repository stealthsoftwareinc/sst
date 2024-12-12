##
## Copyright (C) 2012-2024 Stealth Software Technologies, Inc.
##
## Permission is hereby granted, free of charge, to any person
## obtaining a copy of this software and associated documentation
## files (the "Software"), to deal in the Software without
## restriction, including without limitation the rights to use,
## copy, modify, merge, publish, distribute, sublicense, and/or
## sell copies of the Software, and to permit persons to whom the
## Software is furnished to do so, subject to the following
## conditions:
##
## The above copyright notice and this permission notice (including
## the next paragraph) shall be included in all copies or
## substantial portions of the Software.
##
## THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
## EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
## OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
## NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
## HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
## WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
## FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
## OTHER DEALINGS IN THE SOFTWARE.
##
## SPDX-License-Identifier: MIT
##

#
# Some parts of this file are from the SST package.
#
# The following copyright notice is generally applicable:
#
#      Copyright (C) Stealth Software Technologies, Inc.
#
# The full copyright information depends on the distribution
# of the package. For more information, see the COPYING file.
# However, depending on the context in which you are viewing
# this file, the COPYING file may not be available.
#

## begin_variables

AM_CPPFLAGS = \
  -I src/c-cpp/lib \
  -I $(srcdir)/src/c-cpp/lib \
  -I src/c-cpp/include \
  -I $(srcdir)/src/c-cpp/include \
  -I include \
  -I $(srcdir)/include \
  -I ../src/c-cpp/lib \
  -I $(srcdir)/../src/c-cpp/lib \
  -I ../src/c-cpp/include \
  -I $(srcdir)/../src/c-cpp/include \
  -I ../include \
  -I $(srcdir)/../include \
$(empty)

MOSTLYCLEANFILES =

gen_targets =

noinst_PROGRAMS =

## end_variables

## begin_includes

include $(srcdir)/../build-aux/GATBPS_VPATH_SEARCH.am
include $(srcdir)/../build-aux/gatbps.am
include $(srcdir)/bin/sst_status_map_generator.am
include $(srcdir)/build-src/top_targets.am
include $(srcdir)/include/src/sst_status_map.inc.am

## end_includes
