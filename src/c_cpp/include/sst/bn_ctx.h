/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 */

#ifndef SST_BN_CTX_H
#define SST_BN_CTX_H

#ifdef __cplusplus

#include <sst/SST_HAVE_LIB_CRYPTO.h>
#if SST_HAVE_LIB_CRYPTO

/* begin_includes */

#include <algorithm>
#include <cassert>
#include <functional>
#include <iterator>
#include <limits>
#include <memory>
#include <new>
#include <openssl/bn.h>
#include <sst/checked.h>
#include <sst/integer.h>
#include <sst/type.h>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

/* end_includes */

namespace sst {

//
// Create one like this:
//
//       sst::bn_ctx ctx;
//
// Get an integer from it like this:
//
//       BIGNUM & x = ctx.get();
//
// Pass it to a C++ function like this:
//
//       f(ctx.arg());
//
// Receive it in a C++ function like this:
//
//       void f(sst::bn_ctx ctx) {
//         ...
//       }
//
// Pass it to a C function like this:
//
//       g(ctx.ptr());
//
// Use one as a wrapper in a C function like this:
//
//       extern "C" void g(BN_CTX * c) {
//         sst::bn_ctx ctx{c, false};
//         ...
//       }
//

/**
 * Wraps a `BN_CTX` and provides various other `BIGNUM` tools.
 */

class bn_ctx final {

  // is_bn2bin_dst<T>::value indicates whether T can be used as Dst in
  // the bn2bin functions.
  template<class, class = void>
  struct is_bn2bin_dst : std::false_type {};
  template<class T>
  struct is_bn2bin_dst<T,
    typename std::enable_if<
      sst::is_unsigned_integer<
        typename T::size_type
      >::value &&
      std::is_same<
        decltype(std::declval<T>().data()),
        unsigned char *
      >::value &&
      std::is_same<
        decltype(std::declval<T>().size()),
        typename T::size_type
      >::value
    >::type
  > : std::true_type {};

public:

  bn_ctx(
  ) :
    bn_ctx{BN_CTX_new()}
  {
  }

  bn_ctx(
    BN_CTX * const ctx,
    bool const free_ctx_on_destruction = true
  ) :
    bn_ctx{nullptr, ctx, free_ctx_on_destruction}
  {
  }

  bn_ctx(
    bn_ctx const &
  ) = delete;

  bn_ctx & operator =(
    bn_ctx const &
  ) = delete;

  bn_ctx(
    bn_ctx && that
  ) noexcept :
    parent{that.parent},
    child{that.child},
    ctx{that.ctx},
    free_ctx_on_destruction{that.free_ctx_on_destruction},
    must_descend_on_next_get{that.must_descend_on_next_get},
    depth{that.depth}
  {
    that.reset_members();
  }

  bn_ctx & operator =(
    bn_ctx && that
  ) {
    if (this != &that) {
      expect_no_child();
      this->~bn_ctx();
      parent = that.parent;
      child = that.child;
      ctx = that.ctx;
      free_ctx_on_destruction = that.free_ctx_on_destruction;
      must_descend_on_next_get = that.must_descend_on_next_get;
      depth = that.depth;
      that.reset_members();
    }
    return *this;
  }

  ~bn_ctx(
  ) {
    assert(child == nullptr);
    for (; depth != 0; --depth) {
      BN_CTX_end(ctx);
    }
    if (free_ctx_on_destruction) {
      BN_CTX_free(ctx);
    }
    if (parent != nullptr) {
      parent->child = nullptr;
    }
  }

  void reset(
  ) {
    expect_no_child();
    this->~bn_ctx();
    reset_members();
  }

  BIGNUM & get(
  ) {
    expect_no_child();
    reconstruct_if_necessary();
    if (must_descend_on_next_get) {
      descend();
      must_descend_on_next_get = false;
    }
    BIGNUM * const x = BN_CTX_get(ctx);
    if (x == nullptr) {
      throw std::bad_alloc{};
    }
    return *x;
  }

  bn_ctx arg(
  ) {
    expect_no_child();
    reconstruct_if_necessary();
    must_descend_on_next_get = true;
    return bn_ctx{this, ctx, false};
  }

  BN_CTX * ptr(
  ) {
    expect_no_child();
    reconstruct_if_necessary();
    must_descend_on_next_get = true;
    return ctx;
  }

  static BIGNUM & add(
    BIGNUM & r,
    BIGNUM const & a,
    BIGNUM const & b
  ) {
    if (BN_add(&r, &a, &b) != 1) {
      throw std::runtime_error{"BN_add() failed"};
    }
    return r;
  }

