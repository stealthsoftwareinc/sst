#ifndef SST_CATALOG_ELGAMAL_SERIALIZATION_HPP
#define SST_CATALOG_ELGAMAL_SERIALIZATION_HPP

#include <sst/catalog/SST_WITH_OPENSSL_CRYPTO.h>

#if SST_WITH_OPENSSL_CRYPTO

#include <openssl/opensslv.h>

#if OPENSSL_VERSION_NUMBER >= 0x10100000

#include <algorithm>
#include <cstddef>
#include <limits>
#include <stdexcept>
#include <vector>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/bignum.hpp>
#include <sst/catalog/char_bit.hpp>
#include <sst/catalog/char_bit_v.hpp>
#include <sst/catalog/checked.hpp>
#include <sst/catalog/checked_resize.hpp>
#include <sst/catalog/openssl/ec_group.hpp>
#include <sst/catalog/openssl/ec_point.hpp>
#include <sst/catalog/openssl/err_exception.hpp>
#include <sst/catalog/perfect_gt.hpp>

#include <openssl/ec.h>

namespace sst {
namespace elgamal {

constexpr auto point_size_size = 2;
constexpr auto string_size_size = 4;

template<typename Value, typename Size>
inline void serialize_integer(std::vector<unsigned char> & dst,
                              Value src,
                              Size const & size) {
  SST_ASSERT((size > 0));
  SST_ASSERT((src >= 0));
  for (Size i = 0; i < size; ++i) {
    dst.push_back(static_cast<unsigned char>(src));
    src >>= sst::char_bit_v - 1;
    src >>= 1;
  }
  if (src != 0) {
    throw std::runtime_error("serialize_integer overflow");
  }
}

template<typename Value, typename Size>
inline std::vector<unsigned char> serialize_integer(Value src,
                                                    Size const & size) {
  std::vector<unsigned char> dst;
  serialize_integer(dst, src, size);
  return dst;
}

template<typename Value, typename Size>
inline void
deserialize_integer(std::vector<unsigned char> const & src,
                    std::vector<unsigned char>::size_type & idx,
                    Value & dst,
                    Size const & size) {
  SST_ASSERT((size > 0));
  SST_ASSERT((idx >= 0));
  SST_ASSERT((idx < src.size()));
  if (sst::perfect_gt(size, src.size() - idx)) {
    throw std::runtime_error("deserialize corruption");
  }
  dst = 0;
  for (Size i = 0; i < size; ++i) {
    if (std::numeric_limits<Value>::is_bounded) {
      Value max = std::numeric_limits<Value>::max();
      max >>= sst::char_bit_v - 1;
      max >>= 1;
      if (dst > max) {
        throw std::runtime_error("deserialize_integer overflow");
      }
    }
    dst <<= sst::char_bit_v - 1;
    dst <<= 1;
    dst |= static_cast<Value>(src[idx + (size - 1 - i)]);
  }
  idx += size;
}

template<typename Value, typename Size>
inline Value
deserialize_integer(std::vector<unsigned char> const & src,
                    std::vector<unsigned char>::size_type & idx,
                    Size const & size) {
  Value dst;
  deserialize_integer(src, idx, dst, size);
  return dst;
}

template<typename Value, typename Size>
inline void deserialize_integer(std::vector<unsigned char> const & src,
                                Value & dst) {
  std::vector<unsigned char>::size_type idx = 0;
  deserialize_integer(src, idx, dst, src.size());
}

template<typename Value, typename Size>
inline Value
deserialize_integer(std::vector<unsigned char> const & src) {
  Value dst;
  deserialize_integer(src, dst);
  return dst;
}

inline void serialize_point(std::vector<unsigned char> & dst,
                            sst::openssl::ec_point const & src,
                            sst::openssl::ec_group const & group) {
  auto const pcf = EC_GROUP_get_point_conversion_form(group);
  auto const len1 = EC_POINT_point2oct(group,
                                       src,
                                       pcf,
                                       nullptr,
                                       0,
                                       sst::bignum::ctx());
  if (len1 == 0) {
    throw sst::openssl::err_exception("EC_POINT_point2oct()");
  }

  serialize_integer(dst, len1, point_size_size);
  sst::checked_resize(dst, sst::checked(dst.size()) + len1);
  auto const len2 = EC_POINT_point2oct(group,
                                       src,
                                       pcf,
                                       dst.data() + dst.size() - len1,
                                       len1,
                                       sst::bignum::ctx());
  if (len2 == 0) {
    throw sst::openssl::err_exception("EC_POINT_point2oct()");
  }
  SST_ASSERT((len2 == len1));
}

inline std::vector<unsigned char>
serialize_point(sst::openssl::ec_point const & src,
                sst::openssl::ec_group const & group) {
  std::vector<unsigned char> dst;
  serialize_point(dst, src, group);
  return dst;
}

inline void
deserialize_point(std::vector<unsigned char> const & src,
                  std::vector<unsigned char>::size_type & idx,
                  sst::openssl::ec_point & dst,
                  sst::openssl::ec_group const & group) {
  std::size_t len{};
  deserialize_integer(src, idx, len, point_size_size);
  if (len > src.size() - idx) {
    throw std::runtime_error("deserialize corruption");
  }
  if (EC_POINT_oct2point(group,
                         dst,
                         src.data() + idx,
                         len,
                         sst::bignum::ctx())
      != 1) {
    throw sst::openssl::err_exception("EC_POINT_oct2point()");
  }
  idx += len;
}

inline sst::openssl::ec_point
deserialize_point(std::vector<unsigned char> const & src,
                  std::vector<unsigned char>::size_type & idx,
                  sst::openssl::ec_group const & group) {
  sst::openssl::ec_point dst(group);
  deserialize_point(src, idx, dst, group);
  return dst;
}

inline void deserialize_point(std::vector<unsigned char> const & src,
                              sst::openssl::ec_point & dst,
                              sst::openssl::ec_group const & group) {
  std::vector<unsigned char>::size_type idx = 0;
  deserialize_point(src, idx, dst, group);
}

inline sst::openssl::ec_point
deserialize_point(std::vector<unsigned char> const & src,
                  sst::openssl::ec_group const & group) {
  sst::openssl::ec_point dst(group);
  deserialize_point(src, dst, group);
  return dst;
}

inline void serialize_string(std::vector<unsigned char> & dst,
                             std::string const & src) {
  serialize_integer(dst, src.size(), string_size_size);
  sst::checked_resize(dst, sst::checked(dst.size()) + src.size());
  std::copy_n(src.c_str(),
              src.size(),
              dst.data() + dst.size() - src.size());
}

inline std::vector<unsigned char>
serialize_string(std::string const & src) {
  std::vector<unsigned char> dst;
  serialize_string(dst, src);
  return dst;
}

inline void
deserialize_string(std::vector<unsigned char> const & src,
                   std::vector<unsigned char>::size_type & idx,
                   std::string & dst) {
  std::size_t len{};
  deserialize_integer(src, idx, len, string_size_size);
  if (len > src.size() - idx) {
    throw std::runtime_error("deserialize corruption");
  }
  dst = std::string(reinterpret_cast<char const *>(&src[idx]),
                    reinterpret_cast<char const *>(&src[idx] + len));
  idx += len;
}

inline std::string
deserialize_string(std::vector<unsigned char> const & src,
                   std::vector<unsigned char>::size_type & idx) {
  std::string dst;
  deserialize_string(src, idx, dst);
  return dst;
}

inline void deserialize_string(std::vector<unsigned char> const & src,
                               std::string & dst) {
  std::vector<unsigned char>::size_type idx = 0;
  deserialize_string(src, idx, dst);
}

inline std::string
deserialize_string(std::vector<unsigned char> const & src) {
  std::string dst;
  deserialize_string(src, dst);
  return dst;
}

} // namespace elgamal
} // namespace sst

#endif // #if OPENSSL_VERSION_NUMBER
#endif // #if SST_WITH_OPENSSL_CRYPTO
#endif // SST_CATALOG_ELGAMAL_SERIALIZATION_HPP
