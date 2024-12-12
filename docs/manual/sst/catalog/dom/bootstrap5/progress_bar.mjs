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

import {} from "../../is_subset.mjs";
import {} from "../../SST_ASSERT.mjs";
import {} from "../../SST_UNREACHABLE.mjs";
import {} from "../progress_value.mjs";

globalThis.sst = globalThis.sst || {};
sst.dom = sst.dom || {};
sst.dom.bootstrap5 = sst.dom.bootstrap5 || {};

sst.dom.bootstrap5.progress_bar = class progress_bar {

  //--------------------------------------------------------------------

  value_;

  max(...args) {
    const r = this.value_.max(...args);
    if (args.length > 0) {
      this.refresh_();
    }
    return r;
  }

  value(...args) {
    const r = this.value_.value(...args);
    if (args.length > 0) {
      this.refresh_();
    }
    return r;
  }

  percent(...args) {
    const r = this.value_.percent(...args);
    if (args.length > 0) {
      this.refresh_();
    }
    return r;
  }

  //--------------------------------------------------------------------

  container_;

  container() {
    SST_ASSERT((arguments.length === 0));
    return this.container_;
  }

  //--------------------------------------------------------------------

  label_type_;
  progress_;
  bar_;

  //--------------------------------------------------------------------

  error_ = false;

  error(x) {
    if (arguments.length === 0) {
      return this.error_;
    }
    SST_ASSERT((arguments.length === 1));
    SST_ASSERT((typeof (x) === "boolean"));
    if (x) {
      this.bar_.classList.add(
          "sst_dom_bootstrap5_progress_bar_error",
      );
    } else {
      this.bar_.classList.remove(
          "sst_dom_bootstrap5_progress_bar_error",
      );
    }
    this.error_ = x;
  }

  //--------------------------------------------------------------------

  refresh_() {
    SST_ASSERT((arguments.length === 0));
    const p = this.percent();
    if (this.bar_ !== undefined) {
      this.bar_.style.setProperty("width",
                                  `min(100%, max(4em, ${p}%))`);
      if (p === 100) {
        this.bar_.classList.add(
            "sst_dom_bootstrap5_progress_bar_green");
      } else {
        this.bar_.classList.remove(
            "sst_dom_bootstrap5_progress_bar_green");
      }
      if (this.label_type_ === "percent") {
        this.bar_.innerText = `${Math.floor(p)}%`;
      } else {
        this.bar_.innerText = "";
      }
    }
  }

  //--------------------------------------------------------------------

  spinning_ = false;

  spinning(x) {
    if (arguments.length === 0) {
      return this.spinning_;
    }
    SST_ASSERT((arguments.length === 1));
    SST_ASSERT((typeof (x) === "boolean"));
    if (x) {
      this.bar_.classList.add("progress-bar-animated");
    } else {
      this.bar_.classList.remove("progress-bar-animated");
    }
    this.spinning_ = x;
  }

  //--------------------------------------------------------------------

  constructor(options = {}) {

    SST_ASSERT((arguments.length <= 1));
    SST_ASSERT((typeof (options) === "object"));
    SST_ASSERT((sst.is_subset(Object.keys(options), [
      "container",
      "label_type",
      "max",
      "percent",
      "value",
    ])));

    this.value_ = new sst.dom.progress_value({
      max: options.max,
      percent: options.percent,
      value: options.value,
    });

    SST_ASSERT((options.container === undefined
                || (options.container instanceof HTMLElement
                    && options.container.nodeName === "DIV")));
    if (options.container === undefined) {
      this.container_ = document.createElement("div");
    } else {
      this.container_ = options.container;
    }

    this.progress_ = document.createElement("div");
    this.container_.appendChild(this.progress_);
    this.progress_.classList.add("progress");

    this.bar_ = document.createElement("div");
    this.progress_.appendChild(this.bar_);
    this.bar_.classList.add(
        "progress-bar",
        "progress-bar-striped",
    );

    SST_ASSERT(([
      undefined,
      "percent",
    ].includes(options.label_type)));
    if (options.label_type === undefined) {
      this.label_type_ = "percent";
    } else {
      this.label_type_ = options.label_type;
    }

    this.refresh_();

  } //

  //--------------------------------------------------------------------

}; //
