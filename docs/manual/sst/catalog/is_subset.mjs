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
import {} from "./SST_DEBUG.mjs";
import {} from "./SST_TEST_BOOL.mjs";

// TODO: Note that this function effectively ignores dupes in arrays,
//       i.e., it does not have multiset behavior. This is intentional.
//       Document this in the SST user manual.

// TODO: If we want multiset behavior, add another function
//       sst.is_submultiset() to the library.

globalThis.sst = globalThis.sst || {};

sst.is_subset = function(xs, ys) {
  SST_ASSERT((arguments.length === 2));
  if (xs instanceof Set) {
    xs = Array.from(xs);
  }
  SST_ASSERT((Array.isArray(xs)));
  if (ys instanceof Set) {
    ys = Array.from(ys);
  }
  SST_ASSERT((Array.isArray(ys)));
  return xs.every(x => ys.includes(x));
};

//----------------------------------------------------------------------
// Tests
//----------------------------------------------------------------------

if (SST_DEBUG) {

  let f = function(xs1, ys1, r) {
    const xs2 = `new Set(${xs1})`;
    const ys2 = `new Set(${ys1})`;
    SST_TEST_BOOL(`sst.is_subset(${xs1}, ${ys1}) === ${r}`);
    SST_TEST_BOOL(`sst.is_subset(${xs1}, ${ys2}) === ${r}`);
    SST_TEST_BOOL(`sst.is_subset(${xs2}, ${ys1}) === ${r}`);
    SST_TEST_BOOL(`sst.is_subset(${xs2}, ${ys2}) === ${r}`);
  };

  f(`[]`, `[]`, true);
  f(`[]`, `[0]`, true);
  f(`[0]`, `[]`, false);
  f(`[0]`, `[0]`, true);

} //
