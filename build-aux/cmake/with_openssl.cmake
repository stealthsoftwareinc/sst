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

include_guard(GLOBAL)

foreach(x
  with_threads
)
  if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/build-aux/cmake/${x}.cmake)
    include(build-aux/cmake/${x}.cmake)
  endif()
endforeach()

set(with_openssl auto CACHE STRING
  "Whether to use the OpenSSL library."
)

set_property(CACHE with_openssl
  PROPERTY STRINGS yes no auto
)

if(${with_openssl} STREQUAL no)
  add_compile_definitions(${m_prefix}WITH_OPENSSL_CRYPTO=0)
  add_compile_definitions(${m_prefix}WITH_OPENSSL_SSL=0)
elseif(${with_openssl} STREQUAL auto OR ${with_openssl} STREQUAL yes)
  if(DEFINED OpenSSL_FOUND)
    string(CONCAT m
      "SST was about to call "
      "find_package(OpenSSL), "
      "but it looks like it's already been called. "
      "Please remove the call and let SST handle it."
    )
    message(FATAL_ERROR "${m}")
  endif()
  find_package(OpenSSL)
  if(OpenSSL_FOUND)
    add_compile_definitions(${m_prefix}WITH_OPENSSL_CRYPTO=1)
    add_compile_definitions(${m_prefix}WITH_OPENSSL_SSL=1)
    list(PREPEND libs OpenSSL::Crypto)
    list(PREPEND libs OpenSSL::SSL)
  elseif(${with_openssl} STREQUAL auto)
    add_compile_definitions(${m_prefix}WITH_OPENSSL_CRYPTO=0)
    add_compile_definitions(${m_prefix}WITH_OPENSSL_SSL=0)
  else()
    message(FATAL_ERROR
      "The OpenSSL library is not available."
    )
  endif()
else()
  message(FATAL_ERROR
    "Invalid with_openssl value: \"${with_openssl}\"."
  )
endif()