  BIGNUM & add(
    BIGNUM const & a,
    BIGNUM const & b
  ) {
    return add(get(), a, b);
  }

  static BIGNUM & add_word(
    BIGNUM & a,
    BN_ULONG const b
  ) {
    if (BN_add_word(&a, b) != 1) {
      throw std::runtime_error{"BN_add_word() failed"};
    }
    return a;
  }

  /**
   * Converts an unsigned bytewise big-endian integer to a `BIGNUM`.
   *
   * @returns
   * `dst`.
   *
   * @xthrows
   * - `std::runtime_error` if the underlying `BN_bin2bn()` call fails.
   *
   * @fineprint
   * - `src_size` must be nonnegative.
   * - `src` must point to at least `src_size` bytes.
   * - `src` must be a valid pointer even if `src_size` is zero.
   */

  static BIGNUM & bin2bn(
    unsigned char const * const src,
    int const src_size,
    BIGNUM & dst
  ) {
    assert(src != nullptr);
    assert(src_size >= 0);
    if (BN_bin2bn(src, src_size, &dst) != &dst) {
      throw std::runtime_error{"BN_bin2bn() failed"};
    }
    return dst;
  }

  template<class Src>
  static BIGNUM & bin2bn(
    Src const & src,
    typename Src::size_type const src_pos,
    typename Src::size_type const src_size,
    BIGNUM & dst
  ) {
    if (src.data() == nullptr) {
      return zero(dst);
    }
    if (
      src_size >
      static_cast<unsigned int>(std::numeric_limits<int>::max())
    ) {
      throw std::overflow_error{"int overflow"};
    }
    return (
      bin2bn(
        src.data() + src_pos,
        static_cast<int>(src_size),
        dst
      )
    );
  }

  template<class Src>
  BIGNUM & bin2bn(
    Src const & src,
    typename Src::size_type const src_pos,
    typename Src::size_type const src_size
  ) {
    return bin2bn(src, src_pos, src_size, get());
  }

  template<class Src>
  static BIGNUM & bin2bn(
    Src const & src,
    BIGNUM & dst
  ) {
    return bin2bn(src, 0, src.size(), dst);
  }

  template<class Src>
  BIGNUM & bin2bn(
    Src const & src
  ) {
    return bin2bn(src, get());
  }

  /**
   * Converts the absolute value of a `BIGNUM` to an unsigned bytewise
   * big-endian integer.
   *
   * If `num_bytes(src)` is zero, i.e., if `src` is zero, then nothing
   * is written to `dst`.
   * Otherwise, the unsigned bytewise big-endian integer is written to
   * `[dst, dst + num_bytes(src))`.
   *
   * @returns
   * `dst`.
   *
   * @fineprint
   * - If `dst` is a null pointer or points to fewer than
   *   `num_bytes(src)` bytes, then the behavior is undefined.
   */

  static unsigned char * bn2bin(
    BIGNUM const & src,
    unsigned char * const dst
  ) noexcept {
    assert(dst != nullptr);
    BN_bn2bin(&src, dst);
    return dst;
  }

  /**
   * Converts the absolute value of a `BIGNUM` to an unsigned bytewise
   * big-endian integer.
   *
   * If `num_bytes(src)` is zero, i.e., if `src` is zero, then nothing
   * is written to `dst`.
   * Otherwise, the unsigned bytewise big-endian integer is written to
   * `[dst.data() + dst_pos, dst.data() + dst_pos + num_bytes(src))`.
   *
   * @returns
   * - a null pointer if `dst.data()` is a null pointer, or
   *   `dst.data() + dst_pos` if not.
   *
   * @fineprint
   * - If `dst.size()` is less than `dst_pos + num_bytes(src)`, then the
   *   behavior is undefined.
   */

  template<
    class Dst
  > static auto bn2bin(
    BIGNUM const & src,
    Dst & dst,
    typename Dst::size_type const dst_pos
  ) noexcept -> typename std::enable_if<
    is_bn2bin_dst<Dst>::value,
    unsigned char *
  >::type {
    assert(dst.size() >= dst_pos);
    assert(sst::unsigned_ge(dst.size() - dst_pos, num_bytes(src)));
    if (dst.data() == nullptr) {
      return nullptr;
    }
    return bn2bin(src, dst.data() + dst_pos);
  }

  /**
   * Converts the absolute value of a `BIGNUM` to an unsigned bytewise
   * big-endian integer.
   *
   * If `num_bytes(src)` is zero, i.e., if `src` is zero, then nothing
   * is written to `dst`.
   * Otherwise, the unsigned bytewise big-endian integer is written to
   * `[dst.data(), dst.data() + num_bytes(src))`.
   *
   * @returns
   * `dst`.
   *
   * @fineprint
   * - If `dst.size()` is less than `num_bytes(src)`, then the behavior
   *   is undefined.
   */

