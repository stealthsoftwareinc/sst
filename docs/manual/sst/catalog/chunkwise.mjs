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

import {} from "./fetch.mjs";
import {} from "./in_browser.mjs";
import {} from "./SST_ASSERT.mjs";

globalThis.sst = globalThis.sst || {};

sst.chunkwise = async function(src, f, options) {
  SST_ASSERT((arguments.length >= 2));
  SST_ASSERT((arguments.length <= 3));
  SST_ASSERT((typeof (f) === "function"));
  if (arguments.length < 3) {
    options = {};
  } else {
    SST_ASSERT((typeof (options) === "object"));
    options = Object.assign({}, options);
  }
  if (options.fetch !== undefined) {
    SST_ASSERT((typeof (options.fetch) === "object"));
    SST_ASSERT((typeof (src) === "string"));
    const response = await sst.fetch(src, options.fetch);
    if (!response.ok) {
      const e = new Error(response.statusText);
      e.response = response;
      throw e;
    }
    delete options.fetch;
    await sst.chunkwise(response.body, f, options);
    return;
  }
  const in_browser = sst.in_browser();
  if (in_browser && src instanceof File) {
    try {
      await sst.chunkwise(src.stream(), f, options);
    } catch (e) {
      throw new Error("Error while reading file "
                          + JSON.stringify(src.name),
                      {cause: e});
    }
    return;
  }
  if (src instanceof Blob) {
    await sst.chunkwise(src.stream(), f, options);
    return;
  }
  if (!in_browser && typeof (src) === "object"
      && typeof (src.createReadStream) === "function") {
    // src instanceof fsp.FileHandle
    await sst.chunkwise(src.createReadStream(), f, options);
    return;
  }
  if (!in_browser && typeof (src) === "object"
      && typeof (src.bytesRead) === "number") {
    // src instanceof fsp.ReadStream
    const stream = await import("node:stream");
    await sst.chunkwise(stream.Readable.toWeb(src), f, options);
    return;
  }
  if (src instanceof ReadableStream) {
    const reader = src.getReader();
    while (true) {
      const r = await reader.read();
      if (r.done) {
        break;
      }
      if (r.value instanceof ArrayBuffer) {
        r.value = new Uint8Array(r.value);
      }
      await f(r.value);
    }
    return;
  }
  if (!in_browser && typeof (src) === "string") {
    const fsp = await import("node:fs/promises");
    let handle;
    try {
      handle = await fsp.open(src, "r");
    } catch (e) {
      throw new Error("Error opening file " + JSON.stringify(src),
                      {cause: e});
    }
    try {
      await sst.chunkwise(handle, f, options);
    } catch (e) {
      throw new Error("Error while reading file " + JSON.stringify(src),
                      {cause: e});
    }
    return;
  }
  if (src instanceof ArrayBuffer) {
    src = new Uint8Array(src);
  }
  await f(src);
};
