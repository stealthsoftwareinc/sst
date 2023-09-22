//
// Copyright (C) 2012-2023 Stealth Software Technologies, Inc.
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice (including
// the next paragraph) shall be included in all copies or
// substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// SPDX-License-Identifier: MIT
//

#ifndef SST_PRIVATE_JSON_GET_TO_FROM_NLOHMANN_FROM_MEMBER_HPP
#define SST_PRIVATE_JSON_GET_TO_FROM_NLOHMANN_FROM_MEMBER_HPP

#include <cstddef>
#include <exception>
#include <type_traits>

#include <sst/catalog/SST_DEFINE_BOOLEAN_TRAIT_1.hpp>
#include <sst/catalog/SST_DEFINE_BOOLEAN_TRAIT_2.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/is_optional.hpp>
#include <sst/catalog/is_smart_pointer.hpp>
#include <sst/catalog/json/exception.hpp>
#include <sst/catalog/json/expect_object.hpp>
#include <sst/catalog/json/is_nlohmann.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/private/json/get_to.hpp>

namespace sst {
namespace json {

namespace guts {
namespace get_to {
namespace from_nlohmann_json {
namespace from_member {

SST_DEFINE_BOOLEAN_TRAIT_2(
    is_key,
    T,
    Src,
    (std::is_convertible<T,
                         typename sst::remove_cvref_t<
                             Src>::object_t::key_type const &>::value))

SST_DEFINE_BOOLEAN_TRAIT_1(
    is_found,
    T,
    (std::is_pointer<sst::remove_cvref_t<T>>::value
     || std::is_same<sst::remove_cvref_t<T>, std::nullptr_t>::value))

} // namespace from_member
} // namespace from_nlohmann_json
} // namespace get_to
} // namespace guts

//----------------------------------------------------------------------
// src, dst, key, found, null_means_undefined
//----------------------------------------------------------------------

template<class Src, class Dst, class Key, class Found>
class get_to_functor<
    sst::enable_if_t<sst::json::is_nlohmann<Src>::value
                     && sst::json::guts::get_to::from_nlohmann_json::
                         from_member::is_key<Key, Src>::value
                     && sst::json::guts::get_to::from_nlohmann_json::
                         from_member::is_found<Found>::value>,
    void,
    Src,
    Dst,
    Key,
    Found,
    bool> {

  using src_t = sst::remove_cvref_t<Src>;
  using dst_t = sst::remove_cvref_t<Dst>;
  using key_t = typename src_t::object_t::key_type;

public:

  dst_t & operator()(src_t const & src,
                     dst_t & dst,
                     key_t const & key,
                     bool * const found = nullptr,
                     bool const null_means_undefined = true) const {
    sst::json::expect_object(src);
    try {
      auto const p = src.find(key);
      if (p == src.end() || (p->is_null() && null_means_undefined)) {
        if (found == nullptr) {
          if (p == src.end()) {
            throw sst::json::exception::missing_value();
          } else {
            throw sst::json::exception::expected_not_null();
          }
        }
        *found = false;
      } else {
        sst::json::get_to(*p, dst);
        if (found != nullptr) {
          *found = true;
        }
      }
    } catch (sst::json::exception const & e) {
      std::throw_with_nested(e.add_key(key));
    }
    return dst;
  }

}; //

//----------------------------------------------------------------------
// src, dst, key, found
//----------------------------------------------------------------------

template<class Src, class Dst, class Key, class Found>
class get_to_functor<
    sst::enable_if_t<sst::json::is_nlohmann<Src>::value
                     && sst::json::guts::get_to::from_nlohmann_json::
                         from_member::is_key<Key, Src>::value
                     && sst::json::guts::get_to::from_nlohmann_json::
                         from_member::is_found<Found>::value>,
    void,
    Src,
    Dst,
    Key,
    Found> : public get_to_functor<sst::enable_t,
                                   void,
                                   Src,
                                   Dst,
                                   Key,
                                   bool *,
                                   bool> {};

//----------------------------------------------------------------------
// src, dst, key, default_value, null_means_undefined
//----------------------------------------------------------------------

template<class Src, class Dst, class Key, class DefaultValue>
class get_to_functor<
    sst::enable_if_t<sst::json::is_nlohmann<Src>::value
                     && sst::json::guts::get_to::from_nlohmann_json::
                         from_member::is_key<Key, Src>::value
                     && !sst::json::guts::get_to::from_nlohmann_json::
                            from_member::is_found<DefaultValue>::value>,
    void,
    Src,
    Dst,
    Key,
    DefaultValue,
    bool> {

  using src_t = sst::remove_cvref_t<Src>;
  using dst_t = sst::remove_cvref_t<Dst>;
  using key_t = typename src_t::object_t::key_type;

public:

  template<class DefaultValue2>
  dst_t & operator()(src_t const & src,
                     dst_t & dst,
                     key_t const & key,
                     DefaultValue2 && default_value,
                     bool const null_means_undefined = true) const {
    sst::json::expect_object(src);
    try {
      auto const p = src.find(key);
      if (p == src.end() || (p->is_null() && null_means_undefined)) {
        dst = std::forward<DefaultValue2>(default_value);
      } else {
        sst::json::get_to(*p, dst);
      }
    } catch (sst::json::exception const & e) {
      std::throw_with_nested(e.add_key(key));
    }
    return dst;
  }

}; //

//----------------------------------------------------------------------
// src, dst, key, default_value
//----------------------------------------------------------------------

template<class Src, class Dst, class Key, class DefaultValue>
class get_to_functor<
    sst::enable_if_t<sst::json::is_nlohmann<Src>::value
                     && sst::json::guts::get_to::from_nlohmann_json::
                         from_member::is_key<Key, Src>::value
                     && !sst::json::guts::get_to::from_nlohmann_json::
                            from_member::is_found<DefaultValue>::value>,
    void,
    Src,
    Dst,
    Key,
    DefaultValue> : public get_to_functor<sst::enable_t,
                                          void,
                                          Src,
                                          Dst,
                                          Key,
                                          DefaultValue,
                                          bool> {};

//----------------------------------------------------------------------
// src, dst, key
//----------------------------------------------------------------------

template<class Src, class Dst, class Key>
class get_to_functor<
    sst::enable_if_t<sst::json::is_nlohmann<Src>::value
                     && sst::json::guts::get_to::from_nlohmann_json::
                         from_member::is_key<Key, Src>::value
                     && (sst::is_optional<Dst>::value
                         || sst::is_smart_pointer<Dst>::value)>,
    void,
    Src,
    Dst,
    Key> {

  using src_t = sst::remove_cvref_t<Src>;
  using dst_t = sst::remove_cvref_t<Dst>;
  using key_t = typename src_t::object_t::key_type;

public:

  dst_t &
  operator()(src_t const & src, dst_t & dst, key_t const & key) const {
    return sst::json::get_to(src, dst, key, dst_t());
  }

}; //

template<class Src, class Dst, class Key>
class get_to_functor<
    sst::enable_if_t<sst::json::is_nlohmann<Src>::value
                     && sst::json::guts::get_to::from_nlohmann_json::
                         from_member::is_key<Key, Src>::value
                     && !sst::is_optional<Dst>::value
                     && !sst::is_smart_pointer<Dst>::value>,
    void,
    Src,
    Dst,
    Key> : public get_to_functor<sst::enable_t,
                                 void,
                                 Src,
                                 Dst,
                                 Key,
                                 bool *,
                                 bool> {};

//----------------------------------------------------------------------

} // namespace json
} // namespace sst

#endif // SST_PRIVATE_JSON_GET_TO_FROM_NLOHMANN_FROM_MEMBER_HPP