  template<
    class Dst
  > static auto bn2bin(
    BIGNUM const & src,
    Dst & dst
  ) noexcept -> typename std::enable_if<
    is_bn2bin_dst<Dst>::value,
    Dst &
  >::type {
    bn2bin(src, dst, 0);
    return dst;
  }

  /**
   * Converts the absolute value of a `BIGNUM` to an unsigned bytewise
   * big-endian integer.
   *
   * @returns
   * a `Dst` containing the unsigned bytewise big-endian integer, which
   * is `num_bytes(src)` bytes in size.
   * Note that `num_bytes(src)` is zero when `src` is zero.
   *
   * @xthrows
   * - `std::range_error` if `Dst::size_type` cannot represent
   *   `num_bytes(src)`.
   */

  template<
    class Dst = std::vector<unsigned char>
  > static auto bn2bin(
    BIGNUM const & src
  ) -> typename std::enable_if<
    is_bn2bin_dst<Dst>::value,
    Dst
  >::type {
    Dst dst(sst::checked<typename Dst::size_type>{num_bytes(src)}.v());
    return bn2bin(src, dst);
  }

  /**
   * Converts the absolute value of a `BIGNUM` to an unsigned bytewise
   * big-endian integer with a specified size.
   *
   * @returns
   * `dst`.
   *
   * @fineprint
   * - `dst_size` must be greater than or equal to `num_bytes(src)`.
   * - `dst` must point to at least `dst_size` bytes.
   * - `dst` must be a valid pointer even if `dst_size` is zero.
   */

  template<
    class DstSize
  > static auto bn2binpad(
    BIGNUM const & src,
    unsigned char * const dst,
    DstSize const dst_size
  ) noexcept -> typename std::enable_if<
    std::is_integral<DstSize>::value,
    unsigned char *
  >::type {
    auto const src_size = num_bytes(src);
    assert(dst != nullptr);
    assert(dst_size >= 0);
    assert(unsigned_ge(dst_size, src_size));
    std::fill(dst, dst + dst_size - src_size, 0);
    bn2bin(src, dst + dst_size - src_size);
    return dst;
  }

  /**
   * Converts the absolute value of a `BIGNUM` to an unsigned bytewise
   * big-endian integer with a specified size.
   *
   * @returns
   * `dst.data()`.
   */

  template<
    class Dst
  > static auto bn2binpad(
    BIGNUM const & src,
    Dst & dst,
    typename Dst::size_type const dst_pos,
    typename Dst::size_type const dst_size
  ) noexcept -> typename std::enable_if<
    is_bn2bin_dst<Dst>::value,
    unsigned char *
  >::type {
    assert(dst.size() >= dst_pos);
    assert(dst.size() - dst_pos >= dst_size);
    assert(sst::unsigned_ge(dst_size, num_bytes(src)));
    if (dst.data() == nullptr) {
      return nullptr;
    }
    return bn2binpad(src, dst.data() + dst_pos, dst_size);
  }

  /**
   * Converts the absolute value of a `BIGNUM` to an unsigned bytewise
   * big-endian integer with a specified size.
   *
   * @returns
   * `dst`.
   */

  template<
    class Dst
  > static auto bn2binpad(
    BIGNUM const & src,
    Dst & dst,
    typename Dst::size_type const dst_size
  ) noexcept -> typename std::enable_if<
    is_bn2bin_dst<Dst>::value,
    Dst &
  >::type {
    bn2binpad(src, dst, 0, dst_size);
    return dst;
  }

  /**
   * Converts the absolute value of a `BIGNUM` to an unsigned bytewise
   * big-endian integer with a specified size.
   *
   * @returns
   * `dst`.
   */

  template<
    class Dst
  > static auto bn2binpad(
    BIGNUM const & src,
    Dst & dst
  ) noexcept -> typename std::enable_if<
    is_bn2bin_dst<Dst>::value,
    Dst &
  >::type {
    return bn2binpad(src, dst, dst.size());
  }

  /**
   * Converts the absolute value of a `BIGNUM` to an unsigned bytewise
   * big-endian integer with a specified size.
   */

  template<
    class Dst = std::vector<unsigned char>,
    class DstSize
  > static auto bn2binpad(
    BIGNUM const & src,
    DstSize const dst_size
  ) -> typename std::enable_if<
    is_bn2bin_dst<Dst>::value && std::is_integral<DstSize>::value,
    Dst
  >::type {
    Dst dst(sst::checked<typename Dst::size_type>{dst_size}.v());
    return bn2binpad(src, dst);
  }

