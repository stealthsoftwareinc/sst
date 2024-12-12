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

import {} from "./mix_in_container.mjs";

globalThis.sst = globalThis.sst || {};
sst.dom = sst.dom || {};

sst.dom.hideable = class hideable {

  //--------------------------------------------------------------------

  grid_;
  row_;

  //--------------------------------------------------------------------

  hidden_;

  hidden(x) {
    if (arguments.length === 0) {
      return this.hidden_;
    }
    SST_ASSERT((arguments.length === 1));
    SST_ASSERT((typeof (x) === "boolean"));
    if (x !== this.hidden_) {
      this.hidden_ = x;
      if (this.hidden_) {
        this.grid_.classList.add("sst_dom_hideable_hidden");
      } else {
        this.grid_.classList.remove("sst_dom_hideable_hidden");
      }
    }
  }

  //--------------------------------------------------------------------

  constructor(options = {}) {

    SST_ASSERT((arguments.length <= 1));
    SST_ASSERT((typeof (options) === "object"));
    SST_ASSERT((sst.is_subset(Object.keys(options), [
      "container",
      "hidden",
    ])));

    sst.dom.mix_in_container(this, {value: options.container});

    if (options.hidden === undefined) {
      this.hidden_ = false;
    } else {
      SST_ASSERT((typeof (options.hidden === "boolean")));
      this.hidden_ = options.hidden;
    }

    sst.dom.mix_in_container(this, {name: "content"});

    this.grid_ = document.createElement("div");
    this.container_.appendChild(this.grid_);
    this.grid_.classList.add("sst_dom_hideable");
    if (this.hidden_) {
      this.grid_.classList.add("sst_dom_hideable_hidden");
    }

    this.row_ = document.createElement("div");
    this.grid_.appendChild(this.row_);

    this.row_.appendChild(this.content_);

  } //

  //--------------------------------------------------------------------

}; //
