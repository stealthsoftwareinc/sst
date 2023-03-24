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
#include <sst/catalog/posix_directory_iterator.hpp>
// Include twice to test idempotence.
#include <sst/catalog/posix_directory_iterator.hpp>
//

#include <sst/catalog/SST_WITH_POSIX.h>

#if SST_WITH_POSIX

#include <cstring>
#include <memory>

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/directory_iterator_options.hpp>
#include <sst/catalog/posix_readdir.hpp>

namespace sst {

posix_directory_iterator::posix_directory_iterator(
    construct_from_byte_pointer_tag,
    char const * const path,
    sst::directory_iterator_options const & options)
    : shared_(std::make_shared<decltype(shared_)::element_type>()) {
  SST_ASSERT((path != nullptr));
  shared_->path = path;
  shared_->options = options;
  shared_->stack.emplace(shared_->path, 0);
  if (!shared_->path.empty() && shared_->path.back() != '/') {
    shared_->path += '/';
  }
  prefix_ = shared_->path.size();
  ++*this;
}

} // namespace sst

#endif // #if SST_WITH_POSIX