  template<class OutputIterator>
  OutputIterator bn2dec(
    BIGNUM const & a,
    OutputIterator b
  ) {
    bn_ctx && bn{arg()};
    if (bn.is_negative(a)) {
      *b++ = '-';
      BIGNUM & x = bn.copy(a);
      bn.set_negative(x, false);
      bn.bn2dec(x, b);
    } else {
      BIGNUM & x = bn.set_word(10);
      BIGNUM & y = bn.get();
      while (bn.cmp(x, a) <= 0) {
        bn.mul_word(x, 10);
      }
      bn.div_word(x, 10);
      while (!bn.is_zero(x)) {
        bn.div(y, a, x);
        *b++ = '0' + bn.mod_word(y, 10);
        bn.div_word(x, 10);
      }
    }
    return b;
  }

  std::string bn2dec(
    BIGNUM const & a
  ) {
    std::string b;
    bn2dec(a, std::back_inserter(b));
    return b;
  }

  template<class OutputIterator>
  OutputIterator bn2hex(
    BIGNUM const & a,
    OutputIterator b
  ) {
    bn_ctx && bn{arg()};
    if (bn.is_negative(a)) {
      *b++ = '-';
      BIGNUM & x = bn.copy(a);
      bn.set_negative(x, false);
      bn.bn2hex(x, b);
    } else {
      BIGNUM & x = bn.get();
      int n = bn.num_bits(a);
      if (n % 4 != 0) {
        n = n / 4 * 4;
      } else if (n != 0) {
        n -= 4;
      }
      for (;;) {
        bn.rshift(x, a, n);
        bn.mask_bits(x, 4);
        *b++ = "0123456789ABCDEF"[bn.get_word(x)];
        if (n == 0) {
          break;
        }
        n -= 4;
      }
    }
    return b;
  }

  std::string bn2hex(
    BIGNUM const & a
  ) {
    std::string b;
    bn2hex(a, std::back_inserter(b));
    return b;
  }

  static BIGNUM & clear_bit(
    BIGNUM & a,
    int const i
  ) noexcept {
    assert(i >= 0);
    BN_clear_bit(&a, i);
    return a;
  }

  BIGNUM & clear_bit(
    int const i
  ) {
    assert(i >= 0);
    return zero();
  }

  static int cmp(
    BIGNUM const & a,
    BIGNUM const & b
  ) noexcept {
    return BN_cmp(&a, &b);
  }

  static BIGNUM & copy(
    BIGNUM & a,
    BIGNUM const & b
  ) {
    if (BN_copy(&a, &b) == nullptr) {
      throw std::runtime_error{"BN_copy() failed"};
    }
    return a;
  }

  BIGNUM & copy(
    BIGNUM const & b
  ) {
    return copy(get(), b);
  }

  template<class InputIterator>
  static BIGNUM & dec2bn(
    BIGNUM & a,
    InputIterator b,
    InputIterator const b_end
  ) {
    static char const * const message =
      "sst::bn_ctx::dec2bn invalid argument"
    ;
    if (b == b_end) {
      throw std::invalid_argument{message};
    }
    auto c = *b++;
    bool const negative = (c == '-');
    if (negative) {
      if (b == b_end) {
        throw std::invalid_argument{message};
      }
      c = *b++;
    }
    int v = dec_value(c);
    if (v < 0) {
      throw std::invalid_argument{message};
    }
    set_word(a, v);
    while (b != b_end) {
      c = *b++;
      v = dec_value(c);
      if (v < 0) {
        throw std::invalid_argument{message};
      }
      mul_word(a, 10);
      add_word(a, v);
    }
    if (negative) {
      set_negative(a, true);
    }
    return a;
  }

  template<class InputIterator>
  BIGNUM & dec2bn(
    InputIterator b,
    InputIterator const b_end
  ) {
    return dec2bn(get(), b, b_end);
  }

  BIGNUM & div(
    BIGNUM & q,
    BIGNUM & r,
    BIGNUM const & a,
    BIGNUM const & m
  ) {
    if (BN_div(&q, &r, &a, &m, ptr()) != 1) {
      throw std::runtime_error{"BN_div() failed"};
    }
    return q;
  }

  BIGNUM & div(
    BIGNUM & q,
    BIGNUM const & a,
    BIGNUM const & m
  ) {
    if (BN_div(&q, nullptr, &a, &m, ptr()) != 1) {
      throw std::runtime_error{"BN_div() failed"};
    }
    return q;
  }

