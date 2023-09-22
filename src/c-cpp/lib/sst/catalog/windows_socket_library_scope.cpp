//
// Copyright (C) 2012-2023 Stealth Software Technologies, Inc.
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice (including
// the next paragraph) shall be included in all copies or
// substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// SPDX-License-Identifier: MIT
//

// Include first to test independence.
#include <sst/catalog/windows_socket_library_scope.hpp>
// Include twice to test idempotence.
#include <sst/catalog/windows_socket_library_scope.hpp>
//

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/sst_w32_WSADATA_wrapper.h>
#include <sst/config.h>

namespace {

void check_major_minor(int const major, int const minor) {
  // clang-format off
  SST_ASSERT((false
    || (major == 1 && minor == 0)
    || (major == 1 && minor == 1)
    || (major == 2 && minor == 0)
    || (major == 2 && minor == 1)
    || (major == 2 && minor == 2)
  ));
  // clang-format on
}

} // namespace

namespace sst {

windows_socket_library_scope::windows_socket_library_scope()
    : windows_socket_library_scope(2, 2) {
}

} // namespace sst

//----------------------------------------------------------------------
#if SST_WITH_WINDOWS_WS2_32
//----------------------------------------------------------------------

#include <cstdlib>
#include <memory>
#include <new>

#include <sst/catalog/sst_w32_WSACleanup.h>
#include <sst/catalog/sst_w32_WSADATA.h>
#include <sst/catalog/sst_w32_WSADATA_wrap.h>
#include <sst/catalog/sst_w32_WSAStartup.h>
#include <sst/catalog/sst_w32_sizeof_WSADATA.h>
#include <sst/catalog/wsa_exception.hpp>

namespace sst {

windows_socket_library_scope::windows_socket_library_scope(
    int const major,
    int const minor) {
  check_major_minor(major, minor);
  sst_w32_WSADATA * const data =
      static_cast<sst_w32_WSADATA *>(malloc(sst_w32_sizeof_WSADATA));
  if (data == nullptr) {
    throw std::bad_alloc();
  }
  std::unique_ptr<sst_w32_WSADATA, void (*)(sst_w32_WSADATA *)> d_ptr(
      data,
      [](sst_w32_WSADATA * const data) { free(data); });
  int const s = sst_w32_WSAStartup(
      static_cast<sst_w32_WORD>((major << 8) | minor),
      data);
  if (s != 0) {
    throw sst::wsa_exception("WSAStartup()", s);
  }
  sst_w32_WSADATA_wrap(data, &data_);
}

windows_socket_library_scope::~windows_socket_library_scope() noexcept {
  int const s = sst_w32_WSACleanup();
  static_cast<void>(s);
}

} // namespace sst

//----------------------------------------------------------------------
#else
//----------------------------------------------------------------------

namespace sst {

windows_socket_library_scope::windows_socket_library_scope(
    int const major,
    int const minor)
    : data_{} {
  check_major_minor(major, minor);
}

windows_socket_library_scope::~windows_socket_library_scope() noexcept {
}

} // namespace sst

//----------------------------------------------------------------------
#endif
