//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_VALUE_BOX_HPP
#define SST_CATALOG_VALUE_BOX_HPP

#include <sst/catalog/SST_CPP_CONSTEXPR.hpp>
#include <utility>

namespace sst {

template<class T, class>
class boxed {
  T value_;

public:
  using value_type = T;

  // Construction is forwarded to T.
  template<class... Args>
  explicit boxed(Args &&... args) noexcept(
      noexcept(T(std::forward<Args>(args)...)))
      : value_(std::forward<Args>(args)...) {
  }

  // Copy construction and assignment are intentionally implicit.
  // Move construction and assignment are intentionally implicit.
  // Destruction is intentionally implicit.

  // Value retrieval.
  explicit SST_CPP14_CONSTEXPR operator T &() noexcept {
    return value_;
  }
  explicit constexpr operator T const &() const noexcept {
    return value_;
  }
  SST_CPP14_CONSTEXPR T & value() noexcept {
    return value_;
  }
  constexpr T const & value() const noexcept {
    return value_;
  }
};

} // namespace sst

#endif // SST_CATALOG_VALUE_BOX_HPP
