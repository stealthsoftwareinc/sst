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

#ifndef SST_CATALOG_POSIX_DIR_IT_HPP
#define SST_CATALOG_POSIX_DIR_IT_HPP

#include <sst/catalog/SST_WITH_POSIX.h>

#if SST_WITH_POSIX

#include <cstddef>
#include <iterator>
#include <memory>
#include <stack>
#include <string>

#include <sst/catalog/dir_it_options.hpp>
#include <sst/catalog/posix_path.hpp>
#include <sst/catalog/posix_readdir.hpp>

namespace sst {

class posix_dir_it {

  //--------------------------------------------------------------------
  // begin
  //--------------------------------------------------------------------
  //
  // Returns a copy of this iterator.
  //
  // Q: Why do we have this function? Isn't this class an iterator, not
  //    an iterable collection?
  // A: Because it's convenient. For example, this function (along with
  //    the end() function) lets us write range-based for loops like
  //    for (auto & path : sst::posix_dir_it(".")).
  //

public:

  posix_dir_it begin() const;

  //--------------------------------------------------------------------
  // construct-end
  //--------------------------------------------------------------------
  //
  // Constructs an end sentinel.
  //
  // When a directory iterator is iterated one past its last value, it
  // becomes an end sentinel. End sentinels compare equal to each other,
  // and unequal to iterators that have not yet become end sentinels.
  //

public:

  posix_dir_it() noexcept {
  }

  //--------------------------------------------------------------------
  // construct-from-byte-pointer
  //--------------------------------------------------------------------

private:

  struct construct_from_byte_pointer_tag {};

  explicit posix_dir_it(construct_from_byte_pointer_tag,
                        char const * path,
                        sst::dir_it_options const & options = {});

public:

  template<class Byte, sst::enable_if_t<sst::is_byte<Byte>::value> = 0>
  explicit posix_dir_it(Byte const * const path,
                        sst::dir_it_options const & options = {})
      : posix_dir_it(construct_from_byte_pointer_tag(),
                     reinterpret_cast<char const *>(path),
                     options) {
  }

  //--------------------------------------------------------------------
  // ctor-vaor3p41
  //--------------------------------------------------------------------

public:

  explicit posix_dir_it(std::string const & dir,
                        sst::dir_it_options const & options = {});

  //--------------------------------------------------------------------
  // copy-assign
  //--------------------------------------------------------------------

public:

  posix_dir_it & operator=(posix_dir_it const & other);

  //--------------------------------------------------------------------
  // copy-construct
  //--------------------------------------------------------------------

public:

  posix_dir_it(posix_dir_it const & other);

  //--------------------------------------------------------------------
  // destruct
  //--------------------------------------------------------------------

public:

  ~posix_dir_it() noexcept;

  //--------------------------------------------------------------------
  // difference_type
  //--------------------------------------------------------------------

public:

  using difference_type = std::ptrdiff_t;

  //--------------------------------------------------------------------
  // end
  //--------------------------------------------------------------------
  //
  // Returns an end sentinel.
  //
  // When a directory iterator is iterated one past its last value, it
  // becomes an end sentinel. End sentinels compare equal to each other,
  // and unequal to iterators that have not yet become end sentinels.
  //
  // Q: Why do we have this function? Isn't this class an iterator, not
  //    an iterable collection?
  // A: Because it's convenient. For example, this function (along with
  //    the begin() function) lets us write range-based for loops like
  //    for (auto & path : sst::posix_dir_it(".")).
  //

public:

  static posix_dir_it end();

  //--------------------------------------------------------------------
  // iterator_category
  //--------------------------------------------------------------------

public:

  using iterator_category = std::input_iterator_tag;

  //--------------------------------------------------------------------
  // move-assign
  //--------------------------------------------------------------------
  //
  // Q: What happens to the other iterator?
  // A: It becomes an end sentinel.
  //

public:

  posix_dir_it & operator=(posix_dir_it && other) noexcept;

  //--------------------------------------------------------------------
  // move-construct
  //--------------------------------------------------------------------
  //
  // Q: What happens to the other iterator?
  // A: It becomes an end sentinel.
  //

public:

  posix_dir_it(posix_dir_it && other) noexcept;

  //--------------------------------------------------------------------
  // operator-arrow
  //--------------------------------------------------------------------
  //
  // Q: Why does this function always return a pointer to non-const?
  // A: See operator-deref.
  //


public:

  sst::posix_path * operator->() const;

  //--------------------------------------------------------------------
  // operator-deref
  //--------------------------------------------------------------------
  //
  // Q: Why does this function always return a reference to non-const?
  // A: For efficiency opportunities. Each iterator keeps its own cached
  //    copy of the current path of the walk (path_), and you can freely
  //    modify the cached copy without being forced to copy it yourself.
  //    For example, you could std::move it elsewhere. The cached copy
  //    will be overwritten each time the iterator is incremented. The
  //    constness of the iterator does not affect the constness of the
  //    cached copy. The cached copy is always non-const.
  //

public:

  sst::posix_path & operator*() const;

  //--------------------------------------------------------------------
  // operator-eq
  //--------------------------------------------------------------------

public:

  bool operator==(posix_dir_it const & other) const;

  //--------------------------------------------------------------------
  // operator-ne
  //--------------------------------------------------------------------

public:

  bool operator!=(posix_dir_it const & other) const;

  //--------------------------------------------------------------------
  // operator-post-inc
  //--------------------------------------------------------------------

public:

  posix_dir_it operator++(int);

  //--------------------------------------------------------------------
  // operator-pre-inc
  //--------------------------------------------------------------------

public:

  posix_dir_it & operator++();

  //--------------------------------------------------------------------
  // path_
  //--------------------------------------------------------------------

private:

  std::unique_ptr<sst::posix_path> path_;

  //--------------------------------------------------------------------
  // pointer
  //--------------------------------------------------------------------

public:

  using pointer = sst::posix_path *;

  //--------------------------------------------------------------------
  // prefix
  //--------------------------------------------------------------------
  //
  // Returns the number of initial characters in the current path that
  // are part of the directory path this iterator was constructed with,
  // including an additional slash, if necessary.
  //
  // For example:
  //
  //       sst::posix_dir_it("foo").prefix() -> 4
  //       sst::posix_dir_it("foo/").prefix() -> 4
  //       sst::posix_dir_it("foo//").prefix() -> 5
  //       sst::posix_dir_it("foo///").prefix() -> 6
  //
  // This value never changes and is guaranteed to be positive.
  //
  // It is invalid to call this function on an end sentinel, even if the
  // end sentinel was previously not an end sentinel.
  //

private:

  std::string::size_type prefix_ = 0;

public:

  std::string::size_type prefix() const;

  //--------------------------------------------------------------------
  // reference
  //--------------------------------------------------------------------

public:

  using reference = sst::posix_path &;

  //--------------------------------------------------------------------
  // shared_
  //--------------------------------------------------------------------

private:

  struct stack_entry_t {
    sst::posix_readdir readdir;
    std::string::size_type step;
    explicit stack_entry_t(std::string const & dir,
                           std::string::size_type const step)
        : readdir(dir.c_str()),
          step(step) {
    }
  };

  struct data_t {
    sst::dir_it_options options;
    std::stack<stack_entry_t> stack;
    std::string path;
  };

  std::shared_ptr<data_t> shared_;

  //--------------------------------------------------------------------
  // value_type
  //--------------------------------------------------------------------

public:

  using value_type = sst::posix_path;

  //--------------------------------------------------------------------
};

} // namespace sst

#endif // #if SST_WITH_POSIX

#endif // SST_CATALOG_POSIX_DIR_IT_HPP