  BIGNUM & div(
    BIGNUM const & a,
    BIGNUM const & m
  ) {
    return div(get(), a, m);
  }

  static BN_ULONG div_word(
    BIGNUM & a,
    BN_ULONG const m
  ) {
    BN_ULONG const r = BN_div_word(&a, m);
    if (r == std::numeric_limits<BN_ULONG>::max()) {
      throw std::runtime_error{"BN_div_word() failed"};
    }
    return r;
  }

  using wild = std::unique_ptr<BIGNUM, std::function<void (BIGNUM *)>>;

  static wild dup(
    BIGNUM const & b
  ) {
    BIGNUM * const a = BN_dup(&b);
    if (a == nullptr) {
      throw std::runtime_error{"BN_dup() failed"};
    }
    return wild{a, [=](BIGNUM *) { BN_free(a); }};
  }

  static wild dup(
  ) {
    BIGNUM * const a = BN_new();
    if (a == nullptr) {
      throw std::runtime_error{"BN_new() failed"};
    }
    return wild{a, [=](BIGNUM *) { BN_free(a); }};
  }

  BIGNUM & exp(
    BIGNUM & r,
    BIGNUM const & a,
    BIGNUM const & b
  ) {
    if (BN_exp(&r, &a, &b, ptr()) != 1) {
      throw std::runtime_error{"BN_exp() failed"};
    }
    return r;
  }

  BIGNUM & exp(
    BIGNUM const & a,
    BIGNUM const & b
  ) {
    return exp(get(), a, b);
  }

  BIGNUM & gcd(
    BIGNUM & r,
    BIGNUM const & a,
    BIGNUM const & b
  ) {
    if (BN_gcd(&r, &a, &b, ptr()) != 1) {
      throw std::runtime_error{"BN_gcd() failed"};
    }
    return r;
  }

  BIGNUM & gcd(
    BIGNUM const & a,
    BIGNUM const & b
  ) {
    return gcd(get(), a, b);
  }

  static BN_ULONG get_word(
    BIGNUM const & a
  ) noexcept {
    return BN_get_word(&a);
  }

  template<class InputIterator>
  static BIGNUM & hex2bn(
    BIGNUM & a,
    InputIterator b,
    InputIterator const b_end
  ) {
    static char const * const message =
      "sst::bn_ctx::hex2bn invalid argument"
    ;
    if (b == b_end) {
      throw std::invalid_argument{message};
    }
    auto c = *b++;
    bool const negative = (c == '-');
    if (negative) {
      if (b == b_end) {
        throw std::invalid_argument{message};
      }
      c = *b++;
    }
    int v = hex_value(c);
    if (v < 0) {
      throw std::invalid_argument{message};
    }
    set_word(a, v);
    while (b != b_end) {
      c = *b++;
      v = hex_value(c);
      if (v < 0) {
        throw std::invalid_argument{message};
      }
      lshift(a, a, 4);
      add_word(a, v);
    }
    if (negative) {
      set_negative(a, true);
    }
    return a;
  }

  template<class InputIterator>
  BIGNUM & hex2bn(
    InputIterator b,
    InputIterator const b_end
  ) {
    return hex2bn(get(), b, b_end);
  }

  template<class Src>
  static BIGNUM & int2bn(
    BIGNUM & dst,
    Src const src
  ) {
    static_assert(
      std::is_integral<Src>::value,
      "Src must be an integer type"
    );
    if (src >= 0) {
      Src n{1};
      for (
        auto i =
          static_cast<
            typename std::common_type<
              typename std::make_unsigned<Src>::type,
              BN_ULONG
            >::type
          >(src)
        ;
        i > std::numeric_limits<BN_ULONG>::max();
        i = (i >> 1) >> (BN_BITS2 - 1)
      ) {
        ++n;
      }
      set_word(dst, static_cast<BN_ULONG>(src >> (--n * BN_BITS2)));
      while (n != 0) {
        lshift(dst, dst, BN_BITS2);
        add_word(dst, static_cast<BN_ULONG>(src >> (--n * BN_BITS2)));
      }
    } else if (src == std::numeric_limits<Src>::min()) {
      int2bn(dst, -(src + 1));
      set_negative(dst, true);
      sub_word(dst, 1);
    } else {
      int2bn(dst, -src);
      set_negative(dst, true);
    }
    return dst;
  }

  template<class Src>
  BIGNUM & int2bn(
    Src const src
  ) {
    static_assert(
      std::is_integral<Src>::value,
      "Src must be an integer type"
    );
    return int2bn(get(), src);
  }

  static bool is_bit_set(
    BIGNUM const & a,
    int const i
  ) noexcept {
    assert(i >= 0);
    return BN_is_bit_set(&a, i);
  }

