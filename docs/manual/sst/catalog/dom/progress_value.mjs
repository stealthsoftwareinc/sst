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

import {} from "../is_subset.mjs";
import {} from "../SST_ASSERT.mjs";
import {} from "../SST_UNREACHABLE.mjs";

globalThis.sst = globalThis.sst || {};
sst.dom = sst.dom || {};

sst.dom.progress_value = class {

  //--------------------------------------------------------------------

  max_;

  max(x) {
    SST_ASSERT((arguments.length <= 1));
    if (arguments.length === 0) {
      return this.max_;
    }
    SST_ASSERT((typeof (x) === "number" || typeof (x) === "bigint"));
    if (typeof (x) === "number") {
      SST_ASSERT((Number.isFinite(x)));
      SST_ASSERT((x >= 0));
    } else if (typeof (x) === "bigint") {
      SST_ASSERT((x >= 0n));
    } else {
      SST_UNREACHABLE();
    }
    this.max_ = x;
  }

  //--------------------------------------------------------------------

  value_;

  value(x) {
    SST_ASSERT((arguments.length <= 1));
    if (arguments.length === 0) {
      return this.value_;
    }
    SST_ASSERT((typeof (x) === "number" || typeof (x) === "bigint"));
    if (typeof (x) === "number") {
      SST_ASSERT((Number.isFinite(x)));
      SST_ASSERT((x >= 0));
    } else if (typeof (x) === "bigint") {
      SST_ASSERT((x >= 0n));
    } else {
      SST_UNREACHABLE();
    }
    this.value_ = x;
  }

  //--------------------------------------------------------------------

  percent(x) {
    SST_ASSERT((arguments.length <= 1));
    const b = this.max_;
    const b_is_bigint = typeof (b) === "bigint";
    if (arguments.length === 0) {
      const a = this.value_;
      const a_is_bigint = typeof (a) === "bigint";
      if (a >= b) {
        return 100;
      }
      if (!a_is_bigint && !b_is_bigint) {
        return a / b * 100;
      }
      const k = 1 << 10;
      if (a_is_bigint && b_is_bigint) {
        return Number(BigInt(k) * a / b) / k * 100;
      }
      if (a_is_bigint) {
        return Number(a) / b * 100;
      }
      if (BigInt.asUintN(53, b) == b) {
        return a / Number(b) * 100;
      }
      const aa = BigInt(Math.round(a));
      return Number(BigInt(k) * aa / b) / k * 100;
    }
    SST_ASSERT((typeof (x) === "number" || typeof (x) === "bigint"));
    SST_ASSERT((x >= 0));
    SST_ASSERT((x <= 100));
    const x_is_bigint = typeof (x) === "bigint";
    if (!x_is_bigint && !b_is_bigint) {
      this.value_ = x / 100 * b;
    } else if (x_is_bigint && b_is_bigint) {
      this.value_ = x * b / 100n;
    } else if (x_is_bigint) {
      this.value_ = Number(x) / 100 * b;
    } else if (BigInt.asUintN(53, b) == b) {
      this.value_ = x / 100 * Number(b);
    } else {
      const xx = BigInt(Math.round(x));
      this.value_ = xx * b / 100n;
    }
  }

  //--------------------------------------------------------------------

  constructor(options = {}) {

    SST_ASSERT((arguments.length <= 1));
    SST_ASSERT((typeof (options) === "object"));
    SST_ASSERT((sst.is_subset(Object.keys(options), [
      "max",
      "percent",
      "value",
    ])));

    if (options.max === undefined) {
      this.max(100);
    } else {
      this.max(options.max);
    }

    SST_ASSERT(
        (options.value === undefined || options.percent === undefined));
    if (options.value !== undefined) {
      this.value(options.value);
    } else if (options.percent !== undefined) {
      this.percent(options.percent);
    } else {
      this.value(0);
    }

  } //

  //--------------------------------------------------------------------

}; //
