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

globalThis.sst = globalThis.sst || {};

sst.is_json = function(x) {
  SST_ASSERT((arguments.length === 1));
  if (typeof (x) === "string") {
    return true;
  }
  if (Number.isFinite(x)) {
    return true;
  }
  if (typeof (x) === "boolean") {
    return true;
  }
  if (x === null) {
    return true;
  }
  if (Array.isArray(x)) {
    for (let i = 0; i < x.length; ++i) {
      if (!sst.is_json(x[i])) {
        return false;
      }
    }
    return true;
  }
  if (x?.constructor === Object) {
    for (const i in x) {
      if (!sst.is_json(x[i])) {
        return false;
      }
    }
    return true;
  }
  return false;
};

//----------------------------------------------------------------------
// Tests
//----------------------------------------------------------------------

if (SST_DEBUG) {

  await import("./SST_TEST_BOOL.mjs");

  SST_TEST_BOOL((`sst.is_json("") === true`));
  SST_TEST_BOOL((`sst.is_json(0) === true`));
  SST_TEST_BOOL((`sst.is_json(0.5) === true`));
  SST_TEST_BOOL((`sst.is_json(true) === true`));
  SST_TEST_BOOL((`sst.is_json(false) === true`));
  SST_TEST_BOOL((`sst.is_json(null) === true`));
  SST_TEST_BOOL((`sst.is_json([]) === true`));
  SST_TEST_BOOL((`sst.is_json([0]) === true`));
  SST_TEST_BOOL((`sst.is_json({}) === true`));
  SST_TEST_BOOL((`sst.is_json({x: 0}) === true`));

  SST_TEST_BOOL((`sst.is_json(undefined) === false`));
  SST_TEST_BOOL((`sst.is_json(Infinity) === false`));
  SST_TEST_BOOL((`sst.is_json(NaN) === false`));
  SST_TEST_BOOL((`sst.is_json(0n) === false`));
  SST_TEST_BOOL((`sst.is_json([undefined]) === false`));
  SST_TEST_BOOL((`sst.is_json({x: undefined}) === false`));

} //