  static bool is_negative(
    BIGNUM const & a
  ) noexcept {
    return BN_is_negative(&a);
  }

  static bool is_odd(
    BIGNUM const & a
  ) noexcept {
    return BN_is_odd(&a);
  }

  static bool is_one(
    BIGNUM const & a
  ) noexcept {
    return BN_is_one(&a);
  }

  static bool is_word(
    BIGNUM const & a,
    BN_ULONG const b
  ) noexcept {
    return BN_is_word(&a, b);
  }

  static bool is_zero(
    BIGNUM const & a
  ) noexcept {
    return BN_is_zero(&a);
  }

  static BIGNUM & lshift(
    BIGNUM & a,
    BIGNUM const & b,
    int const n
  ) {
    assert(n >= 0);
    if (BN_lshift(&a, &b, n) != 1) {
      throw std::runtime_error{"BN_lshift() failed"};
    }
    return a;
  }

  BIGNUM & lshift(
    BIGNUM const & b,
    int const n
  ) {
    assert(n >= 0);
    return lshift(get(), b, n);
  }

  static BIGNUM & lshift1(
    BIGNUM & a,
    BIGNUM const & b
  ) {
    if (BN_lshift1(&a, &b) != 1) {
      throw std::runtime_error{"BN_lshift1() failed"};
    }
    return a;
  }

  BIGNUM & lshift1(
    BIGNUM const & b
  ) {
    return lshift1(get(), b);
  }

  static BIGNUM & mask_bits(
    BIGNUM & a,
    int const n
  ) noexcept {
    assert(n >= 0);
    BN_mask_bits(&a, n);
    return a;
  }

  BIGNUM & mod(
    BIGNUM & r,
    BIGNUM const & a,
    BIGNUM const & m
  ) {
    if (BN_mod(&r, &a, &m, ptr()) != 1) {
      throw std::runtime_error{"BN_mod() failed"};
    }
    return r;
  }

  BIGNUM & mod(
    BIGNUM const & a,
    BIGNUM const & m
  ) {
    return mod(get(), a, m);
  }

  BIGNUM & mod_inverse(
    BIGNUM & r,
    BIGNUM const & a,
    BIGNUM const & m
  ) {
    if (BN_mod_inverse(&r, &a, &m, ptr()) != &r) {
      throw std::runtime_error{"BN_mod_inverse() failed"};
    }
    return r;
  }

  BIGNUM & mod_inverse(
    BIGNUM const & a,
    BIGNUM const & m
  ) {
    return mod_inverse(get(), a, m);
  }

  static BN_ULONG mod_word(
    BIGNUM const & a,
    BN_ULONG const m
  ) {
    BN_ULONG const r = BN_mod_word(&a, m);
    if (r == std::numeric_limits<BN_ULONG>::max()) {
      throw std::runtime_error{"BN_mod_word() failed"};
    }
    return r;
  }

  BIGNUM & mod_add(
    BIGNUM & r,
    BIGNUM const & a,
    BIGNUM const & b,
    BIGNUM const & m
  ) {
    if (BN_mod_add(&r, &a, &b, &m, ptr()) != 1) {
      throw std::runtime_error{"BN_mod_add() failed"};
    }
    return r;
  }

  BIGNUM & mod_add(
    BIGNUM const & a,
    BIGNUM const & b,
    BIGNUM const & m
  ) {
    return mod_add(get(), a, b, m);
  }

  BIGNUM & mod_exp(
    BIGNUM & r,
    BIGNUM const & a,
    BIGNUM const & b,
    BIGNUM const & m
  ) {
    if (BN_mod_exp(&r, &a, &b, &m, ptr()) != 1) {
      throw std::runtime_error{"BN_mod_exp() failed"};
    }
    return r;
  }

  BIGNUM & mod_exp(
    BIGNUM const & a,
    BIGNUM const & b,
    BIGNUM const & m
  ) {
    return mod_exp(get(), a, b, m);
  }

  BIGNUM & mod_mul(
    BIGNUM & r,
    BIGNUM const & a,
    BIGNUM const & b,
    BIGNUM const & m
  ) {
    if (BN_mod_mul(&r, &a, &b, &m, ptr()) != 1) {
      throw std::runtime_error{"BN_mod_mul() failed"};
    }
    return r;
  }

  BIGNUM & mod_mul(
    BIGNUM const & a,
    BIGNUM const & b,
    BIGNUM const & m
  ) {
    return mod_mul(get(), a, b, m);
  }

