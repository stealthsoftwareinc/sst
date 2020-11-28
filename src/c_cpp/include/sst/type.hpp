//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_TYPE_HPP
#define SST_TYPE_HPP

#include <sst/catalog/integer_promote.hpp>
#include <sst/catalog/integer_promotes.hpp>
#include <sst/catalog/is_bool.hpp>
#include <sst/catalog/remove_cvref.hpp>
#include <sst/limits.h>
#include <type_traits>

namespace sst {

//----------------------------------------------------------------------
// sst::is_signed_integer
//----------------------------------------------------------------------

template<class, class = void>
struct is_signed_integer : std::false_type {};

template<class T>
struct is_signed_integer<
    T,
    typename std::enable_if<std::is_integral<T>()
                            && std::is_signed<T>()>::type>
    : std::true_type {};

//----------------------------------------------------------------------
// sst::is_unsigned_integer
//----------------------------------------------------------------------

template<class, class = void>
struct is_unsigned_integer : std::false_type {};

template<class T>
struct is_unsigned_integer<
    T,
    typename std::enable_if<std::is_integral<T>()
                            && std::is_unsigned<T>()>::type>
    : std::true_type {};

//----------------------------------------------------------------------
// sst::is_non_bool_integer
//----------------------------------------------------------------------

template<class, class = void>
struct is_non_bool_integer : std::false_type {};

template<class T>
struct is_non_bool_integer<
    T,
    typename std::enable_if<std::is_integral<T>()
                            && !sst::is_bool<T>()>::type>
    : std::true_type {};

//----------------------------------------------------------------------
// sst::is_twos_complement
//----------------------------------------------------------------------

template<class T = int, class = void>
struct is_twos_complement : std::false_type {};

template<class T>
struct is_twos_complement<
    T,
    typename std::enable_if<is_unsigned_integer<T>()
                            || (is_signed_integer<T>()
                                && ~1 == -2)>::type> : std::true_type {
};

//----------------------------------------------------------------------
// sst::is_ones_complement
//----------------------------------------------------------------------

template<class T = int, class = void>
struct is_ones_complement : std::false_type {};

template<class T>
struct is_ones_complement<
    T,
    typename std::enable_if<is_signed_integer<T>() && ~1 == -1>::type>
    : std::true_type {};

//----------------------------------------------------------------------
// sst::is_sign_magnitude
//----------------------------------------------------------------------

template<class T = int, class = void>
struct is_sign_magnitude : std::false_type {};

template<class T>
struct is_sign_magnitude<
    T,
    typename std::enable_if<is_signed_integer<T>()
                            && ~1 == type_min<int>() + 1>::type>
    : std::true_type {};

//----------------------------------------------------------------------

} // namespace sst

#endif // SST_TYPE_HPP
