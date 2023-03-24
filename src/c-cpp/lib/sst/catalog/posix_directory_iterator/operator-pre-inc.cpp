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

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/make_unique.hpp>

namespace sst {

posix_directory_iterator & posix_directory_iterator::operator++() {
  SST_ASSERT((shared_ != nullptr));
  auto const & options = shared_->options;
  auto & stack = shared_->stack;
  SST_ASSERT((!stack.empty()));
next:
  if (stack.empty()) {
    shared_ = nullptr;
  } else {
    auto & top = stack.top();
    if (!top.readdir.next()) {
      shared_->path.erase(shared_->path.size() - top.step);
      stack.pop();
      goto next;
    }
    // TODO: We should have an option that lets . and .. be included.
    if (top.readdir.name_is_dot_or_dotdot()) {
      goto next;
    }
    {
      auto const n = shared_->path.size();
      shared_->path += top.readdir.name();
      if (path_ == nullptr) {
        path_ = sst::make_unique<sst::posix_path>(shared_->path);
      } else {
        *path_ = shared_->path;
      }
      shared_->path.resize(n);
    }
    path_->follow_links(options.follow_links());
    if (options.recursive() && path_->test_d()) {
      auto const n = shared_->path.size();
      shared_->path += top.readdir.name();
      shared_->path += '/';
      stack.emplace(path_->str().c_str(), shared_->path.size() - n);
    }
  }
  return *this;
}

} // namespace sst

#endif // #if SST_WITH_POSIX
