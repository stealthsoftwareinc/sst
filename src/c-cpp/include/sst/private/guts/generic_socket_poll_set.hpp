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

#ifndef SST_PRIVATE_GUTS_GENERIC_SOCKET_POLL_SET_HPP
#define SST_PRIVATE_GUTS_GENERIC_SOCKET_POLL_SET_HPP

#include <functional>
#include <memory>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>

#include <sst/catalog/SST_WITH_POSIX.h>
#include <sst/catalog/SST_WITH_WINDOWS_WS2_32.h>
#include <sst/catalog/basic_ptr.hpp>
#include <sst/catalog/posix_socket.hpp>
#include <sst/catalog/posix_socket_poll_set_entry.hpp>
#include <sst/catalog/windows_socket.hpp>
#include <sst/catalog/windows_socket_poll_set_entry.hpp>
#include <sst/private/SST_DLL_EXPORT.h>
#include <sst/private/guts/generic_socket_poll_set_iterator.hpp>

namespace sst {
namespace guts {

template<class Socket, class Entry>
class generic_socket_poll_set final {

  //--------------------------------------------------------------------
  // iterator
  //--------------------------------------------------------------------

public:

  using iterator = sst::guts::generic_socket_poll_set_iterator<Entry>;

  //--------------------------------------------------------------------
  // begin
  //--------------------------------------------------------------------

public:

  iterator begin() const;

  //--------------------------------------------------------------------
  // consolidate
  //--------------------------------------------------------------------

public:

  void consolidate();

  //--------------------------------------------------------------------
  // consolidate_helper
  //--------------------------------------------------------------------

private:

  template<class Pfd>
  void consolidate_helper();

  //--------------------------------------------------------------------
  // construct-empty
  //--------------------------------------------------------------------

public:

  generic_socket_poll_set() noexcept;

  //--------------------------------------------------------------------
  // copy-assign
  //--------------------------------------------------------------------

public:

  generic_socket_poll_set &
  operator=(generic_socket_poll_set const & other) = delete;

  //--------------------------------------------------------------------
  // copy-construct
  //--------------------------------------------------------------------

public:

  generic_socket_poll_set(generic_socket_poll_set const & other) =
      delete;

  //--------------------------------------------------------------------
  // destruct
  //--------------------------------------------------------------------

public:

  ~generic_socket_poll_set() noexcept;

  //--------------------------------------------------------------------
  // end
  //--------------------------------------------------------------------

public:

  iterator end() const;

  //--------------------------------------------------------------------
  // entries_
  //--------------------------------------------------------------------

private:

  std::unique_ptr<std::vector<Entry>> entries_ = nullptr;

  //--------------------------------------------------------------------
  // size_type
  //--------------------------------------------------------------------
  //
  // We use the size_type of entries_ as our size_type. This type has
  // sufficient range because entries_ becomes the same size as pfds_
  // after consolidate().
  //

public:

  using size_type = decltype(entries_->size());

  //--------------------------------------------------------------------
  // entries_size_
  //--------------------------------------------------------------------

private:

  size_type entries_size_ = 0;

  //--------------------------------------------------------------------
  // deletions_
  //--------------------------------------------------------------------
  //
  // The indexes of pfds_ that have been marked as deleted. The
  // consolidate() algorithm requires that this set is ordered
  // descendingly.
  //

private:

  std::unique_ptr<std::set<size_type, std::greater<size_type>>>
      deletions_ = nullptr;

  //--------------------------------------------------------------------
  // erase-entry
  //--------------------------------------------------------------------

public:

  void erase(Entry const * entry);

  //--------------------------------------------------------------------
  // erase-iterator
  //--------------------------------------------------------------------

public:

  void erase(iterator it);

  //--------------------------------------------------------------------
  // erase-socket
  //--------------------------------------------------------------------

public:

  void erase(Socket const * socket);

  //--------------------------------------------------------------------
  // erase_helper-entry
  //--------------------------------------------------------------------

private:

  template<class Pfd>
  void erase_helper(Entry const & entry);

  //--------------------------------------------------------------------
  // erase_helper-socket
  //--------------------------------------------------------------------

private:

  template<class Pfd>
  void erase_helper(Socket const & socket);

  //--------------------------------------------------------------------
  // erase_pfd
  //--------------------------------------------------------------------

private:

  static void erase_pfd(void * pfd) noexcept;

  //--------------------------------------------------------------------
  // failed_deletion_
  //--------------------------------------------------------------------

private:

  std::pair<bool, size_type> failed_deletion_ = {false, 0};

  //--------------------------------------------------------------------
  // initialize_pfd
  //--------------------------------------------------------------------

private:

  void initialize_pfd(void * pfd, Socket & socket);

  //--------------------------------------------------------------------
  // insert
  //--------------------------------------------------------------------

public:

