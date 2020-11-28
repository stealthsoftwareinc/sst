//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

// Include first to test independence.
#include <sst/catalog/mkdir_p.hpp>
// Include twice to test idempotence.
#include <sst/catalog/mkdir_p.hpp>

#include <sst/config.h>

//----------------------------------------------------------------------
// POSIX
//----------------------------------------------------------------------
#if SST_HAVE_POSIX

#include <errno.h>
#include <sst/fs/error.h>
#include <string>
#include <sys/stat.h>

namespace sst {

//
// Algorithm: For each successive initial strict substring of the path
// that ends in a nonslash and whose following character is a slash,
// call mkdir on that substring. Then call mkdir on the full path.
//
// It's technically possible to omit the final mkdir call in certain
// cases, but it feels dishonest to do so.
//
// POSIX says that "A pathname that begins with two successive slashes
// may be interpreted in an implementation-defined manner, although more
// than two leading slashes shall be treated as a single slash.", but we
// don't cater to this whatsoever.
//

namespace {

//
// Find the next initial strict substring of the path that ends in a
// nonslash and whose following character is a slash, where pos is the
// position of the slash that followed the previous such substring. If
// pos is not given, find the first such substring. Return the position
// of the slash that follows the newly found substring, or npos if none
// is found.
//

std::string::size_type
posix_next(std::string const & path, std::string::size_type pos = 0) {
  do {
    pos = path.find('/', pos + 1);
  } while (pos != path.npos && path[pos - 1] == '/');
  return pos;
}

//
// Do an individual mkdir call.
//

bool posix_step(char const * const path) {
  if (mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO) == 0) {
    return true;
  }
  int const e1 = errno;
  if (e1 != EEXIST) {
    throw fs::error("mkdir() failed with errno = " + std::to_string(e1));
  }
  struct stat st;
  if (stat(path, &st) != 0) {
    int const e2 = errno;
    throw fs::error("stat() failed with errno = " + std::to_string(e2));
  }
  if (st.st_mode & S_IFDIR) {
    return false;
  }
  throw fs::error("file already exists but is not a directory");
}

} // namespace

bool mkdir_p(std::string const & path) {
  bool r = false;
  std::string::size_type i = posix_next(path);
  if (i != path.npos) {
    std::string p = path;
    do {
      p[i] = 0;
      r |= posix_step(p.c_str());
      p[i] = '/';
      i = posix_next(path, i);
    } while (i != path.npos);
  }
  r |= posix_step(path.c_str());
  return r;
}

} // namespace sst

//----------------------------------------------------------------------
// Windows
//----------------------------------------------------------------------
#elif SST_HAVE_WINDOWS

#include <sst/fs/error.h>
#include <string>
#include <windows.h>

namespace sst {

namespace {

std::string::size_type windows_next(std::string const & path,
                                    std::string::size_type pos = 0) {
  while (++pos < path.size()) {
    if (path[pos] == '/' || path[pos] == '\\') {
      if (path[pos - 1] != '/' && path[pos - 1] != '\\') {
        break;
      }
    }
  }
  if (pos >= path.size()) {
    pos = path.npos;
  }
  return pos;
}

bool windows_step(std::string const & path) {
  if (path.size() == 2 && path[1] == ':') {
    // C:
    return true;
  }
  if (path == "\\\\?") {
    // \\?
    return true;
  }
  if (path.size() == 6 && path[0] == '\\' && path[1] == '\\'
      && path[2] == '?' && path[3] == '\\' && path[5] == ':') {
    // \\?\C:
    return true;
  }
  if (path == "\\\\?\\UNC") {
    // \\?\UNC
    return true;
  }
  if (CreateDirectoryA(path.c_str(), nullptr) != 0) {
    return true;
  }
  DWORD const e = GetLastError();
  if (e == ERROR_ALREADY_EXISTS) {
    return false;
  }
  throw fs::error("CreateDirectoryA failed");
}

} // namespace

bool mkdir_p(std::string const & path) {
  bool r = false;
  std::string::size_type i = windows_next(path);
  if (i != path.npos) {
    std::string p = path;
    do {
      auto const x = p[i];
      p[i] = 0;
      r |= windows_step(p);
      p[i] = x;
      i = windows_next(path, i);
    } while (i != path.npos);
  }
  r |= windows_step(path);
  return r;
}

} // namespace sst

#endif
