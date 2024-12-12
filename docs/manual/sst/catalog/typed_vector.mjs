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

import {} from "./SST_ASSERT.mjs";

globalThis.sst = globalThis.sst || {};

function array_type_is_valid(array_type) {
  let b = false;
  b = b || array_type === BigInt64Array;
  b = b || array_type === BigUint64Array;
  b = b || array_type === Float32Array;
  b = b || array_type === Float64Array;
  b = b || array_type === Int16Array;
  b = b || array_type === Int32Array;
  b = b || array_type === Int8Array;
  b = b || array_type === Uint16Array;
  b = b || array_type === Uint32Array;
  b = b || array_type === Uint8Array;
  b = b || array_type === Uint8ClampedArray;
  return b;
}

sst.typed_vector = class typed_vector {

  array_type_;
  array_;
  size_;

  constructor(array_type) {
    SST_ASSERT((arguments.length === 1));
    SST_ASSERT((array_type_is_valid(array_type)));
    this.array_type_ = array_type;
    this.array_ = new array_type();
    this.size_ = 0;
  }

  array() {
    SST_ASSERT((arguments.length === 0));
    return this.array_.subarray(0, this.size_);
  }

  array_type() {
    SST_ASSERT((arguments.length === 0));
    return this.array_type_;
  }

  clear() {
    SST_ASSERT((arguments.length === 0));
    this.size_ = 0;
  }

  data() {
    SST_ASSERT((arguments.length === 0));
    return this.array_;
  }

  empty() {
    SST_ASSERT((arguments.length === 0));
    return this.size_ === 0;
  }

  push_back(x) {
    SST_ASSERT((arguments.length === 1));
    if (x instanceof this.array_type_) {
      const max = Number.MAX_SAFE_INTEGER;
      if (x.length > max || this.size_ > max - x.length) {
        throw new Error("Safe integer range exceeded");
      }
      const size = this.size_ + x.length;
      this.reserve(size);
      this.array_.set(x, this.size_);
      this.size_ = size;
      return;
    }
    SST_ASSERT((false));
  }

  reserve(size) {
    SST_ASSERT((arguments.length === 1));
    SST_ASSERT((typeof (size) === "number"));
    SST_ASSERT((Number.isInteger(size)));
    SST_ASSERT((size >= 0));
    const max = Number.MAX_SAFE_INTEGER;
    if (size > max) {
      throw new Error("Safe integer range exceeded");
    }
    if (size > this.array_.length) {
      let n = this.array_.length;
      while (n < size) {
        if (n === 0) {
          n = 1;
        } else if (n === 1) {
          n = 2;
        } else {
          n = Math.round(n * 1.5);
        }
      }
      if (n > max) {
        n = max;
      }
      const b = new Uint8Array(n);
      b.set(this.array_);
      this.array_ = b;
    }
  }

  resize(size) {
    SST_ASSERT((arguments.length === 1));
    SST_ASSERT((typeof (size) === "number"));
    SST_ASSERT((Number.isInteger(size)));
    SST_ASSERT((size >= 0));
    const max = Number.MAX_SAFE_INTEGER;
    if (size > max) {
      throw new Error("Safe integer range exceeded");
    }
    this.reserve(size);
    this.size_ = size;
  }

  size() {
    SST_ASSERT((arguments.length === 0));
    return this.size_;
  }

}; //
