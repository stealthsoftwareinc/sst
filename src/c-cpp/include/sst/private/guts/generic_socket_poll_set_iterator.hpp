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

#ifndef SST_PRIVATE_GUTS_GENERIC_SOCKET_POLL_SET_ITERATOR_HPP
#define SST_PRIVATE_GUTS_GENERIC_SOCKET_POLL_SET_ITERATOR_HPP

#include <functional>
#include <set>
#include <utility>
#include <vector>

#include <sst/catalog/SST_ASSERT.hpp>

namespace sst {
namespace guts {

template<class, class>
class generic_socket_poll_set;

template<class Entry>
class generic_socket_poll_set_iterator final {

  template<class, class>
  friend class sst::guts::generic_socket_poll_set;

  //--------------------------------------------------------------------
  // entries_
  //--------------------------------------------------------------------

private:

  std::vector<Entry> const * entries_;

  //--------------------------------------------------------------------
  // size_type
  //--------------------------------------------------------------------

private:

  using size_type = decltype(entries_->size());

  //--------------------------------------------------------------------
  // entries_size_
  //--------------------------------------------------------------------

private:

  size_type entries_size_;

  //--------------------------------------------------------------------
  // construct
  //--------------------------------------------------------------------

private:

  explicit generic_socket_poll_set_iterator(
      std::vector<Entry> const * const entries,
      size_type const entries_size,
      std::set<size_type, std::greater<size_type>> const * const
          deletions,
      std::pair<bool, size_type> const & failed_deletion,
      size_type const position) noexcept
      : entries_(entries),
        entries_size_(entries_size),
        deletions_(deletions),
        failed_deletion_(&failed_deletion),
        position_(position) {
    if (entries == nullptr) {
      SST_ASSERT((entries_size == 0));
      SST_ASSERT((position == 0));
    } else {
      SST_ASSERT((entries_size <= entries->size()));
      SST_ASSERT((position <= entries_size));
    }
    position_ = skip_deletions(position_);
  }

  //--------------------------------------------------------------------
  // copy-assign
  //--------------------------------------------------------------------

public:

  generic_socket_poll_set_iterator &
  operator=(generic_socket_poll_set_iterator const & other) noexcept {
    entries_ = other->entries_;
    entries_size_ = other->entries_size_;
    deletions_ = other->deletions_;
    failed_deletion_ = other->failed_deletion_;
    position_ = other->position_;
    return *this;
  }

  //--------------------------------------------------------------------
  // copy-construct
  //--------------------------------------------------------------------

public:

  generic_socket_poll_set_iterator(
      generic_socket_poll_set_iterator const & other) noexcept
      : entries_(other.entries_),
        entries_size_(other.entries_size_),
        deletions_(other.deletions_),
        failed_deletion_(other.failed_deletion_),
        position_(other.position_) {
  }

  //--------------------------------------------------------------------
  // deletions_
  //--------------------------------------------------------------------

private:

  std::set<size_type, std::greater<size_type>> const * deletions_;

  //--------------------------------------------------------------------
  // destruct
  //--------------------------------------------------------------------

public:

  ~generic_socket_poll_set_iterator() noexcept {
  }

  //--------------------------------------------------------------------
  // failed_deletion_
  //--------------------------------------------------------------------

private:

  std::pair<bool, size_type> const * failed_deletion_;

  //--------------------------------------------------------------------
  // move-assign
  //--------------------------------------------------------------------

public:

  generic_socket_poll_set_iterator &
  operator=(generic_socket_poll_set_iterator && other) noexcept {
    entries_ = other->entries_;
    entries_size_ = other->entries_size_;
    deletions_ = other->deletions_;
    failed_deletion_ = other->failed_deletion_;
    position_ = other->position_;
    return *this;
  }

  //--------------------------------------------------------------------
  // move-construct
  //--------------------------------------------------------------------

public:

  generic_socket_poll_set_iterator(
      generic_socket_poll_set_iterator && other) noexcept
      : entries_(other.entries_),
        entries_size_(other.entries_size_),
        deletions_(other.deletions_),
        failed_deletion_(other.failed_deletion_),
        position_(other.position_) {
  }

  //--------------------------------------------------------------------
  // operator-deref
  //--------------------------------------------------------------------

public:

  Entry const & operator*() const {
    SST_ASSERT((entries_ != nullptr));
    SST_ASSERT((position_ < entries_size_));
    SST_ASSERT((deletions_ == nullptr
                || deletions_->find(position_) == deletions_->end()
                || (failed_deletion_->first
                    && position_ == failed_deletion_->second)));
    return (*entries_)[position_];
  }

  //--------------------------------------------------------------------
  // operator-eq
  //--------------------------------------------------------------------

public:

  bool
  operator==(generic_socket_poll_set_iterator const & other) const {
    {
      bool const same_set = failed_deletion_ == other.failed_deletion_;
      // clang-format off
      SST_ASSERT("Iterators from different sets cannot be compared." && (same_set));
      // clang-format on
    }
    return position_ == other.position_;
  }

  //--------------------------------------------------------------------
  // operator-ne
  //--------------------------------------------------------------------

public:

  bool
  operator!=(generic_socket_poll_set_iterator const & other) const {
    return !(*this == other);
  }

  //--------------------------------------------------------------------
  // operator-post-inc
  //--------------------------------------------------------------------

public:

  generic_socket_poll_set_iterator operator++(int) {
    generic_socket_poll_set_iterator const prev = *this;
    ++(*this);
    return prev;
  }

  //--------------------------------------------------------------------
  // operator-pre-inc
  //--------------------------------------------------------------------

public:

  generic_socket_poll_set_iterator & operator++() {
    SST_ASSERT((entries_ != nullptr));
    SST_ASSERT((position_ < entries_size_));
    size_type i = position_;
    ++i;
    i = skip_deletions(i);
    position_ = i;
    return *this;
  }

  //--------------------------------------------------------------------
  // position_
  //--------------------------------------------------------------------

private:

  size_type position_;

  //--------------------------------------------------------------------
  // skip_deletions
  //--------------------------------------------------------------------

private:

  size_type skip_deletions(size_type i) {
    SST_ASSERT((i <= entries_size_));
    while (i < entries_size_ && deletions_ != nullptr
           && deletions_->find(i) != deletions_->end()
           && (!failed_deletion_->first
               || i != failed_deletion_->second)) {
      ++i;
    }
    return i;
  }

  //--------------------------------------------------------------------
};

} // namespace guts
} // namespace sst

#endif // SST_PRIVATE_GUTS_GENERIC_SOCKET_POLL_SET_ITERATOR_HPP
