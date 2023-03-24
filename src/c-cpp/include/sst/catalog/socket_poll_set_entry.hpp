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

#ifndef SST_CATALOG_SOCKET_POLL_SET_ENTRY_HPP
#define SST_CATALOG_SOCKET_POLL_SET_ENTRY_HPP

#include <sst/catalog/SST_WITH_POSIX.h>
#include <sst/catalog/SST_WITH_WINDOWS.h>

#if 0

//----------------------------------------------------------------------
#elif SST_WITH_POSIX
//----------------------------------------------------------------------

#include <sst/catalog/posix_socket_poll_set_entry.hpp>

namespace sst {

using socket_poll_set_entry = sst::posix_socket_poll_set_entry;

} // namespace sst

//----------------------------------------------------------------------
#elif SST_WITH_WINDOWS
//----------------------------------------------------------------------

#include <sst/catalog/windows_socket_poll_set_entry.hpp>

namespace sst {

using socket_poll_set_entry = sst::windows_socket_poll_set_entry;

} // namespace sst

//----------------------------------------------------------------------
#endif

#endif // #ifndef SST_CATALOG_SOCKET_POLL_SET_ENTRY_HPP
