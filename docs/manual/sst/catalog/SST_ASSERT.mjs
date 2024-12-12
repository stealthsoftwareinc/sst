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

import {} from "./assertion_exception.mjs";
import {} from "./in_browser.mjs";
import {} from "./SST_DEBUG.mjs";
import {} from "./SST_USE_ASSERTION_EXCEPTION.mjs";

globalThis.sst = globalThis.sst || {};

const null_error = {};

globalThis.SST_ASSERT = function(x, message) {
  if (!SST_DEBUG) {
    return;
  }
  if (x instanceof sst.assertion_exception) {
    throw x;
  }
  if (x instanceof Error || x === null_error) {
    const m = message !== undefined ? String(message) : undefined;
    const c = x instanceof Error ? x : undefined;
    const e = new sst.assertion_exception(m, c);
    if (SST_USE_ASSERTION_EXCEPTION || sst.in_browser()) {
      throw e;
    }
    // TODO: Coloring? Would sst.barf() make sense here?
    console.error(e);
    process.abort();
  }
  try {
    let fail;
    if (typeof (x) === "function") {
      fail = !x();
    } else {
      fail = !x;
    }
    if (fail) {
      SST_ASSERT(null_error, message);
    }
  } catch (e) {
    SST_ASSERT(e);
  }
}
