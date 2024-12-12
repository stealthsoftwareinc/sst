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

import {} from "./is_filehandle.mjs";
import {} from "./is_stream_writable.mjs";
import {} from "./SST_ASSERT.mjs";
import {} from "./SST_UNREACHABLE.mjs";

globalThis.sst = globalThis.sst || {};

sst.write = function(src, dst, options = {}) {
  SST_ASSERT((arguments.length >= 2));
  SST_ASSERT((arguments.length <= 3));
  SST_ASSERT((typeof (options) === "object"));
  if (options.async !== undefined) {
    SST_ASSERT((typeof (options.async) === "boolean"));
  }
  if (options.callback !== undefined) {
    SST_ASSERT((options.callback === null
                || typeof (options.callback) === "function"));
  }
  if (options.fs !== undefined) {
    SST_ASSERT((typeof (options.fs) === "object"));
  }
  if (options.encoding !== undefined) {
    SST_ASSERT((typeof (options.encoding) === "string"));
    SST_ASSERT((typeof (src) === "string"));
  }
  if (sst.is_filehandle(dst)) {
    // TODO: Check the type of src?
    SST_ASSERT((options.callback === undefined));
    if (typeof (src) === "string") {
      const args = [src];
      if (options.encoding !== undefined) {
        args.push(options.encoding);
      }
      src = Buffer.from(...args);
    }
    if (options.async) {
      return dst.write(src).then(() => undefined);
    }
    SST_ASSERT((options.fs !== undefined));
    options.fs.writeSync(dst.fd, src);
    return undefined;
  }
  if (sst.is_stream_writable(dst)) {
    // TODO: Check the type of src?
    if (options.async) {
      SST_ASSERT((options.callback === undefined));
    } else {
      SST_ASSERT(
          (options.callback !== undefined),
          ("sst.write(): dst is a stream.Writable and you omitted options.callback, which is usually a mistake. stream.Writable does not support normal synchronous writing behavior. Instead, it unboundedly accumulates data into memory and returns false to indicate that you should slow down. If you really want this behavior with no completion callback, you can explicitly specify options.callback = null."));
    }
    const args = [src];
    if (options.encoding !== undefined) {
      args.push(options.encoding);
    }
    if (options.callback) {
      args.push(options.callback);
    }
    const pressure = !dst.write(...args);
    if (!options.async) {
      return !pressure;
    }
    if (!pressure) {
      return undefined;
    }
    return new Promise((resolve, reject) => {
      let on_drain;
      let on_error;
      on_drain = () => {
        dst.removeListener("error", on_error);
        resolve(undefined);
      };
      on_error = (e) => {
        dst.removeListener("drain", on_drain);
        reject(e);
      };
      dst.once("drain", on_drain);
      dst.once("error", on_error);
    });
  }
  SST_UNREACHABLE();
};