  void insert(Socket * socket);

  //--------------------------------------------------------------------
  // insert_helper
  //--------------------------------------------------------------------

private:

  template<class Pfd>
  void insert_helper(Socket & socket);

  //--------------------------------------------------------------------
  // move-assign
  //--------------------------------------------------------------------

public:

  generic_socket_poll_set &
  operator=(generic_socket_poll_set && other) = delete;

  //--------------------------------------------------------------------
  // move-construct
  //--------------------------------------------------------------------

public:

  generic_socket_poll_set(generic_socket_poll_set && other) = delete;

  //--------------------------------------------------------------------
  // new_entries_
  //--------------------------------------------------------------------

private:

  std::unique_ptr<std::vector<Entry>> new_entries_ = nullptr;

  //--------------------------------------------------------------------
  // new_entries_size_
  //--------------------------------------------------------------------

private:

  size_type new_entries_size_ = 0;

  //--------------------------------------------------------------------
  // pfds_
  //--------------------------------------------------------------------
  //
  // This is the array that will be passed to the underlying system's
  // poll function.
  //
  // We use a void pointer to help prevent this header file from
  // requiring any system headers, which helps reduce compilation
  // difficulties. In the implementation files, we'll convert the
  // pointer to the proper type as needed.
  //

private:

  sst::basic_ptr<void> pfds_ = nullptr;

  //--------------------------------------------------------------------
  // pfds_size_
  //--------------------------------------------------------------------

private:

  size_type pfds_size_ = 0;

  //--------------------------------------------------------------------
  // poll-with-timeout
  //--------------------------------------------------------------------

public:

  template<class Duration>
  size_type poll(Duration const & timeout);

  //--------------------------------------------------------------------
  // poll-without-timeout
  //--------------------------------------------------------------------

public:

  size_type poll();

  //--------------------------------------------------------------------
  // poll_helper
  //--------------------------------------------------------------------

private:

  size_type poll_helper(int timeout);

  //--------------------------------------------------------------------
  // positions_
  //--------------------------------------------------------------------

private:

  std::unique_ptr<std::unordered_map<Socket const *, size_type>>
      positions_ = nullptr;

  //--------------------------------------------------------------------
  // recover_after_exception
  //--------------------------------------------------------------------
  //
  // Performs any recovery needed after an exception has been thrown by
  // any function, including itself. This function should be called at
  // the beginning of every function, except itself.
  //

private:

  void recover_after_exception();

  //--------------------------------------------------------------------
  // recover_after_exception_helper
  //--------------------------------------------------------------------

private:

  template<class Pfd>
  void recover_after_exception_helper();

