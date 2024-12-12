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
// Do not try to use a "with" statement, as it is de facto deprecated.
//

import {} from "./SST_ASSERT.mjs";

globalThis.SST_TEST_BOOL = function(...args) {
  SST_ASSERT((arguments.length >= 1));
  let ctx;
  let code;
  let values;
  if (typeof (args[0]) === "string") {
    ctx = {};
    code = args[0];
    values = args.slice(1);
  } else {
    SST_ASSERT((arguments.length >= 2));
    ctx = args[0];
    code = args[1];
    values = args.slice(2);
  }
  SST_ASSERT((typeof (ctx) === "object"));
  SST_ASSERT((typeof (code) === "string"));
  if (!eval.call(ctx, code)) {
    let message = `Test failed: ${code}`;
    for (const value of values) {
      message += `\n  (${value}): ${eval.call(ctx, value)}`;
    }
    throw new Error(message);
  }
};
