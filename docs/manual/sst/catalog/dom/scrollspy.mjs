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

// TODO: Document that, if container is specified and is not window, it
//       should be the closest scrollable ancestor of all items,
//       otherwise funny stuff can happen.

import {} from "../is_subset.mjs";
import {} from "../SST_ASSERT.mjs";

globalThis.sst = globalThis.sst || {};
sst.dom = sst.dom || {};

sst.dom.scrollspy = function(items, callback, options = {}) {
  SST_ASSERT((arguments.length >= 2));
  SST_ASSERT((arguments.length <= 3));

  // TODO: Surely we should handle the items parameter being a single
  //       object (typically HTMLElement) instead of being an array of
  //       objects? But what do we do about the callback parameters in
  //       that case? Should they be simplified too?

  // TODO: Array.from() silently returns an empty array for silly calls
  //       like Array.from(1234).

  if (!Array.isArray(items)) {
    items = Array.from(items);
  }

  // Items can be any objects with getBoundingClientRect, not just
  // instances of Element. This allows custom items, which is useful.
  SST_ASSERT(
      (items.every(item => (typeof (item) === "object"
                            && typeof (item.getBoundingClientRect)
                                   === "function"))));

  SST_ASSERT((typeof (options) === "object"));
  SST_ASSERT((sst.is_subset(Object.keys(options), [
    "container",
    "omit_handler_call",
  ])));

  SST_ASSERT((options.container === undefined
              || options.container === window
              || options.container instanceof HTMLElement));
  const container =
      options.container === undefined ? window : options.container;

  SST_ASSERT((options.omit_handler_call === undefined
              || typeof (options.omit_handler_call) === "boolean"));
  const omit_handler_call = !!options.omit_handler_call;

  const rv = {};

  const handler = function() {
    const active_items = [];
    const inactive_items = [];
    const a =
        container === window ?
            new DOMRect(0, 0, window.innerWidth, window.innerHeight) :
            container.getBoundingClientRect();
    for (const item of items) {
      const b = item.getBoundingClientRect();
      if (a.left < b.right && a.right > b.left && a.top < b.bottom
          && a.bottom > b.top) {
        active_items.push(item);
      } else {
        inactive_items.push(item);
      }
    }
    const r = callback(active_items, inactive_items);
    SST_ASSERT((r === undefined));
  };
  rv.handler = handler;

  if (!omit_handler_call) {
    handler();
  }

  const destroy_functions = [];
  const destroy = function() {
    try {
      for (const f of destroy_functions) {
        if (f !== undefined) {
          try {
            f();
          } catch (e) {
          }
        }
      }
    } catch (e) {
    }
  };
  rv.destroy = destroy;

  try {

    {
      const f = function() {
        container.removeEventListener("scroll", handler);
      };
      destroy_functions.push(undefined);
      container.addEventListener("scroll", handler);
      destroy_functions[destroy_functions.length - 1] = f;
    }

    if (container === window) {
      const f = function() {
        container.removeEventListener("resize", handler);
      };
      destroy_functions.push(undefined);
      container.addEventListener("resize", handler);
      destroy_functions[destroy_functions.length - 1] = f;
    } else {
      const observer = new ResizeObserver(handler);
      const f = function() {
        observer.unobserve(container);
      };
      destroy_functions.push(undefined);
      observer.observe(container);
      destroy_functions[destroy_functions.length - 1] = f;
    }

  } catch (e) {
    destroy();
    throw e;
  }

  return rv;
};
