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
import {} from "../reduce_motion.mjs";
import {} from "../SST_ASSERT.mjs";
import {} from "../SST_UNREACHABLE.mjs";

globalThis.sst = globalThis.sst || {};
sst.dom = sst.dom || {};

// TODO: Document this important styling guarantee: list.container()
//       will contain exactly one element per list item. It will not
//       contain any other elements. This means if you use
//       list.container().classList.add("my_list"), you can use CSS
//       selectors like .my_list > :first-child for styling.

sst.dom.list_item = class list_item {

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
  // custom()
  //--------------------------------------------------------------------
  //
  // Returns a persistent plain object that the caller can use to store
  // whatever they like.
  //

  custom_ = {};

  custom() {
    SST_ASSERT((arguments.length === 0));
    return this.custom_;
  }

  //--------------------------------------------------------------------
  // index()
  //--------------------------------------------------------------------
  //
  // Returns the index of this item in the containing list.
  //

  index() {
    SST_ASSERT((arguments.length === 0));
    return this.list_.index(this);
  }

  //--------------------------------------------------------------------

  list_;

  list() {
    SST_ASSERT((arguments.length === 0));
    return this.list_;
  }

  //--------------------------------------------------------------------

  next() {
    SST_ASSERT((arguments.length === 0));
    const i = this.list_.index(this);
    if (i + 1 < this.list_.size()) {
      return this.list_.item(i + 1);
    }
    return undefined;
  }

  //--------------------------------------------------------------------

  prev() {
    SST_ASSERT((arguments.length === 0));
    const i = this.list_.index(this);
    if (i - 1 >= 0) {
      return this.list_.item(i - 1);
    }
    return undefined;
  }

  //--------------------------------------------------------------------

  constructor(options = {}) {

    SST_ASSERT((arguments.length <= 1));
    SST_ASSERT((typeof (options) === "object"));
    SST_ASSERT((sst.is_subset(Object.keys(options), [
      "container",
      "list",
    ])));

    if (options.container === undefined) {
      this.container_ = document.createElement("div");
    } else {
      SST_ASSERT((options.container instanceof HTMLElement));
      SST_ASSERT((options.container.nodeName === "DIV"));
      this.container_ = options.container;
    }

    SST_ASSERT((options.list instanceof sst.dom.list));
    this.list_ = options.list;

    this.content_ = document.createElement("div");
    this.container_.appendChild(this.content_);

  } //

  //--------------------------------------------------------------------

}; //

