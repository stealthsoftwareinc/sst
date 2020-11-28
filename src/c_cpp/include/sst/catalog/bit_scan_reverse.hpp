//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_BIT_SCAN_REVERSE_HPP
#define SST_CATALOG_BIT_SCAN_REVERSE_HPP

#include <cassert>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/type_max.hpp>
#include <sst/catalog/value_bits.hpp>
#include <sst/catalog/width_bits.hpp>
#include <sst/config.h>
#include <type_traits>

#if SST_HAVE_X86
#include <x86intrin.h>
#endif

namespace sst {

namespace _ {
namespace bit_scan_reverse {

template<class, class = void>
struct can_use_x86_intrinsic : std::false_type {};

template<class T>
struct can_use_x86_intrinsic<
    T,
    typename std::enable_if<SST_HAVE_X86 && std::is_integral<T>::value
                            && (sst::width_bits<T>::value <= 32)>::type>
    : std::true_type {};

template<class T>
int fallback(T const & x) {
  assert(x != static_cast<T>(0));
  if (sst::is_negative(x)) {
    return sst::width_bits<T>::value - 1;
  }
  T m = sst::type_max<T>::value >> 1;
  int i = sst::value_bits<T>::value - 1;
  while ((x & m) == x) {
    m >>= 1;
    --i;
  }
  return i;
}

}; // namespace bit_scan_reverse
}; // namespace _

template<class T,
         typename std::enable_if<
             sst::_::bit_scan_reverse::can_use_x86_intrinsic<T>::value
                 && (sst::width_bits<T>::value == 32),
             int>::type = 0>
int bit_scan_reverse(T const x) noexcept {
  assert(x != static_cast<T>(0));
  return _bit_scan_reverse(static_cast<int>(x));
}

template<class T,
         typename std::enable_if<
             sst::_::bit_scan_reverse::can_use_x86_intrinsic<T>::value
                 && (sst::width_bits<T>::value < 32),
             int>::type = 0>
int bit_scan_reverse(T const x) noexcept {
  assert(x != static_cast<T>(0));
  if (sst::is_negative(x)) {
    return sst::width_bits<T>::value - 1;
  }
  return _bit_scan_reverse(static_cast<int>(x));
}

template<class T,
         typename std::enable_if<
             !sst::_::bit_scan_reverse::can_use_x86_intrinsic<T>::value,
             int>::type = 0>
int bit_scan_reverse(T const & x) {
  return sst::_::bit_scan_reverse::fallback(x);
}

} // namespace sst

#endif // SST_CATALOG_BIT_SCAN_REVERSE_HPP
