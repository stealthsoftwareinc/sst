#ifndef SST_CATALOG_ELGAMAL_COMMON_HPP
#define SST_CATALOG_ELGAMAL_COMMON_HPP

#include <sst/catalog/bignum.hpp>
#include <sst/catalog/openssl/ec_group.hpp>
#include <sst/catalog/openssl/ec_point.hpp>
#include <sst/catalog/openssl/err_exception.hpp>

#include <openssl/ec.h>

namespace sst {
namespace elgamal {

inline sst::bignum
random_element(sst::openssl::ec_group const & group) {
  sst::bignum order;
  if (EC_GROUP_get_order(group, order.peek(), sst::bignum::ctx())
      == 0) {
    throw sst::openssl::err_exception("EC_GROUP_get_order()");
  }
  return sst::bignum::rand_range(order);
}

} // namespace elgamal
} // namespace sst

#endif // SST_CATALOG_ELGAMAL_COMMON_HPP
