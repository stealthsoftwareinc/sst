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

#ifndef SST_CATALOG_WINDOWS_PATH_MV_ONTO_CORE_HPP
#define SST_CATALOG_WINDOWS_PATH_MV_ONTO_CORE_HPP

// Include first to test independence.
#include <sst/catalog/windows_path.hpp>
// Include twice to test idempotence.
#include <sst/catalog/windows_path.hpp>
//

#include <sst/catalog/SST_WITH_WINDOWS_KERNEL32.h>

#if SST_WITH_WINDOWS_KERNEL32

#include <string>

#include <windows.h>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/SST_THROW_UNIMPLEMENTED.hpp>
#include <sst/catalog/c_quote.hpp>
#include <sst/catalog/gle_exception.hpp>

namespace sst {

//
// Do not use MOVEFILE_COPY_ALLOWED. Yes, it makes moving a file across
// filesystems work, but it also causes any attempt to move a directory
// across filesystems to fail with ERROR_ACCESS_DENIED. If we leave out
// MOVEFILE_COPY_ALLOWED, we consistently get ERROR_NOT_SAME_DEVICE for
// files and directories.
//

// TODO: What happens with symbolic links here?

template<class CharT>
template<class MoveFileExFunc>
void windows_path<CharT>::mv_onto_core(
    MoveFileExFunc * const MoveFileEx_func,
    char const * const MoveFileEx_name,
    windows_path<CharT> const & dst) const {
  windows_path<CharT> const & src = *this;
  SST_ASSERT((!src.moved_from_));
  SST_ASSERT((!dst.moved_from_));
  SST_ASSERT((!dst.test_d()));
  char_t const * const a = src.c_str();
  char_t const * const b = dst.c_str();
  if (!MoveFileEx_func(a,
                       b,
                       MOVEFILE_REPLACE_EXISTING
                           | MOVEFILE_WRITE_THROUGH)) {
    DWORD const e = GetLastError();
    if (e == ERROR_NOT_SAME_DEVICE) {
      // TODO: Copy src to dst and delete src.
      SST_THROW_UNIMPLEMENTED();
    }
    throw sst::gle_exception(
        std::string(MoveFileEx_name) + "() failed to move "
            + sst::c_quote(a) + " to " + sst::c_quote(b),
        e);
  }
}

} // namespace sst

#endif // #if SST_WITH_WINDOWS_KERNEL32

#endif // SST_CATALOG_WINDOWS_PATH_MV_ONTO_CORE_HPP