  BIGNUM & mod_sqr(
    BIGNUM & r,
    BIGNUM const & a,
    BIGNUM const & m
  ) {
    if (BN_mod_sqr(&r, &a, &m, ptr()) != 1) {
      throw std::runtime_error{"BN_mod_sqr() failed"};
    }
    return r;
  }

  BIGNUM & mod_sqr(
    BIGNUM const & a,
    BIGNUM const & m
  ) {
    return mod_sqr(get(), a, m);
  }

  BIGNUM & mod_sub(
    BIGNUM & r,
    BIGNUM const & a,
    BIGNUM const & b,
    BIGNUM const & m
  ) {
    if (BN_mod_sub(&r, &a, &b, &m, ptr()) != 1) {
      throw std::runtime_error{"BN_mod_sub() failed"};
    }
    return r;
  }

  BIGNUM & mod_sub(
    BIGNUM const & a,
    BIGNUM const & b,
    BIGNUM const & m
  ) {
    return mod_sub(get(), a, b, m);
  }

  BIGNUM & mul(
    BIGNUM & r,
    BIGNUM const & a,
    BIGNUM const & b
  ) {
    if (BN_mul(&r, &a, &b, ptr()) != 1) {
      throw std::runtime_error{"BN_mul() failed"};
    }
    return r;
  }

  BIGNUM & mul(
    BIGNUM const & a,
    BIGNUM const & b
  ) {
    return mul(get(), a, b);
  }

  static BIGNUM & mul_word(
    BIGNUM & a,
    BN_ULONG const b
  ) {
    if (BN_mul_word(&a, b) != 1) {
      throw std::runtime_error{"BN_mul_word() failed"};
    }
    return a;
  }

  BIGNUM & nnmod(
    BIGNUM & r,
    BIGNUM const & a,
    BIGNUM const & m
  ) {
    if (BN_nnmod(&r, &a, &m, ptr()) != 1) {
      throw std::runtime_error{"BN_nnmod() failed"};
    }
    return r;
  }

  BIGNUM & nnmod(
    BIGNUM const & a,
    BIGNUM const & m
  ) {
    return nnmod(get(), a, m);
  }

  static int num_bits(
    BIGNUM const & a
  ) noexcept {
    return BN_num_bits(&a);
  }

  static int num_bits(
    BN_ULONG const a
  ) noexcept {
    return BN_num_bits_word(a);
  }

  static int num_bytes(
    BIGNUM const & a
  ) noexcept {
    return BN_num_bytes(&a);
  }

  static BIGNUM & one(
    BIGNUM & a
  ) {
    if (BN_one(&a) != 1) {
      throw std::runtime_error{"BN_one() failed"};
    }
    return a;
  }

  BIGNUM & one(
  ) {
    return one(get());
  }

  static BIGNUM & rand_range(
    BIGNUM & a,
    BIGNUM const & m
  ) {
    if (BN_rand_range(&a, &m) != 1) {
      throw std::runtime_error{"BN_rand_range() failed"};
    }
    return a;
  }

  BIGNUM & rand_range(
    BIGNUM const & m
  ) {
    return rand_range(get(), m);
  }

  static BIGNUM & rshift(
    BIGNUM & a,
    BIGNUM const & b,
    int const n
  ) {
    assert(n >= 0);
    if (BN_rshift(&a, &b, n) != 1) {
      throw std::runtime_error{"BN_rshift() failed"};
    }
    return a;
  }

  BIGNUM & rshift(
    BIGNUM const & b,
    int const n
  ) {
    assert(n >= 0);
    return rshift(get(), b, n);
  }

  static BIGNUM & rshift1(
    BIGNUM & a,
    BIGNUM const & b
  ) {
    if (BN_rshift1(&a, &b) != 1) {
      throw std::runtime_error{"BN_rshift1() failed"};
    }
    return a;
  }

  BIGNUM & rshift1(
    BIGNUM const & b
  ) {
    return rshift1(get(), b);
  }

  static BIGNUM & set_bit(
    BIGNUM & a,
    int const i
  ) {
    assert(i >= 0);
    if (BN_set_bit(&a, i) != 1) {
      throw std::runtime_error{"BN_set_bit() failed"};
    }
    return a;
  }

  static BIGNUM & set_bit(
    BIGNUM & a,
    int const i,
    bool const b
  ) {
    assert(i >= 0);
    if (b) {
      return set_bit(a, i);
    }
    return clear_bit(a, i);
  }

  BIGNUM & set_bit(
    int const i
  ) {
    assert(i >= 0);
    return set_bit(zero(), i);
  }

  BIGNUM & set_bit(
    int const i,
    bool const b
  ) {
    assert(i >= 0);
    if (b) {
      return set_bit(i);
    }
    return clear_bit(i);
  }

