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
import {} from "./json/dump.mjs";
import {} from "./SST_ASSERT.mjs";

globalThis.sst = globalThis.sst || {};

sst.post_json = async function(resource, body, options) {
  SST_ASSERT((arguments.length >= 2));
  SST_ASSERT((arguments.length <= 3));

  SST_ASSERT((typeof (resource) === "string"));

  // TODO: Verify that body is a JSON value.

  if (arguments.length < 3) {
    options = {};
  } else {
    SST_ASSERT((typeof (options) === "object"));
    options = {...options};
  }

  if (options.body === undefined) {
    options.body = sst.json.dump(body);
  }

  if (options.headers === undefined) {
    options.headers = {"content-type": "application/json"};
  } else if (options.headers instanceof Headers) {
    if (!options.headers.has("content-type")) {
      const headers = new Headers();
      for (const [k, v] of options.headers.entries()) {
        headers.set(k, v);
      }
      headers.set("content-type", "application/json");
      options.headers = headers;
    }
  } else {
    SST_ASSERT((typeof (options.headers) === "object"));
    let xs = Object.keys(options.headers);
    xs = xs.map(x => x.toLowerCase());
    xs = new Set(xs);
    if (!xs.has("content-type")) {
      const headers = new Headers();
      for (const [k, v] of Object.entries(options.headers)) {
        headers.set(k, v);
      }
      headers.set("content-type", "application/json");
      options.headers = headers;
    }
  }

  if (options.method === undefined) {
    options.method = "POST";
  }

  return sst.fetch(resource, options).then((response) => {
    if (!response.ok) {
      const e = new Error(response.statusText);
      e.response = response;
      throw e;
    }
    return response.json();
  });
}
