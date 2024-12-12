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

sst.dom.mix_in_container = function(object, options = {}) {
  SST_ASSERT((arguments.length >= 1));
  SST_ASSERT((arguments.length <= 2));
  SST_ASSERT((typeof (object) === "object"));
  SST_ASSERT((typeof (options) === "object"));
  SST_ASSERT((sst.is_subset(Object.keys(options), [
    "name",
    "tag",
    "value",
  ])));

  const name = (() => {
    if (options.name === undefined) {
      return "container";
    }
    SST_ASSERT((typeof (options.name) === "string"));
    return options.name;
  })();

  const name_ = name + "_";

  const tag = (() => {
    if (options.tag === undefined) {
      return "div";
    }
    SST_ASSERT((typeof (options.tag) === "string"));
    return options.tag;
  })();

  if (options.value !== undefined) {
    SST_ASSERT((options.value instanceof HTMLElement));
    SST_ASSERT((options.value.nodeName === tag.toUpperCase()));
  }

  if (object[name_] === undefined) {
    if (options.value === undefined) {
      object[name_] = document.createElement(tag);
    } else {
      object[name_] = options.value;
    }
    object[name] = function() {
      SST_ASSERT((arguments.length === 0));
      return this[name_];
    };
  }

  SST_ASSERT((object[name_] instanceof HTMLElement));
  SST_ASSERT((object[name_].nodeName === tag.toUpperCase()));
  SST_ASSERT((typeof (object[name]) === "function"));
  SST_ASSERT((object[name]() === object[name_]));
};
