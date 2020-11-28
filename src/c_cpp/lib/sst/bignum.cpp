//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#include <sst/config.h>

#if SST_HAVE_LIB_CRYPTO

#include <sst/catalog/bignum.hpp>
#include <utility>
#include <vector>

namespace sst {

namespace detail {

std::vector<detail::bignum_ptr_t> & bignum_pool() noexcept {
  static thread_local std::vector<detail::bignum_ptr_t> x;
  return x;
}

detail::bignum_bn_ctx_t & bignum_bn_ctx() noexcept {
  static thread_local detail::bignum_bn_ctx_t x;
  return x;
}

namespace {

thread_local std::vector<std::vector<unsigned char>> buffer_pool;

std::vector<unsigned char> acquire_buffer() {
  if (buffer_pool.empty()) {
    return std::vector<unsigned char>();
  }
  std::vector<unsigned char> buffer(std::move(buffer_pool.back()));
  buffer_pool.pop_back();
  return buffer;
}

void release_buffer(std::vector<unsigned char> && buffer) noexcept {
  buffer_pool.push_back(std::move(buffer));
}

} // namespace

buffer_t::buffer_t() : buffer(acquire_buffer()) {
}

buffer_t::~buffer_t() noexcept {
  release_buffer(std::move(buffer));
}

} // namespace detail

} // namespace sst

#endif // SST_HAVE_LIB_CRYPTO
