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

import {} from "./is_subset.mjs";
import {} from "./SST_ASSERT.mjs";

globalThis.sst = globalThis.sst || {};

sst.mix_in_validity = function(object, options = {}) {
  SST_ASSERT((arguments.length >= 1));
  SST_ASSERT((arguments.length <= 2));
  SST_ASSERT((typeof (object) === "object"));
  SST_ASSERT((typeof (options) === "object"));
  SST_ASSERT((sst.is_subset(Object.keys(options), [
    "event_bubbles",
    "event_cancelable",
    "event_composed",
    "event_target",
    "validity",
  ])));
  const {
    event_bubbles,
    event_cancelable,
    event_composed,
    event_target,
    validity,
  } = options;
  SST_ASSERT((event_bubbles === undefined
              || typeof (event_bubbles) === "boolean"));
  SST_ASSERT((event_cancelable === undefined
              || typeof (event_cancelable) === "boolean"));
  SST_ASSERT((event_composed === undefined
              || typeof (event_composed) === "boolean"));
  SST_ASSERT((event_target === undefined
              || event_target instanceof EventTarget));
  SST_ASSERT((validity === undefined || validity === "valid"
              || validity === "invalid" || validity === "validating"));
  if (object.validity_ === undefined) {
    object.validity_event_target_ = event_target;
    object.validity_event_target = function() {
      SST_ASSERT((arguments.length === 0));
      return this.validity_event_target_;
    };
    object.validity_ = validity;
    object.validity = function(new_validity) {
      SST_ASSERT((arguments.length <= 1));
      if (arguments.length === 0) {
        return this.validity_;
      }
      SST_ASSERT((new_validity === "valid" || new_validity === "invalid"
                  || new_validity === "validating"));
      const old_validity = this.validity_;
      if (new_validity !== old_validity) {
        this.validity_ = new_validity;
        if (this.validity_event_target_ !== undefined) {
          this.validity_event_target_.dispatchEvent(
              new CustomEvent("sst_validity_event", {
                bubbles: event_bubbles,
                cancelable: event_cancelable,
                composed: event_composed,
                detail: {
                  object,
                  new_validity,
                  old_validity,
                },
              }));
        }
      }
    };
    object.valid = function() {
      SST_ASSERT((arguments.length === 0));
      return this.validity_ === "valid";
    };
    object.invalid = function() {
      SST_ASSERT((arguments.length === 0));
      return this.validity_ === "invalid";
    };
    object.validating = function() {
      SST_ASSERT((arguments.length === 0));
      return this.validity_ === "validating";
    };

    object.on_validity = function(callback) {
      SST_ASSERT((arguments.length === 1));
      SST_ASSERT((typeof (callback) === "function"));
      this.validity_event_target_.addEventListener(
          "sst_validity_event",
          (event) => { callback(event); });
    };

  } //
  SST_ASSERT((object.validity_event_target_ === event_target));
};
