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

// TODO: Implement the "sst_height_guide" class. It will need
//       display:inline-block.
// TODO: Implement the "sst_dom_bootstrap5_is_validating" class.

import {} from "../../debounce.mjs";
import {} from "../../is_subset.mjs";
import {} from "../../mix_in_validity.mjs";
import {} from "../../SST_ASSERT.mjs";
import {} from "../../SST_UNREACHABLE.mjs";
import {} from "../id.mjs";

globalThis.sst = globalThis.sst || {};
sst.dom = sst.dom || {};
sst.dom.bootstrap5 = sst.dom.bootstrap5 || {};

sst.dom.bootstrap5.text_input = class text_input {

  multiline_;

  //--------------------------------------------------------------------

  container_;

  container() {
    SST_ASSERT((arguments.length === 0));
    return this.container_;
  }

  //--------------------------------------------------------------------

  input_group_;
  form_floating_;
  input_;

  //--------------------------------------------------------------------
  // input()
  //--------------------------------------------------------------------

  input() {
    SST_ASSERT((arguments.length === 0));
    return this.input_;
  }

  //--------------------------------------------------------------------
  // input_group_item()
  //--------------------------------------------------------------------
  //
  // Returns the HTMLElement x such that you can insert siblings before
  // or after x to add elements to the input group [1]. By default, the
  // input group only contains x.
  //
  // [1] https://getbootstrap.com/docs/5.3/forms/input-group/
  //

  input_group_item() {
    SST_ASSERT((arguments.length === 0));
    if (this.form_floating_ !== undefined) {
      return this.form_floating_;
    }
    return this.input_;
  }

  //--------------------------------------------------------------------

  label_;
  label_when_empty_;
  label_is_html_;
  label_element_;
  label_span_1_;
  label_span_2_;
  label_pencil_;

  feedback_;
  feedback_div_;
  validator_;
  validator_is_html_;

  //--------------------------------------------------------------------

  label_type_;

  //--------------------------------------------------------------------

  disabled_;
  committed_;

  refresh_() {
    SST_ASSERT((arguments.length === 0));
    if (this.committed_) {
      this.input_.disabled = false;
      this.input_.readOnly = true;
      switch (this.label_type_) {
        case "floating": {
          this.input_.classList.remove("form-control");
          this.input_.classList.add("form-control-plaintext");
          if (this.label_pencil_ !== undefined) {
            this.label_pencil_.style.setProperty("opacity", "0");
          }
        } break;
        default:
          SST_UNREACHABLE();
      }
    } else {
      this.input_.disabled = this.disabled_;
      this.input_.readOnly = false;
      switch (this.label_type_) {
        case "floating": {
          this.input_.classList.remove("form-control-plaintext");
          this.input_.classList.add("form-control");
          if (this.label_pencil_ !== undefined) {
            this.label_pencil_.style.setProperty("opacity", "1");
          }
        } break;
        default:
          SST_UNREACHABLE();
      }
    }
  }

  disabled(x) {
    SST_ASSERT((arguments.length <= 1));
    if (arguments.length === 0) {
      return this.disabled_;
    }
    SST_ASSERT((typeof (x) === "boolean"));
    this.disabled_ = x;
    this.refresh_();
  }

  committed(x) {
    SST_ASSERT((arguments.length <= 1));
    if (arguments.length === 0) {
      return this.committed_;
    }
    SST_ASSERT((typeof (x) === "boolean"));
    this.committed_ = x;
    this.refresh_();
  }

  //--------------------------------------------------------------------
  // value([x])
  //--------------------------------------------------------------------
  //
  // Gets or sets the value.
  //

  value(x) {
    SST_ASSERT((arguments.length <= 1));
    if (arguments.length === 0) {
      return this.input_.value;
    }
    SST_ASSERT((typeof (x) === "string"));
    this.input_.value = x;
    this.input_.dispatchEvent(new Event("input", {bubbles: true}));
  }

  //--------------------------------------------------------------------
  // input_height_guide()
  //--------------------------------------------------------------------
  //
  // Returns a newly created element with the same height as the input
  // element and zero width.
  //

  input_height_guide_;

  input_height_guide() {
    SST_ASSERT((!this.multiline_));
    SST_ASSERT((arguments.length === 0));
    return this.input_height_guide_.cloneNode(true);
  }

  //--------------------------------------------------------------------

  constructor(options = {}) {

    SST_ASSERT((arguments.length <= 1));
    SST_ASSERT((typeof (options) === "object"));
    SST_ASSERT((sst.is_subset(Object.keys(options), [
      "committed",
      "container",
      "disabled",
      "label",
      "label_is_html",
      "label_type",
      "label_when_empty",
      "multiline",
      "placeholder",
      "spellcheck",
      "validator",
      "validator_is_html",
      "validity",
      "value",
    ])));

    SST_ASSERT((options.container === undefined
                || (options.container instanceof HTMLElement
                    && options.container.nodeName === "DIV")));
    if (options.container === undefined) {
      this.container_ = document.createElement("div");
    } else {
      this.container_ = options.container;
    }

    this.input_group_ = document.createElement("div");
    this.input_group_.classList.add(
        "input-group",
        "has-validation",
    );
    this.container_.appendChild(this.input_group_);

    SST_ASSERT((options.multiline === undefined
                || typeof (options.multiline) === "boolean"));
    this.multiline_ = !!options.multiline;

    if (this.multiline_) {
      this.input_ = document.createElement("textarea");
    } else {
      this.input_ = document.createElement("input");
    }
    this.input_.setAttribute("type", "text");
    this.input_.classList.add("form-control");

    if (options.value === undefined) {
      this.input_.value = "";
    } else {
      SST_ASSERT((typeof (options.value) === "string"));
      this.input_.value = options.value;
    }

    SST_ASSERT((options.spellcheck === undefined
                || typeof (options.spellcheck) === "boolean"));
    this.input_.spellcheck = !!options.spellcheck;

    this.feedback_ = document.createElement("div");
    this.feedback_.classList.add(
        "invalid-feedback",
        "sst_dom_bootstrap5_animate_height",
    );

    this.feedback_div_ = document.createElement("div");
    this.feedback_.appendChild(this.feedback_div_);

    SST_ASSERT((options.validity === undefined
                || options.validity === "valid"
                || options.validity === "invalid"));
    sst.mix_in_validity(this, {
      event_target: this.container_,
      validity: options.validity,
    });

    if (options.label === undefined) {
      this.label_ = undefined;
    } else {
      SST_ASSERT((typeof (options.label) === "string"));
      this.label_ = options.label;
    }

    if (options.label_when_empty === undefined) {
      this.label_when_empty_ = undefined;
    } else {
      SST_ASSERT((typeof (options.label_when_empty) === "string"));
      this.label_when_empty_ = options.label_when_empty;
    }

    if (options.label_is_html === undefined) {
      this.label_is_html_ = false;
    } else {
      SST_ASSERT((typeof (options.label_is_html) === "boolean"));
      this.label_is_html_ = options.label_is_html;
    }

    if (this.label_ === undefined) {
      this.label_element_ = undefined;
      this.label_span_1_ = undefined;
      this.label_span_2_ = undefined;
      this.label_pencil_ = undefined;
    } else {
      this.label_element_ = document.createElement("label");
      this.label_span_1_ = document.createElement("span");
      if (this.label_is_html_) {
        this.label_span_1_.innerHTML = this.label_;
      } else {
        this.label_span_1_.innerText = this.label_;
      }
      this.label_element_.appendChild(this.label_span_1_);
      if (this.label_when_empty_ === undefined) {
        this.label_span_2_ = undefined;
      } else {
        this.label_span_2_ = document.createElement("span");
        if (this.label_is_html_) {
          this.label_span_2_.innerHTML = this.label_when_empty_;
        } else {
          this.label_span_2_.innerText = this.label_when_empty_;
        }
        this.label_element_.appendChild(this.label_span_2_);
        if (this.input_.value === "") {
          this.label_span_1_.style.setProperty("display", "none");
        } else {
          this.label_span_2_.style.setProperty("display", "none");
        }
      }
      this.label_pencil_ = document.createElement("i");
      this.label_pencil_.classList.add(
          "sst_dom_bootstrap5_bi",
          "sst_dom_bootstrap5_bi_pencil",
      );
      this.label_pencil_.style.setProperty(
          "margin-left",
          "0.5em",
      );
      this.label_element_.appendChild(this.label_pencil_);
    }

    SST_ASSERT(([
      undefined,
      "floating",
    ].includes(options.label_type)));
    if (options.label_type === undefined) {
      this.label_type_ = "floating";
    } else {
      this.label_type_ = options.label_type;
    }

    if (this.label_ === undefined) {
      this.input_group_.appendChild(this.input_);
      this.input_height_guide_ = this.input_group_.cloneNode(true);
    } else {
      switch (this.label_type_) {
        case "floating": {
          this.form_floating_ = document.createElement("div");
          this.form_floating_.classList.add("form-floating");
          this.form_floating_.appendChild(this.input_);
          this.input_height_guide_ =
              this.form_floating_.cloneNode(true);
          this.form_floating_.appendChild(this.label_element_);
          this.input_group_.appendChild(this.form_floating_);
        } break;
        default:
          SST_UNREACHABLE();
      }
      this.input_.id = sst.dom.id();
      this.label_element_.htmlFor = this.input_.id;
    }
    this.input_height_guide_.classList.add("sst_height_guide");

    this.input_group_.appendChild(this.feedback_);

    SST_ASSERT((options.disabled === undefined
                || typeof (options.disabled) === "boolean"));
    SST_ASSERT((options.committed === undefined
                || typeof (options.committed) === "boolean"));
    this.disabled_ = !!options.disabled;
    this.committed_ = !!options.committed;
    this.refresh_();

    SST_ASSERT((options.placeholder === undefined
                || typeof (options.placeholder) === "string"));
    if (options.placeholder === undefined) {
      // Omitting this seemingly noop assignment breaks Bootstrap's
      // floating labels. It seems to always need placeholder to be
      // explicitly set.
      this.input_.placeholder = "";
    } else {
      this.input_.placeholder = options.placeholder;
    }

    SST_ASSERT((options.validator === undefined
                || typeof (options.validator) === "function"));
    if (options.validator === undefined) {
      this.validator_ = value => undefined;
    } else {
      this.validator_ = options.validator;
    }

    SST_ASSERT((options.validator_is_html === undefined
                || typeof (options.validator_is_html) === "boolean"));
    this.validator_is_html_ = !!options.validator_is_html;

    const is_validating = "sst_dom_bootstrap5_is_validating";

    this.input_.addEventListener(
        "input",
        sst.debounce(
            () => {
              if (this.form_floating_ !== undefined) {
                this.form_floating_.classList.remove("is-invalid");
                this.form_floating_.classList.add(is_validating);
              }
              this.input_.classList.remove("is-invalid");
              this.input_.classList.add(is_validating);
              if (this.label_when_empty_ !== undefined) {
                if (this.input_.value === "") {
                  this.label_span_1_.style.setProperty("display",
                                                       "none");
                  this.label_span_2_.style.removeProperty("display");
                } else {
                  this.label_span_2_.style.setProperty("display",
                                                       "none");
                  this.label_span_1_.style.removeProperty("display");
                }
              }
              this.validity("validating");
            },
            async () => {
              const error = await this.validator_(this.value());
              if (error === undefined) {
                if (this.form_floating_ !== undefined) {
                  this.form_floating_.classList.remove("is-invalid");
                  this.form_floating_.classList.remove(is_validating);
                }
                this.input_.classList.remove("is-invalid");
                this.input_.classList.remove(is_validating);
                this.validity("valid");
              } else {
                if (this.validator_is_html_) {
                  this.feedback_div_.innerHTML = error;
                } else {
                  this.feedback_div_.innerText = error + ".";
                }
                if (this.form_floating_ !== undefined) {
                  this.form_floating_.classList.remove(is_validating);
                  this.form_floating_.classList.add("is-invalid");
                }
                this.input_.classList.remove(is_validating);
                this.input_.classList.add("is-invalid");
                this.validity("invalid");
              }
            }));

    if (options.validity === undefined) {
      this.input_.dispatchEvent(new Event("input", {bubbles: true}));
    }

  } //

  //--------------------------------------------------------------------

  on_input(callback) {
    SST_ASSERT((arguments.length === 1));
    SST_ASSERT((typeof (callback) === "function"));
    this.container().addEventListener("input",
                                      (event) => { callback(event); });
  }

  //--------------------------------------------------------------------
};
