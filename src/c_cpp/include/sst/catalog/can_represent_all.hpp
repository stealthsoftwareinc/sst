//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_CAN_REPRESENT_ALL_HPP
#define SST_CATALOG_CAN_REPRESENT_ALL_HPP

#include <sst/catalog/perfect_ge.hpp>
#include <sst/catalog/perfect_le.hpp>
#include <sst/catalog/type_max.hpp>
#include <sst/catalog/type_min.hpp>
#include <type_traits>

namespace sst {

//
// sst::can_represent_all<T, U>::value indicates whether an integer type
// T can represent all values of an integer type U.
//
// This trait is named after the "can represent all" phrasing used in
// the C and C++ standards when discussing the ranges of integer types.
//

namespace detail {

template<class T, class U, class = void>
struct can_represent_all_2 : std::false_type {};

template<class T, class U>
struct can_represent_all_2<
    T,
    U,
    typename std::enable_if<sst::perfect_le(sst::type_min<T>::value,
                                            sst::type_min<U>::value)
                            && sst::perfect_ge(
                                sst::type_max<T>::value,
                                sst::type_max<U>::value)>::type>
    : std::true_type {};

} // namespace detail

template<class T, class U, class = void>
struct can_represent_all : std::false_type {};

//
// Why is std::remove_cv used here? Because the
// src/c_cpp/test/sst/can_represent_all.cpp unit test in SST commit
// a9c55b7791023bbf0f1a7eae215b150748f5bc6c was failing on CentOS 7 on
// 2020-09-12 (g++ (GCC) 4.8.5 20150623 (Red Hat 4.8.5-39)). GCC seems
// to have a buggy bool volatile. The extent of the issue is unclear,
// but std::numeric_limits<bool volatile>::max() at least sometimes
// yields 0. Using std::remove_cv here helps the unit test succeed
// without affecting the SST interface.
//

template<class T, class U>
struct can_represent_all<
    T,
    U,
    typename std::enable_if<std::is_integral<T>()
                            && std::is_integral<U>()>::type>
    : detail::can_represent_all_2<typename std::remove_cv<T>::type,
                                  typename std::remove_cv<U>::type> {};

} // namespace sst

#endif // SST_CATALOG_CAN_REPRESENT_ALL_HPP
