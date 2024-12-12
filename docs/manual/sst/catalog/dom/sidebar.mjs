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

import {} from "../is_subset.mjs";
import {} from "../SST_ASSERT.mjs";

globalThis.sst = globalThis.sst || {};
sst.dom = sst.dom || {};

sst.dom.sidebar = class sidebar {

  //--------------------------------------------------------------------

  container_;

  container() {
    SST_ASSERT((arguments.length === 0));
    return this.container_;
  }

  //--------------------------------------------------------------------

  content_;

  content() {
    SST_ASSERT((arguments.length === 0));
    return this.content_;
  }

  //--------------------------------------------------------------------

  top_;

  top(x) {
    SST_ASSERT((arguments.length <= 1));
    if (arguments.length === 0) {
      return this.top_;
    }
    SST_ASSERT((typeof (x) === "string"));
    this.content_.style.setProperty("top", x);
    this.top_ = x;
  }

  //--------------------------------------------------------------------

  constructor(options = {}) {

    SST_ASSERT((arguments.length <= 1));
    SST_ASSERT((typeof (options) === "object"));
    SST_ASSERT((sst.is_subset(Object.keys(options), [
      "container",
      "top",
    ])));

    if (options.container === undefined) {
      this.container_ = document.createElement("div");
    } else {
      SST_ASSERT((options.container instanceof HTMLElement));
      SST_ASSERT((options.container.nodeName === "DIV"));
      this.container_ = options.container;
    }

    if (options.top === undefined) {
      this.top_ = "0";
    } else {
      SST_ASSERT((typeof (options.top) === "string"));
      this.top_ = options.top;
    }

    const box = document.createElement("div");
    box.style.setProperty("max-height", "100vh");
    box.style.setProperty("overflow", "auto");
    box.style.setProperty("position", "sticky");
    box.style.setProperty("top", this.top_);
    this.container_.appendChild(box);

    this.content_ = document.createElement("div");
    box.appendChild(this.content_);

  } //

}; //
