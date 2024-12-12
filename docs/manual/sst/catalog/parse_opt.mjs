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

//
// parse_opt(argv, opts, [style], [hasArg])
//

await import("./SST_TEST_BOOL.mjs");

globalThis.sst = globalThis.sst || {};

sst.parse_opt = function(...fArgs) {

  if (fArgs.length < 2) {
    throw new TypeError();
  }

  let fArgsPos = 0;

  const argv = fArgs[fArgsPos++];
  if (!Array.isArray(argv)) {
    throw new TypeError();
  }
  for (const x of argv) {
    if (typeof(x) != "string") {
      throw new TypeError();
    }
  }

  let opts = fArgs[fArgsPos++];
  if (Array.isArray(opts)) {
    for (const opt of opts) {
      if (typeof(opt) != "string") {
        throw new TypeError();
      }
      if (!opt.startsWith("-")) {
        throw new TypeError();
      }
      if (!opt.startsWith("--") && opt.length != 2) {
        throw new TypeError();
      }
    }
  } else if (typeof(opts) == "string") {
    opts = [opts];
  } else {
    throw new TypeError();
  }

  const style = fArgsPos < fArgs.length ? fArgs[fArgsPos++] : "required";
  if (style != "required" && style != "permitted" && style != "forbidden") {
    throw new TypeError();
  }

  const hasArg = fArgsPos < fArgs.length ? fArgs[fArgsPos++] : [0];
  if (!Array.isArray(hasArg)) {
    throw new TypeError();
  }
  if (hasArg.length == 0) {
    hasArg.push(0);
  }

  if (fArgsPos != fArgs.length) {
    throw new TypeError();
  }

  if (argv.length == 0) {
    return false;
  }

  for (const opt of opts) {

    if (!argv[0].startsWith(opt)) {
      continue;
    }

    if (argv[0].length == opt.length) {
      if (style == "required") {
        if (argv.length < 2) {
          throw new Error(
            "Option " + JSON.stringify(opt) + " requires an argument."
          );
        }
        argv.shift();
        hasArg[0] = true;
      } else {
        argv[0] = "";
        hasArg[0] = false;
      }
      return true;
    }

    if (opt.startsWith("--")) {
      if (argv[0][opt.length] != "=") {
        return false;
      }
      if (style == "forbidden") {
        throw new Error(
          "Option " + JSON.stringify(opt) + " forbids an argument."
        );
      }
      argv[0] = argv[0].slice(opt.length + 1);
      hasArg[0] = true;
      return true;
    }

    if (style == "forbidden") {
      argv[0] = "-" + argv[0].slice(2);
      argv.unshift("");
      hasArg[0] = false;
    } else {
      argv[0] = argv[0].slice(2);
      hasArg[0] = true;
    }
    return true;

  }

  return false;

};

//----------------------------------------------------------------------
// Tests
//----------------------------------------------------------------------

if (!globalThis.NDEBUG) {

  SST_TEST_BOOL(
    {
      argv: undefined,
      r: undefined,
    },
    [
      `this.argv = [],`,
      `this.r = sst.parse_opt(this.argv, "-x"),`,
      `this.r === false`,
      `&& JSON.stringify(this.argv) === "[]"`,
    ].join(" "),
    `this.r`,
    `JSON.stringify(this.argv)`,
  );

}
