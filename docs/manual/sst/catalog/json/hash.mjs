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

import {} from "./dump.mjs";

globalThis.sst = globalThis.sst || {};
sst.json = sst.json || {};

sst.json.hash = async function(json, options) {

  if (options === undefined) {
    options = {};
  }

  let algorithm = "SHA-256";
  if (options.algorithm !== undefined) {
    algorithm = options.algorithm;
  }

  let crypto = undefined;
  if (options.crypto !== undefined) {
    crypto = options.crypto;
  }
  if (crypto === undefined) {
    if (globalThis.crypto !== undefined) {
      crypto = globalThis.crypto;
    } else {
      crypto = await import("node:crypto");
    }
  }

  const encoder = new TextEncoder();

  const data = encoder.encode(sst.json.dump(json));

  return crypto.subtle.digest(algorithm, data);

};
