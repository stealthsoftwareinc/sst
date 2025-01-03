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

globalThis.sst = globalThis.sst || {};

sst.is_integer_ish = function(x) {
  SST_ASSERT((arguments.length === 1));
  return Number.isSafeInteger(x) || typeof (x) === "bigint";
};

//----------------------------------------------------------------------
// Tests
//----------------------------------------------------------------------

if (SST_DEBUG) {

  SST_TEST_BOOL(`sst.is_integer_ish(-1) === true`);
  SST_TEST_BOOL(`sst.is_integer_ish(0) === true`);
  SST_TEST_BOOL(`sst.is_integer_ish(1) === true`);

  SST_TEST_BOOL(
      `sst.is_integer_ish(-Number.MAX_SAFE_INTEGER - 1) === false`);
  SST_TEST_BOOL(
      `sst.is_integer_ish(-Number.MAX_SAFE_INTEGER) === true`);
  SST_TEST_BOOL(
      `sst.is_integer_ish(-Number.MAX_SAFE_INTEGER + 1) === true`);

  SST_TEST_BOOL(
      `sst.is_integer_ish(Number.MAX_SAFE_INTEGER - 1) === true`);
  SST_TEST_BOOL(`sst.is_integer_ish(Number.MAX_SAFE_INTEGER) === true`);
  SST_TEST_BOOL(
      `sst.is_integer_ish(Number.MAX_SAFE_INTEGER + 1) === false`);

  SST_TEST_BOOL(`sst.is_integer_ish(-1n) === true`);
  SST_TEST_BOOL(`sst.is_integer_ish(0n) === true`);
  SST_TEST_BOOL(`sst.is_integer_ish(1n) === true`);

  SST_TEST_BOOL(
      `sst.is_integer_ish(-123456789012345678901234567890n) === true`);
  SST_TEST_BOOL(
      `sst.is_integer_ish(123456789012345678901234567890n) === true`);

  SST_TEST_BOOL(`sst.is_integer_ish(0.5) === false`);
  SST_TEST_BOOL(`sst.is_integer_ish(new Number(0)) === false`);
  SST_TEST_BOOL(`sst.is_integer_ish(true) === false`);
  SST_TEST_BOOL(`sst.is_integer_ish(null) === false`);
  SST_TEST_BOOL(`sst.is_integer_ish({}) === false`);

} //
