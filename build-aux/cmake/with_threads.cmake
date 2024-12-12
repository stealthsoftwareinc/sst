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
# CMAKE_THREAD_PREFER_PTHREAD causes pthreads to be preferred when
# multiple multithreading libraries are present.
#
# THREADS_PREFER_PTHREAD_FLAG causes the -pthread flag to be preferred
# over the obsolete -lpthread flag.
#

include_guard(GLOBAL)

set(with_threads auto CACHE STRING
  "Whether to use threads."
)

set_property(CACHE with_threads
  PROPERTY STRINGS yes no auto
)

if(${with_threads} STREQUAL no)
  add_compile_definitions(${m_prefix}WITH_THREADS=0)
elseif(${with_threads} STREQUAL auto OR ${with_threads} STREQUAL yes)
  if(DEFINED Threads_FOUND)
    string(CONCAT m
      "SST was about to call "
      "find_package(Threads), "
      "but it looks like it's already been called. "
      "Please remove the call and let SST handle it."
    )
    message(FATAL_ERROR "${m}")
  endif()
  set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
  set(THREADS_PREFER_PTHREAD_FLAG TRUE)
  find_package(Threads)
  if(Threads_FOUND)
    add_compile_definitions(${m_prefix}WITH_THREADS=1)
    list(PREPEND libs Threads::Threads)
  elseif(${with_threads} STREQUAL auto)
    add_compile_definitions(${m_prefix}WITH_THREADS=0)
  else()
    message(FATAL_ERROR
      "Threads are not available."
    )
  endif()
else()
  message(FATAL_ERROR
    "Invalid with_threads value: \"${with_threads}\"."
  )
endif()
