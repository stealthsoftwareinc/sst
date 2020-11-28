//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

// Include first to test independence.
#include <sst/time.h>
// Include twice to test idempotence.
#include <sst/time.h>

#include <chrono>
#include <ctime>
#include <mutex>
#include <sst/config.h>
#include <stdexcept>
#include <string>

#if SST_HAVE_POSIX
#include <time.h>
#endif

namespace sst {

//----------------------------------------------------------------------

namespace {

std::mutex mutex;

}; // namespace

//----------------------------------------------------------------------

std::tm gmtime(std::time_t const src) {
  std::tm dst;
#if SST_HAVE_POSIX
  if (::gmtime_r(&src, &dst) == nullptr) {
    throw std::runtime_error("::gmtime_r() failed");
  }
#else
  std::lock_guard<decltype(mutex)> const lock(mutex);
  std::tm const * const p = std::gmtime(&src);
  if (p == nullptr) {
    throw std::runtime_error("std::gmtime() failed");
  }
  dst = *p;
#endif
  return dst;
}

//----------------------------------------------------------------------

std::tm localtime(std::time_t const src) {
  std::tm dst;
#if SST_HAVE_POSIX
  if (::localtime_r(&src, &dst) == nullptr) {
    throw std::runtime_error("::localtime_r() failed");
  }
#else
  std::lock_guard<decltype(mutex)> const lock(mutex);
  std::tm const * const p = std::localtime(&src);
  if (p == nullptr) {
    throw std::runtime_error("std::localtime() failed");
  }
  dst = *p;
#endif
  return dst;
}

//----------------------------------------------------------------------

std::string asctime(std::tm const & src) {
  std::string dst;
#if SST_HAVE_POSIX
  char buf[26];
  if (::asctime_r(&src, buf) == nullptr) {
    throw std::runtime_error("::asctime_r() failed");
  }
  dst = buf;
#else
  std::lock_guard<decltype(mutex)> const lock(mutex);
  char const * const p = std::asctime(&src);
  if (p == nullptr) {
    throw std::runtime_error("std::asctime() failed");
  }
  dst = *p;
#endif
  return dst;
}

//----------------------------------------------------------------------

std::string ctime(std::time_t const src) {
  std::string dst;
#if SST_HAVE_POSIX
  char buf[26];
  if (::ctime_r(&src, buf) == nullptr) {
    throw std::runtime_error("::ctime_r() failed");
  }
  dst = buf;
#else
  std::lock_guard<decltype(mutex)> const lock(mutex);
  char const * const p = std::ctime(&src);
  if (p == nullptr) {
    throw std::runtime_error("std::ctime() failed");
  }
  dst = *p;
#endif
  return dst;
}

//----------------------------------------------------------------------
// sst::mono_time
//----------------------------------------------------------------------

std::once_flag mono_time_flag;

decltype(std::chrono::steady_clock::now()) mono_time_t0;

//----------------------------------------------------------------------

} // namespace sst
