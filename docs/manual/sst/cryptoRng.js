//
// Copyright (C) 2012-2023 Stealth Software Technologies, Inc.
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
// Note that the Web Cryptography API specification
// (<https://w3c.github.io/webcrypto/>) says that the getRandomValues
// method must throw an exception when the byteLength of the array is
// greater than 65536. We must be careful to not exceed this limit.
//

globalThis.sst = globalThis.sst || {};

globalThis.sst.cryptoRng = function(...args) {

  if (args.length == 1 && args[0] instanceof Uint8Array) {
    let i = 0;
    let n = args[0].byteLength;
    while (n > 0) {
      const k = Math.min(n, 65536);
      crypto.getRandomValues(args[0].subarray(i, k));
      i += k;
      n -= k;
    }
    return args[0];
  }

  throw new TypeError();

};
