//
// Copyright (C) 2012-2024 Stealth Software Technologies, Inc.
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

//
// The Web Cryptography API specification [1] says that getRandomValues
// throws an exception when the byteLength of the array is greater than
// 65536. We must be careful to not exceed this limit (per call).
//
// [1] https://w3c.github.io/webcrypto/
//

import {} from "./in_browser.mjs";
import {} from "./is_integer_ish.mjs";
import {} from "./is_subset.mjs";
import {} from "./SST_ASSERT.mjs";
import {} from "./SST_UNREACHABLE.mjs";

globalThis.sst = globalThis.sst || {};

function is_acceptable_array(dst) {
  let b = false;
  b = b || dst instanceof Int8Array;
  b = b || dst instanceof Uint8Array;
  b = b || dst instanceof Uint8ClampedArray;
  b = b || dst instanceof Int16Array;
  b = b || dst instanceof Uint16Array;
  b = b || dst instanceof Int32Array;
  b = b || dst instanceof Uint32Array;
  b = b || dst instanceof BigInt64Array;
  b = b || dst instanceof BigUint64Array;
  return b;
}

function infer_crypto_sync(options) {
  if (options.crypto !== undefined) {
    return options.crypto;
  }
  if (sst.in_browser()) {
    return window.crypto;
  }
  if (typeof (globalThis.crypto) !== "object") {
    return undefined;
  }
  if (typeof (crypto.getRandomValues) === "function") {
    return crypto;
  }
  if (typeof (crypto.webcrypto) !== "object") {
    return undefined;
  }
  if (typeof (crypto.webcrypto.getRandomValues) === "function") {
    return crypto.webcrypto;
  }
  return undefined;
}

async function infer_crypto_async() {
  return (await import("node:crypto")).webcrypto;
}

const max_chunk_size = 16384;

function core_sync(ctx) {
  const crypto = infer_crypto_sync(ctx.options);
  if (crypto === undefined) {
    throw new Error("Unable to infer options.crypto");
  }
  while (ctx.n > 0) {
    const k = Math.min(ctx.n, max_chunk_size);
    crypto.getRandomValues(ctx.dst[0].subarray(ctx.i, ctx.i + k));
    ctx.i += k;
    ctx.n -= k;
  }
  return ctx.dst[0];
}

async function core_async(ctx) {
  const crypto =
      infer_crypto_sync(ctx.options) ?? await infer_crypto_async();
  if (crypto === undefined) {
    throw new Error("Unable to infer options.crypto");
  }
  while (ctx.n > 0) {
    const k = Math.min(ctx.n, max_chunk_size);
    crypto.getRandomValues(ctx.dst[0].subarray(ctx.i, ctx.i + k));
    ctx.i += k;
    ctx.n -= k;
    if (ctx.n > 0) {
      await 0;
    }
  }
  return ctx.dst[0];
}

sst.crypto_rng = function(dst, options = {}) {
  SST_ASSERT((arguments.length >= 1));
  SST_ASSERT((arguments.length <= 2));
  SST_ASSERT((typeof (options) === "object"));
  SST_ASSERT((sst.is_subset(Object.keys(options), [
    "async",
    "crypto",
  ])));

  SST_ASSERT((options.async === undefined
              || typeof (options.async) === "boolean"));
  const async = !!options.async;

  SST_ASSERT(
      (options.crypto === undefined
       || (typeof (options.crypto) === "object"
           && typeof (options.crypto.getRandomValues) === "function")));

  if (Array.isArray(dst) && dst.length === 3
      && is_acceptable_array(dst[0]) && sst.is_integer_ish(dst[1])
      && sst.is_integer_ish(dst[2])) {
    let i = dst[1];
    SST_ASSERT((i >= 0));
    SST_ASSERT((i <= dst[0].length));
    i = Number(i);
    let n = dst[2];
    SST_ASSERT((n >= 0));
    SST_ASSERT((n <= dst[0].length - i));
    n = Number(n);
    if (n > 0) {
      const ctx = {dst, options, i, n};
      return async ? core_async(ctx) : core_sync(ctx);
    }
    return dst[0];
  }

  if (is_acceptable_array(dst)) {
    return sst.crypto_rng([dst, 0, dst.length]);
  }

  if (typeof (dst) === "number") {
    SST_ASSERT((Number.isSafeInteger(dst)));
    SST_ASSERT((dst >= 0));
    const n = dst;
    return sst.crypto_rng([new Uint8Array(n), 0, n]);
  }

  if (typeof (dst) === "bigint") {
    SST_ASSERT((dst >= 0));
    const n = BigInt.asUintN(32, dst);
    if (n != dst) {
      // TODO: sst.bad_alloc?
      throw new Error();
    }
    return sst.crypto_rng([new Uint8Array(n), 0, n]);
  }

  SST_UNREACHABLE();
};