sst.dom.list = class list {

  //--------------------------------------------------------------------

  container_;

  container() {
    SST_ASSERT((arguments.length === 0));
    return this.container_;
  }

  //--------------------------------------------------------------------

  fadeout_events_;

  items_;

  index(i) {
    SST_ASSERT((arguments.length === 1));
    if (typeof (i) === "number") {
      SST_ASSERT((Number.isSafeInteger(i)));
      SST_ASSERT((i >= 0));
      SST_ASSERT((i < this.items_.length));
      return i;
    }
    if (i instanceof sst.dom.list_item) {
      const j = this.items_.indexOf(i);
      SST_ASSERT((j >= 0));
      return j;
    }
    if (i instanceof HTMLElement) {
      SST_ASSERT((i.nodeName === "DIV"));
      const j = this.items_.findIndex(x => x.container() === i);
      SST_ASSERT((j >= 0));
      return j;
    }
    SST_UNREACHABLE();
  }

  size() {
    SST_ASSERT((arguments.length === 0));
    return this.items_.length;
  }

  item(i) {
    SST_ASSERT((arguments.length === 1));
    i = this.index(i);
    return this.items_[i];
  }

  [Symbol.iterator]() {
    const items = this.items_;
    let i = -1;
    return {
      next() {
        if (i + 1 >= items.length) {
          return {done: true};
        }
        ++i;
        return {value: items[i]};
      },
    };
  }

  add(i) {
    if (arguments.length === 0) {
      i = this.items_.length;
    } else {
      SST_ASSERT((arguments.length === 1));
      if (i !== this.items_.length) {
        i = this.index(i);
      }
    }
    const item = new sst.dom.list_item({list: this});
    const items = this.items_.slice();
    items.splice(i, 0, item);
    const fader = document.createElement("div");
    fader.classList.add("sst_dom_list_fader");
    setTimeout(() => {
      if (!fader.classList.contains("sst_dom_list_fader_hide")) {
        fader.classList.add("sst_dom_list_fader_show");
      }
    }, 0);
    fader.prepend(item.container());
    if (i === 0) {
      this.container_.prepend(fader);
    } else {
      this.items_[i - 1].container().parentElement.after(fader);
    }
    this.items_ = items;
    return item;
  }

  remove(i) {
    SST_ASSERT((arguments.length === 1));
    i = this.index(i);
    const items = this.items_.slice();
    items.splice(i, 1);
    const fader = this.items_[i].container().parentElement;
    fader.style.setProperty("pointer-events", "none");
    for (const event of this.fadeout_events_) {
      fader.addEventListener(
          event,
          event => { event.stopImmediatePropagation(); },
          true);
    }
    setTimeout(() => {
      fader.classList.remove("sst_dom_list_fader_show");
      fader.classList.add("sst_dom_list_fader_hide");
      setTimeout(() => { fader.remove(); }, 10000);
    }, 0);
    this.items_ = items;
  }

  move(i, j) {
    SST_ASSERT((arguments.length === 2));
    i = this.index(i);
    if (j !== this.items_.length) {
      j = this.index(j);
    }
    if (i === j || i === j - 1) {
      return;
    }
    const items = this.items_.slice();
    items.splice(j - (i < j ? 1 : 0), 0, items.splice(i, 1)[0]);
    const fader_i = this.items_[i].container().parentElement;
    const fader_j = j === this.items_.length ?
                        undefined :
                        this.items_[j].container().parentElement;

    const h1 = fader_i.getBoundingClientRect().height;

    let h2 = 0;
    if (i < j) {
      for (let k = i + 1; k < j; ++k) {
        const fader_k = this.items_[k].container().parentElement;
        h2 += fader_k.getBoundingClientRect().height;
      }
    } else {
      for (let k = j; k < i; ++k) {
        const fader_k = this.items_[k].container().parentElement;
        h2 += fader_k.getBoundingClientRect().height;
      }
    }

    if (fader_j) {
      fader_j.before(fader_i);
    } else {
      this.container_.appendChild(fader_i);
    }

    if (!sst.reduce_motion()) {
      if (i < j) {
        fader_i.classList.add("sst_dom_list_fader_jump");
        fader_i.style.setProperty("transform", `translateY(-${h2}px)`);
        for (let k = i + 1; k < j; ++k) {
          const fader_k = this.items_[k].container().parentElement;
          fader_k.classList.add("sst_dom_list_fader_jump");
          fader_k.style.setProperty("transform", `translateY(${h1}px)`);
        }
      } else {
        fader_i.classList.add("sst_dom_list_fader_jump");
        fader_i.style.setProperty("transform", `translateY(${h2}px)`);
        for (let k = j; k < i; ++k) {
          const fader_k = this.items_[k].container().parentElement;
          fader_k.classList.add("sst_dom_list_fader_jump");
          fader_k.style.setProperty("transform",
                                    `translateY(-${h1}px)`);
        }
      }
      const snapshot = this.items_.slice();
      setTimeout(() => {
        if (i < j) {
          fader_i.classList.remove("sst_dom_list_fader_jump")
          fader_i.style.setProperty("transform", `translateY(0)`);
          for (let k = i + 1; k < j; ++k) {
            const fader_k = snapshot[k].container().parentElement;
            fader_k.classList.remove("sst_dom_list_fader_jump")
            fader_k.style.setProperty("transform", `translateY(0)`);
          }
        } else {
          fader_i.classList.remove("sst_dom_list_fader_jump")
          fader_i.style.setProperty("transform", `translateY(0)`);
          for (let k = j; k < i; ++k) {
            const fader_k = snapshot[k].container().parentElement;
            fader_k.classList.remove("sst_dom_list_fader_jump")
            fader_k.style.setProperty("transform", `translateY(0)`);
          }
        }
      }, 0);
    }

    this.items_ = items;
  }

  //--------------------------------------------------------------------

  constructor(options = {}) {

    SST_ASSERT((arguments.length <= 1));
    SST_ASSERT((typeof (options) === "object"));
    SST_ASSERT((sst.is_subset(Object.keys(options), [
      "container",
      "fadeout_events",
    ])));

    if (options.container === undefined) {
      this.container_ = document.createElement("div");
    } else {
      SST_ASSERT((options.container instanceof HTMLElement));
      SST_ASSERT((options.container.nodeName === "DIV"));
      this.container_ = options.container;
    }

    if (options.fadeout_events === undefined) {
      this.fadeout_events_ = [
        "click",
        "input",
      ];
    } else {
      SST_ASSERT((Array.isArray(options.fadeout_events)));
      SST_ASSERT(
          (options.fadeout_events.every(x => typeof (x) === "string")));
      this.fadeout_events_ = options.fadeout_events.slice();
    }

    this.items_ = [];

  } //

  //--------------------------------------------------------------------

}; //
