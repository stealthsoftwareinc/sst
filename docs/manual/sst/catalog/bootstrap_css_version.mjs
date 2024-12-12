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

sst.bootstrap_css_version = async function(options = {}) {
  SST_ASSERT((arguments.length >= 0));
  SST_ASSERT((arguments.length <= 1));
  SST_ASSERT((typeof (options) === "object"));
  if (!options.recache
      && sst.bootstrap_css_version.cache !== undefined) {
    return sst.bootstrap_css_version.cache;
  }
  if (sst.in_browser()) {
    for (const child of document.head.children) {
      if (child.tagName === "LINK" && child.rel === "stylesheet") {
        if (child.href.includes("bootstrap")) {
          const response = await sst.fetch(child.href);
          const text = await response.text();
          {
            const match = text.match(
                /^@charset "UTF-8";\/\*!\n \* Bootstrap  v((0|[1-9][0-9]*).(0|[1-9][0-9]*).(0|[1-9][0-9]*)) /);
            if (match) {
              sst.bootstrap_css_version.cache = match[1];
              return sst.bootstrap_css_version.cache;
            }
          }
        }
      }
    }
  }
  sst.bootstrap_css_version.cache = null;
  return sst.bootstrap_css_version.cache;
}
