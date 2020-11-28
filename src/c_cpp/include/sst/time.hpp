//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_TIME_HPP
#define SST_TIME_HPP

#include <chrono>
#include <ctime>
#include <mutex>
#include <sst/catalog/SST_PUBLIC_CPP_FUNCTION.hpp>
#include <sst/catalog/SST_PUBLIC_CPP_OBJECT.hpp>
#include <stdexcept>
#include <string>

namespace sst {

//----------------------------------------------------------------------
// sst::time
//----------------------------------------------------------------------

inline std::time_t time() {
  std::time_t const t = std::time(nullptr);
  if (t == static_cast<std::time_t>(-1)) {
    throw std::runtime_error("std::time failed");
  }
  return t;
}

//----------------------------------------------------------------------
// sst::gmtime
//----------------------------------------------------------------------

SST_PUBLIC_CPP_FUNCTION
std::tm gmtime(std::time_t src);

inline std::tm gmtime() {
  return gmtime(time());
}

//----------------------------------------------------------------------
// sst::localtime
//----------------------------------------------------------------------

SST_PUBLIC_CPP_FUNCTION
std::tm localtime(std::time_t src);

inline std::tm localtime() {
  return localtime(time());
}

//----------------------------------------------------------------------
// sst::asctime
//----------------------------------------------------------------------

SST_PUBLIC_CPP_FUNCTION
std::string asctime(std::tm const & src);

inline std::string asctime() {
  return asctime(localtime());
}

//----------------------------------------------------------------------
// sst::ctime
//----------------------------------------------------------------------

SST_PUBLIC_CPP_FUNCTION
std::string ctime(std::time_t src);

inline std::string ctime() {
  return ctime(time());
}

//----------------------------------------------------------------------
// sst::unix_time
//----------------------------------------------------------------------

template<class Duration = std::chrono::seconds>
typename Duration::rep unix_time() {
  return std::chrono::duration_cast<Duration>(
             std::chrono::system_clock::now().time_since_epoch())
      .count();
}

//----------------------------------------------------------------------
// sst::unix_time_s
//----------------------------------------------------------------------

inline std::chrono::seconds::rep unix_time_s() {
  return unix_time<std::chrono::seconds>();
}

//----------------------------------------------------------------------
// sst::unix_time_ms
//----------------------------------------------------------------------

inline std::chrono::milliseconds::rep unix_time_ms() {
  return unix_time<std::chrono::milliseconds>();
}

//----------------------------------------------------------------------
// sst::unix_time_us
//----------------------------------------------------------------------

inline std::chrono::microseconds::rep unix_time_us() {
  return unix_time<std::chrono::microseconds>();
}

//----------------------------------------------------------------------
// sst::unix_time_ns
//----------------------------------------------------------------------

inline std::chrono::nanoseconds::rep unix_time_ns() {
  return unix_time<std::chrono::nanoseconds>();
}

//----------------------------------------------------------------------
// sst::unix_time_d
//----------------------------------------------------------------------

inline double unix_time_d() {
  return unix_time_ns() / 1000000000.0;
}

//----------------------------------------------------------------------
// sst::mono_time
//----------------------------------------------------------------------

SST_PUBLIC_CPP_OBJECT
std::once_flag mono_time_flag;

SST_PUBLIC_CPP_OBJECT
decltype(std::chrono::steady_clock::now()) mono_time_t0;

template<class Duration>
typename Duration::rep mono_time() {
  std::call_once(mono_time_flag, [] {
    mono_time_t0 = std::chrono::steady_clock::now();
  });
  return std::chrono::duration_cast<Duration>(
             std::chrono::steady_clock::now() - mono_time_t0)
      .count();
}

//----------------------------------------------------------------------
// sst::mono_time_s
//----------------------------------------------------------------------

inline std::chrono::seconds::rep mono_time_s() {
  return mono_time<std::chrono::seconds>();
}

//----------------------------------------------------------------------
// sst::mono_time_ms
//----------------------------------------------------------------------

inline std::chrono::milliseconds::rep mono_time_ms() {
  return mono_time<std::chrono::milliseconds>();
}

//----------------------------------------------------------------------
// sst::mono_time_us
//----------------------------------------------------------------------

inline std::chrono::microseconds::rep mono_time_us() {
  return mono_time<std::chrono::microseconds>();
}

//----------------------------------------------------------------------
// sst::mono_time_ns
//----------------------------------------------------------------------

inline std::chrono::nanoseconds::rep mono_time_ns() {
  return mono_time<std::chrono::nanoseconds>();
}

//----------------------------------------------------------------------
// sst::mono_time_d
//----------------------------------------------------------------------

inline double mono_time_d() {
  return mono_time_ns() / 1000000000.0;
}

//----------------------------------------------------------------------

} // namespace sst

#endif // SST_TIME_HPP