  static BIGNUM & set_negative(
    BIGNUM & a,
    bool const b
  ) {
    BN_set_negative(&a, b);
    return a;
  }

  static BIGNUM & set_word(
    BIGNUM & a,
    BN_ULONG const b
  ) {
    if (BN_set_word(&a, b) != 1) {
      throw std::runtime_error{"BN_set_word() failed"};
    }
    return a;
  }

  BIGNUM & set_word(
    BN_ULONG const b
  ) {
    return set_word(get(), b);
  }

  BIGNUM & sqr(
    BIGNUM & r,
    BIGNUM const & a
  ) {
    if (BN_sqr(&r, &a, ptr()) != 1) {
      throw std::runtime_error{"BN_sqr() failed"};
    }
    return r;
  }

  BIGNUM & sqr(
    BIGNUM const & a
  ) {
    return sqr(get(), a);
  }

  static BIGNUM & sub(
    BIGNUM & r,
    BIGNUM const & a,
    BIGNUM const & b
  ) {
    if (BN_sub(&r, &a, &b) != 1) {
      throw std::runtime_error{"BN_sub() failed"};
    }
    return r;
  }

  BIGNUM & sub(
    BIGNUM const & a,
    BIGNUM const & b
  ) {
    return sub(get(), a, b);
  }

  static BIGNUM & sub_word(
    BIGNUM & a,
    BN_ULONG const b
  ) {
    if (BN_sub_word(&a, b) != 1) {
      throw std::runtime_error{"BN_sub_word() failed"};
    }
    return a;
  }

  static int ucmp(
    BIGNUM const & a,
    BIGNUM const & b
  ) noexcept {
    return BN_ucmp(&a, &b);
  }

  static BIGNUM const & value_one(
  ) noexcept {
    return *BN_value_one();
  }

  static BIGNUM & zero(
    BIGNUM & a
  ) noexcept {
    BN_zero(&a);
    return a;
  }

  BIGNUM & zero(
  ) {
    return zero(get());
  }

private:

  bn_ctx * parent;
  bn_ctx * child;
  BN_CTX * ctx;
  bool free_ctx_on_destruction;
  bool must_descend_on_next_get;
  int depth;

  bn_ctx(
    bn_ctx * const parent,
    BN_CTX * const ctx,
    bool const free_ctx_on_destruction
  ) :
    parent{parent},
    child{nullptr},
    ctx{ctx},
    free_ctx_on_destruction{free_ctx_on_destruction},
    must_descend_on_next_get{false},
    depth{1}
  {
    if (ctx == nullptr) {
      throw std::bad_alloc{};
    }
    BN_CTX_start(ctx);
    if (parent != nullptr) {
      parent->child = this;
    }
  }

  void reset_members(
  ) noexcept {
    parent = nullptr;
    child = nullptr;
    ctx = nullptr;
    free_ctx_on_destruction = false;
    must_descend_on_next_get = false;
    depth = 0;
  }

  void reconstruct_if_necessary(
  ) {
    if (ctx == nullptr) {
      ctx = BN_CTX_new();
      if (ctx == nullptr) {
        throw std::bad_alloc{};
      }
      BN_CTX_start(ctx);
      parent = nullptr;
      child = nullptr;
      free_ctx_on_destruction = true;
      must_descend_on_next_get = false;
      depth = 1;
    }
  }

  void descend(
  ) {
    if (depth == std::numeric_limits<decltype(depth)>::max()) {
      throw std::runtime_error{"sst::bn_ctx::depth overflow"};
    }
    BN_CTX_start(ctx);
    ++depth;
  }

  void expect_no_child(
  ) {
    if (child != nullptr) {
      throw std::logic_error{
        "sst::bn_ctx accessed while child exists"
      };
    }
  }

  template<class CharT>
  static constexpr int dec_value(
    CharT const c
  ) noexcept {
    return (
      (c >= '0' && c <= '9') ? (
        static_cast<int>(c - '0')
      ) : (
        -1
      )
    );
  }

  template<class CharT>
  static constexpr int hex_value(
    CharT const c
  ) noexcept {
    return (
      (c >= '0' && c <= '9') ? (
        static_cast<int>(c - '0')
      ) : (c >= 'A' && c <= 'F') ? (
        10 + static_cast<int>(c - 'A')
      ) : (c >= 'a' && c <= 'f') ? (
        10 + static_cast<int>(c - 'a')
      ) : (
        -1
      )
    );
  }

};

} // namespace sst

#endif // SST_HAVE_LIB_CRYPTO

#endif // __cplusplus

#endif // SST_BN_CTX_H
