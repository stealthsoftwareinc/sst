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

sst.test_e = async function(path, options) {
  SST_ASSERT((arguments.length >= 1));
  SST_ASSERT((arguments.length <= 2));

  SST_ASSERT((typeof (path) === "string"));

  if (arguments.length < 2) {
    options = {};
  } else if (typeof (options) === "boolean") {
    options = {follow_links: options};
  }
  SST_ASSERT((typeof (options) === "object"));

  let follow_links = true;
  if (options.follow_links !== undefined) {
    SST_ASSERT((typeof (options.follow_links) === "boolean"));
    follow_links = options.follow_links;
  }

  const fsp = await import("node:fs/promises");

  let x = undefined;
  if (follow_links) {
    x = fsp.stat(path);
  } else {
    x = fsp.lstat(path);
  }
  x = x.then(v => true);
  x = x.catch(e => {
    if (e.code !== "ENOENT" && e.code !== "ENOTDIR") {
      throw e;
    }
    return false;
  });
  return x;
};
