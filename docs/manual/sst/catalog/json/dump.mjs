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

import {} from "../SST_ASSERT.mjs";
import {} from "../SST_TEST_BOOL.mjs";

globalThis.sst = globalThis.sst || {};
sst.json = sst.json || {};

sst.json.dump = function(json, options) {
  SST_ASSERT((arguments.length >= 1));
  SST_ASSERT((arguments.length <= 2));
  if (arguments.length < 2) {
    options = {};
  }
  SST_ASSERT((typeof (options) === "object"));

  let uppercase_digits = true;
  if (options.uppercase_digits !== undefined) {
    SST_ASSERT((typeof (options.uppercase_digits) === "boolean"));
    uppercase_digits = options.uppercase_digits;
  }

  let indent = -1;
  if (options.indent !== undefined) {
    SST_ASSERT((typeof (options.indent) === "number"));
    SST_ASSERT((Number.isSafeInteger(indent)));
    indent = options.indent;
  }

  let indent_string = " ";
  if (options.indent_string !== undefined) {
    SST_ASSERT((typeof (options.indent_string) === "string"));
    indent_string = options.indent_string;
  }

  const textEncoder = new TextEncoder();
  const compareKeys = function(x, y) {
    const a = textEncoder.encode(String(x));
    const b = textEncoder.encode(String(y));
    let i = 0;
    while (i < a.length && i < b.length) {
      if (a[i] < b[i]) {
        return -1;
      }
      if (a[i] > b[i]) {
        return 1;
      }
      ++i;
    }
    if (i < b.length) {
      return -1;
    }
    if (i < a.length) {
      return 1;
    }
    return 0;
  };
  let indent_inc = "";
  for (let i = 0; i < indent; ++i) {
    indent_inc += indent_string;
  }
  let indent_buf = "";
  const stringify = function(x) {
    if (Array.isArray(x)) {
      let s = "";
      s += "[";
      indent_buf += indent_inc;
      for (let i = 0; i < x.length; ++i) {
        if (indent >= 0) {
          s += "\n";
          s += indent_buf;
        }
        s += stringify(x[i]);
        if (i < x.length - 1) {
          s += ",";
        }
      }
      indent_buf = indent_buf.slice(0, -indent_inc.length);
      if (x.length > 0 && indent >= 0) {
        s += "\n";
        s += indent_buf;
      }
      s += "]";
      return s;
    } else if (typeof (x) === "object") {
      let s = "";
      s += "{";
      indent_buf += indent_inc;
      const keys = Object.keys(x).sort(compareKeys);
      for (let i = 0; i < keys.length; ++i) {
        if (indent >= 0) {
          s += "\n";
          s += indent_buf;
        }
        s += stringify(keys[i]);
        s += ":";
        if (indent >= 0) {
          s += " ";
        }
        s += stringify(x[keys[i]]);
        if (i < keys.length - 1) {
          s += ",";
        }
      }
      indent_buf = indent_buf.slice(0, -indent_inc.length);
      if (keys.length > 0 && indent >= 0) {
        s += "\n";
        s += indent_buf;
      }
      s += "}";
      return s;
    } else if (typeof (x) === "string") {
      let s = "";
      s += "\"";
      for (let i = 0; i < x.length; ++i) {
        const c = x.charCodeAt(i);
        if (c === 0x0008) {
          s += "\\b";
        } else if (c === 0x0009) {
          s += "\\t";
        } else if (c === 0x000A) {
          s += "\\n";
        } else if (c === 0x000C) {
          s += "\\f";
        } else if (c === 0x000D) {
          s += "\\r";
        } else if (c === 0x0022) {
          s += "\\\"";
        } else if (c === 0x002F) {
          s += "\\/";
        } else if (c === 0x005C) {
          s += "\\\\";
        } else if (c >= 0x0020 && c <= 0x007E) {
          s += x[i];
        } else {
          let t = c.toString(16);
          if (uppercase_digits) {
            t = t.toUpperCase();
          }
          t = `0000${t}`.slice(-4);
          t = `\\u${t}`;
          s += t;
        }
      }
      s += "\"";
      return s;
    } else {
      return JSON.stringify(x);
    }
  };
  return stringify(json);
};

//----------------------------------------------------------------------
// Tests
//----------------------------------------------------------------------

if (!globalThis.NDEBUG) {

  SST_TEST_BOOL(
      {},
      `sst.json.dump('\\b') === '"\\\\b"'`,
      `sst.json.dump('\\b')`,
  );

  SST_TEST_BOOL(
      {},
      `sst.json.dump('\\t') === '"\\\\t"'`,
      `sst.json.dump('\\t')`,
  );

  SST_TEST_BOOL(
      {},
      `sst.json.dump('\\n') === '"\\\\n"'`,
      `sst.json.dump('\\n')`,
  );

  SST_TEST_BOOL(
      {},
      `sst.json.dump('\\u000B') === '"\\\\u000B"'`,
      `sst.json.dump('\\u000B')`,
  );

  SST_TEST_BOOL(
      {},
      `sst.json.dump('\\f') === '"\\\\f"'`,
      `sst.json.dump('\\f')`,
  );

  SST_TEST_BOOL(
      {},
      `sst.json.dump('\\r') === '"\\\\r"'`,
      `sst.json.dump('\\r')`,
  );

  SST_TEST_BOOL(
      {},
      `sst.json.dump('\\u000E') === '"\\\\u000E"'`,
      `sst.json.dump('\\u000E')`,
  );

  SST_TEST_BOOL(
      {},
      `sst.json.dump('\\u000F') === '"\\\\u000F"'`,
      `sst.json.dump('\\u000F')`,
  );
}
