//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_JSON_GET_TO_HPP
#define SST_JSON_GET_TO_HPP

#include <algorithm>
#include <sst/bn_ctx.h>
#include <sst/checked.h>
#include <sst/json/error.h>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

namespace sst {
namespace json {

namespace {

void throw_value_is_malformed() {
  throw error(": value is malformed");
}

void throw_value_has_wrong_type() {
  throw error(": value has wrong type");
}

void throw_value_is_out_of_range() {
  throw error(": value is out of range");
}

} // namespace

//----------------------------------------------------------------------
// std::is_integral destinations
//----------------------------------------------------------------------

template<
    class ValueType,
    class BasicJsonType,
    typename std::enable_if<std::is_integral<ValueType>::value, int>::
        type = 0>
ValueType & get_to(BasicJsonType const & src, ValueType & dst) {
  if (src.is_number_unsigned()) {
    dst = sst::checked_cast<ValueType>(
        src.template get_ref<
            typename BasicJsonType::number_unsigned_t const &>());
  } else if (src.is_number_integer()) {
    dst = sst::checked_cast<ValueType>(
        src.template get_ref<
            typename BasicJsonType::number_integer_t const &>());
  } else if (src.is_boolean()) {
    dst = sst::checked_cast<ValueType>(
        src.template get_ref<
            typename BasicJsonType::boolean_t const &>());
  } else if (src.is_string()) {
    auto const & s = src.template get_ref<
        typename BasicJsonType::string_t const &>();
    auto const n = s.size();
    if (n == 4 && s[0] == 't' && s[1] == 'r' && s[2] == 'u' &&
        s[3] == 'e') {
      dst = 1;
    } else if (
        n == 5 && s[0] == 'f' && s[1] == 'a' && s[2] == 'l' &&
        s[3] == 's' && s[4] == 'e') {
      dst = 0;
    } else {
      decltype(+n) i = 0;
      bool const negate = [&]() {
        if (i < n) {
          if (s[i] == '+') {
            i += 1;
            return false;
          }
          if (s[i] == '-') {
            i += 1;
            return true;
          }
        }
        return false;
      }();
      int const base = [&]() {
        if (i < n && s[i] == '0') {
          if (i + 1 < n && (s[i + 1] == 'x' || s[i + 1] == 'X')) {
            i += 2;
            return 16;
          }
          if (i + 1 < n && (s[i + 1] == 'b' || s[i + 1] == 'B')) {
            i += 2;
            return 2;
          }
          return 8;
        }
        return 10;
      }();
      if (i == n) {
        throw_value_is_malformed();
      }
      sst::checked<ValueType> value = 0;
      bool first_digit = true;
      for (; i != n; ++i) {
        if (first_digit) {
          first_digit = false;
        } else if (s[i] == '\'' && ++i == n) {
          throw_value_is_malformed();
        }
        int digit;
        if (s[i] >= '0' && s[i] <= '0' + std::min(base - 1, 9)) {
          digit = static_cast<int>(s[i] - '0');
        } else if (
            base >= 11 && s[i] >= 'A' && s[i] <= 'A' + (base - 11)) {
          digit = static_cast<int>(s[i] - 'A') + 10;
        } else if (
            base >= 11 && s[i] >= 'a' && s[i] <= 'a' + (base - 11)) {
          digit = static_cast<int>(s[i] - 'a') + 10;
        } else {
          throw_value_is_malformed();
        }
        try {
          if (value.v() != 0) {
            value *= base;
          }
          if (negate) {
            value -= digit;
          } else {
            value += digit;
          }
        } catch (std::range_error const &) {
          for (++i; i != n; ++i) {
            if (s[i] >= '0' && s[i] <= '0' + std::min(base - 1, 9)) {
            } else if (
                base >= 11 && s[i] >= 'A' &&
                s[i] <= 'A' + (base - 11)) {
            } else if (
                base >= 11 && s[i] >= 'a' &&
                s[i] <= 'a' + (base - 11)) {
            } else {
              throw_value_is_malformed();
            }
          }
          throw_value_is_out_of_range();
        }
      }
      dst = value.v();
    }
  } else {
    throw_value_has_wrong_type();
  }
  return dst;
}

//----------------------------------------------------------------------
// BIGNUM destinations
//----------------------------------------------------------------------

#if SST_HAVE_LIB_CRYPTO

template<
    class ValueType,
    class BasicJsonType,
    typename std::enable_if<
        (std::is_same<ValueType, BIGNUM>::value),
        int>::type = 0>
ValueType & get_to(BasicJsonType const & src, ValueType & dst) {
  if (src.is_number_unsigned()) {
    sst::bn_ctx::int2bn(
        dst,
        src.template get_ref<
            typename BasicJsonType::number_unsigned_t const &>());
  } else if (src.is_number_integer()) {
    sst::bn_ctx::int2bn(
        dst,
        src.template get_ref<
            typename BasicJsonType::number_integer_t const &>());
  } else if (src.is_boolean()) {
    sst::bn_ctx::set_word(
        dst,
        static_cast<BN_ULONG>(static_cast<bool>(
            src.template get_ref<
                typename BasicJsonType::boolean_t const &>())));
  } else if (src.is_string()) {
    auto const & s = src.template get_ref<
        typename BasicJsonType::string_t const &>();
    auto const n = s.size();
    if (n == 4 && s[0] == 't' && s[1] == 'r' && s[2] == 'u' &&
        s[3] == 'e') {
      sst::bn_ctx::one(dst);
    } else if (
        n == 5 && s[0] == 'f' && s[1] == 'a' && s[2] == 'l' &&
        s[3] == 's' && s[4] == 'e') {
      sst::bn_ctx::zero(dst);
    } else {
      decltype(+n) i = 0;
      bool const negate = [&]() {
        if (i < n) {
          if (s[i] == '+') {
            i += 1;
            return false;
          }
          if (s[i] == '-') {
            i += 1;
            return true;
          }
        }
        return false;
      }();
      int const base = [&]() {
        if (i < n && s[i] == '0') {
          if (i + 1 < n && (s[i + 1] == 'x' || s[i + 1] == 'X')) {
            i += 2;
            return 16;
          }
          if (i + 1 < n && (s[i + 1] == 'b' || s[i + 1] == 'B')) {
            i += 2;
            return 2;
          }
          return 8;
        }
        return 10;
      }();
      if (i == n) {
        throw_value_is_malformed();
      }
      sst::bn_ctx::zero(dst);
      bool first_digit = true;
      for (; i != n; ++i) {
        if (first_digit) {
          first_digit = false;
        } else if (s[i] == '\'' && ++i == n) {
          throw_value_is_malformed();
        }
        int digit;
        if (s[i] >= '0' && s[i] <= '0' + std::min(base - 1, 9)) {
          digit = static_cast<int>(s[i] - '0');
        } else if (
            base >= 11 && s[i] >= 'A' && s[i] <= 'A' + (base - 11)) {
          digit = static_cast<int>(s[i] - 'A') + 10;
        } else if (
            base >= 11 && s[i] >= 'a' && s[i] <= 'a' + (base - 11)) {
          digit = static_cast<int>(s[i] - 'a') + 10;
        } else {
          throw_value_is_malformed();
        }
        sst::bn_ctx::mul_word(dst, static_cast<BN_ULONG>(base));
        sst::bn_ctx::add_word(dst, static_cast<BN_ULONG>(digit));
      }
      sst::bn_ctx::set_negative(dst, negate);
    }
  } else {
    throw_value_has_wrong_type();
  }
  return dst;
}

#endif

//----------------------------------------------------------------------
// std::vector-like destinations
//----------------------------------------------------------------------

template<class, class = void>
struct is_string_like_dst : std::false_type {};

template<class ValueType>
struct is_string_like_dst<
    ValueType,
    decltype(std::declval<ValueType>().c_str(), void())>
    : std::true_type {};

template<class, class = void>
struct is_vector_like_dst : std::false_type {};

template<class ValueType>
struct is_vector_like_dst<
    ValueType,
    typename std::enable_if<
        !is_string_like_dst<ValueType>::value,
        decltype(
            std::declval<ValueType>().clear(),
            std::declval<ValueType>().push_back(
                std::declval<typename ValueType::value_type>()),
            void())>::type> : std::true_type {};

template<
    class ValueType,
    class BasicJsonType,
    typename std::enable_if<is_vector_like_dst<ValueType>::value, int>::
        type = 0>
ValueType & get_to(BasicJsonType const & src, ValueType & dst) {
  if (src.is_array()) {
    dst.clear();
    for (decltype(+src.size()) i = 0; i != src.size(); ++i) {
      try {
        typename ValueType::value_type x;
        dst.push_back(get_to(src[i], x));
      } catch (error const & e) {
        throw error("[" + std::to_string(i) + "]", e);
      }
    }
  } else {
    throw_value_has_wrong_type();
  }
  return dst;
}

//----------------------------------------------------------------------
// std::map-like destinations
//----------------------------------------------------------------------

template<class, class, class = void>
struct is_map_like_dst : std::false_type {};

template<class ValueType, class BasicJsonType>
struct is_map_like_dst<
    ValueType,
    BasicJsonType,
    typename std::enable_if<
        std::is_constructible<
            typename ValueType::key_type,
            typename BasicJsonType::string_t>::value,
        decltype(
            std::declval<ValueType>().clear(),
            std::declval<ValueType>().insert(std::make_pair(
                std::declval<typename ValueType::key_type>(),
                std::declval<typename ValueType::mapped_type>())),
            void())>::type> : std::true_type {};

template<
    class ValueType,
    class BasicJsonType,
    typename std::enable_if<
        is_map_like_dst<ValueType, BasicJsonType>::value,
        int>::type = 0>
ValueType & get_to(BasicJsonType const & src, ValueType & dst) {
  if (src.is_object()) {
    dst.clear();
    for (auto const & kv : src.items()) {
      auto const & k = kv.key();
      auto const & v = kv.value();
      try {
        typename ValueType::mapped_type x;
        dst.insert(std::make_pair(k, get_to(v, x)));
      } catch (error const & e) {
        throw error("." + std::string(k.begin(), k.end()), e);
      }
    }
  } else {
    throw_value_has_wrong_type();
  }
  return dst;
}

//----------------------------------------------------------------------
// Other destinations
//----------------------------------------------------------------------

template<
    class ValueType,
    class BasicJsonType,
    typename std::enable_if<
        !std::is_integral<ValueType>::value &&
#if SST_HAVE_LIB_CRYPTO
            !std::is_same<ValueType, BIGNUM>::value &&
#endif
            !is_vector_like_dst<ValueType>::value &&
            !is_map_like_dst<ValueType, BasicJsonType>::value,
        int>::type = 0>
ValueType & get_to(BasicJsonType const & src, ValueType & dst) {
  return src.get_to(dst);
}

//----------------------------------------------------------------------
// Object member sources
//----------------------------------------------------------------------

template<class ValueType, class BasicJsonType>
ValueType & get_to(
    BasicJsonType const & src,
    typename BasicJsonType::object_t::key_type const & key,
    ValueType & dst) {
  if (src.is_object()) {
    auto const p = src.find(key);
    if (p == src.end()) {
      throw error(
          "." + std::string(key.begin(), key.end()) +
          ": value is missing");
    } else {
      try {
        get_to(*p, dst);
      } catch (error const & e) {
        throw error("." + std::string(key.begin(), key.end()), e);
      }
    }
  } else {
    throw_value_has_wrong_type();
  }
  return dst;
}

template<class ValueType, class BasicJsonType>
ValueType & get_to(
    BasicJsonType const & src,
    typename BasicJsonType::object_t::key_type const & key,
    ValueType & dst,
    ValueType const & default_value) {
  if (src.is_object()) {
    auto const p = src.find(key);
    if (p == src.end()) {
      dst = default_value;
    } else {
      try {
        get_to(*p, dst);
      } catch (error const & e) {
        throw error("." + std::string(key.begin(), key.end()), e);
      }
    }
  } else {
    throw_value_has_wrong_type();
  }
  return dst;
}

//----------------------------------------------------------------------
// Convenience functions
//----------------------------------------------------------------------

template<class ValueType, class BasicJsonType>
ValueType get_as(BasicJsonType const & src) {
  ValueType dst;
  return get_to(src, dst);
}

template<class ValueType, class BasicJsonType>
ValueType get_as(
    BasicJsonType const & src,
    typename BasicJsonType::object_t::key_type const & key) {
  ValueType dst;
  return get_to(src, key, dst);
}

template<class ValueType, class BasicJsonType>
ValueType get_as(
    BasicJsonType const & src,
    typename BasicJsonType::object_t::key_type const & key,
    ValueType const & default_value) {
  ValueType dst;
  return get_to(src, key, dst, default_value);
}

//----------------------------------------------------------------------

} // namespace json
} // namespace sst

#endif // SST_JSON_GET_TO_HPP
