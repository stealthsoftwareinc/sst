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

import {} from "./in_browser.mjs";
import {} from "./SST_ASSERT.mjs";

globalThis.sst = globalThis.sst || {};

sst.fetch = async function(...args) {
  SST_ASSERT((args.length >= 1));
  SST_ASSERT((args.length <= 2));

  const resource = args[0];
  SST_ASSERT((typeof (resource) === "string"));

  const options = {};
  if (args.length === 2) {
    SST_ASSERT((typeof (args[1]) === "object"));
    Object.assign(options, args[1]);
  }

  const insecure = !!options.insecure;
  delete options.insecure;

  let fetch = globalThis.fetch;

  if (insecure
      && (resource.startsWith("https:")
          || (!resource.startsWith("http:") && sst.in_browser()
              && window.location.protocol === "https:"))) {
    if (sst.in_browser()) {
      throw new Error("HTTPS certificate validation " +
                      "cannot be skipped in a browser");
    }
    SST_ASSERT((!sst.in_browser()));
    const https = await import("node:https");
    options.agent = new https.Agent({rejectUnauthorized: false});
    fetch = (await import("node-fetch")).default;
  }

  return fetch(resource, options);
}
