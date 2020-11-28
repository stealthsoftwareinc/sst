//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

// Include first to test independence.
#include <sst/fs/isdir.h>
// Include twice to test idempotence.
#include <sst/fs/isdir.h>

#include <sst/SST_HAVE_POSIX.h>

#if SST_HAVE_POSIX

#include <errno.h>
#include <sst/fs/error.h>
#include <string>
#include <sys/stat.h>

namespace sst {
namespace fs {

bool isdir(std::string const & path) {
  struct stat st;
  if (stat(path.c_str(), &st) == 0) {
    return S_ISDIR(st.st_mode);
  }
  int const e = errno;
  if (e == ENOENT || e == ENOTDIR) {
    return false;
  }
  throw error("stat() failed with errno = " + std::to_string(e));
}

} // namespace fs
} // namespace sst

#endif // SST_HAVE_POSIX