  //--------------------------------------------------------------------
};

//----------------------------------------------------------------------
// Forward declarations for consolidate
//----------------------------------------------------------------------

#if SST_WITH_POSIX

template<>
SST_DLL_EXPORT void generic_socket_poll_set<
    sst::posix_socket,
    sst::posix_socket_poll_set_entry>::consolidate();

#endif

#if SST_WITH_WINDOWS_WS2_32

template<>
SST_DLL_EXPORT void generic_socket_poll_set<
    sst::windows_socket,
    sst::windows_socket_poll_set_entry>::consolidate();

#endif

//----------------------------------------------------------------------
// Forward declarations for construct-empty
//----------------------------------------------------------------------

#if SST_WITH_POSIX

template<>
SST_DLL_EXPORT
generic_socket_poll_set<sst::posix_socket,
                        sst::posix_socket_poll_set_entry>::
    generic_socket_poll_set() noexcept;

#endif

#if SST_WITH_WINDOWS_WS2_32

template<>
SST_DLL_EXPORT
generic_socket_poll_set<sst::windows_socket,
                        sst::windows_socket_poll_set_entry>::
    generic_socket_poll_set() noexcept;

#endif

//----------------------------------------------------------------------
// Forward declarations for erase-entry
//----------------------------------------------------------------------

#if SST_WITH_POSIX

template<>
SST_DLL_EXPORT void
generic_socket_poll_set<sst::posix_socket,
                        sst::posix_socket_poll_set_entry>::
    erase(sst::posix_socket_poll_set_entry const * entry);

#endif

#if SST_WITH_WINDOWS_WS2_32

template<>
SST_DLL_EXPORT void
generic_socket_poll_set<sst::windows_socket,
                        sst::windows_socket_poll_set_entry>::
    erase(sst::windows_socket_poll_set_entry const * entry);

#endif

//----------------------------------------------------------------------
// Forward declarations for erase-socket
//----------------------------------------------------------------------

#if SST_WITH_POSIX

template<>
SST_DLL_EXPORT void
generic_socket_poll_set<sst::posix_socket,
                        sst::posix_socket_poll_set_entry>::
    erase(sst::posix_socket const * socket);

#endif

#if SST_WITH_WINDOWS_WS2_32

template<>
SST_DLL_EXPORT void
generic_socket_poll_set<sst::windows_socket,
                        sst::windows_socket_poll_set_entry>::
    erase(sst::windows_socket const * socket);

#endif

//----------------------------------------------------------------------
// Forward declarations for erase_pfd
//----------------------------------------------------------------------

#if SST_WITH_POSIX

template<>
SST_DLL_EXPORT void generic_socket_poll_set<
    sst::posix_socket,
    sst::posix_socket_poll_set_entry>::erase_pfd(void * pfd) noexcept;

#endif

#if SST_WITH_WINDOWS_WS2_32

template<>
SST_DLL_EXPORT void generic_socket_poll_set<
    sst::windows_socket,
    sst::windows_socket_poll_set_entry>::erase_pfd(void * pfd) noexcept;

#endif

//----------------------------------------------------------------------
// Forward declarations for initialize_pfd
//----------------------------------------------------------------------

#if SST_WITH_POSIX

template<>
SST_DLL_EXPORT void
generic_socket_poll_set<sst::posix_socket,
                        sst::posix_socket_poll_set_entry>::
    initialize_pfd(void * pfd, sst::posix_socket & socket);

#endif

#if SST_WITH_WINDOWS_WS2_32

template<>
SST_DLL_EXPORT void
generic_socket_poll_set<sst::windows_socket,
                        sst::windows_socket_poll_set_entry>::
    initialize_pfd(void * pfd, sst::windows_socket & socket);

#endif

//----------------------------------------------------------------------
// Forward declarations for insert
//----------------------------------------------------------------------

#if SST_WITH_POSIX

template<>
SST_DLL_EXPORT void
generic_socket_poll_set<sst::posix_socket,
                        sst::posix_socket_poll_set_entry>::
    insert(sst::posix_socket * socket);

#endif

#if SST_WITH_WINDOWS_WS2_32

template<>
SST_DLL_EXPORT void
generic_socket_poll_set<sst::windows_socket,
                        sst::windows_socket_poll_set_entry>::
    insert(sst::windows_socket * socket);

#endif

//----------------------------------------------------------------------
// Forward declarations for poll_helper
//----------------------------------------------------------------------

#if SST_WITH_POSIX

template<>
SST_DLL_EXPORT
    generic_socket_poll_set<sst::posix_socket,
                            sst::posix_socket_poll_set_entry>::size_type
    generic_socket_poll_set<
        sst::posix_socket,
        sst::posix_socket_poll_set_entry>::poll_helper(int timeout);

#endif

#if SST_WITH_WINDOWS_WS2_32

template<>
SST_DLL_EXPORT generic_socket_poll_set<
    sst::windows_socket,
    sst::windows_socket_poll_set_entry>::size_type
generic_socket_poll_set<
    sst::windows_socket,
    sst::windows_socket_poll_set_entry>::poll_helper(int timeout);

#endif

//----------------------------------------------------------------------
// Forward declarations for recover_after_exception
//----------------------------------------------------------------------

#if SST_WITH_POSIX

template<>
SST_DLL_EXPORT void generic_socket_poll_set<
    sst::posix_socket,
    sst::posix_socket_poll_set_entry>::recover_after_exception();

#endif

#if SST_WITH_WINDOWS_WS2_32

template<>
SST_DLL_EXPORT void generic_socket_poll_set<
    sst::windows_socket,
    sst::windows_socket_poll_set_entry>::recover_after_exception();

#endif

//----------------------------------------------------------------------

} // namespace guts
} // namespace sst

//----------------------------------------------------------------------
// Function definitions
//----------------------------------------------------------------------

#include <sst/private/guts/generic_socket_poll_set/begin.hpp>
#include <sst/private/guts/generic_socket_poll_set/consolidate_helper.hpp>
#include <sst/private/guts/generic_socket_poll_set/destruct.hpp>
#include <sst/private/guts/generic_socket_poll_set/end.hpp>
#include <sst/private/guts/generic_socket_poll_set/erase-iterator.hpp>
#include <sst/private/guts/generic_socket_poll_set/erase_helper-entry.hpp>
#include <sst/private/guts/generic_socket_poll_set/erase_helper-socket.hpp>
#include <sst/private/guts/generic_socket_poll_set/insert_helper.hpp>
#include <sst/private/guts/generic_socket_poll_set/poll-with-timeout.hpp>
#include <sst/private/guts/generic_socket_poll_set/poll-without-timeout.hpp>
#include <sst/private/guts/generic_socket_poll_set/recover_after_exception_helper.hpp>

//----------------------------------------------------------------------

#endif // #ifndef SST_PRIVATE_GUTS_GENERIC_SOCKET_POLL_SET_HPP
