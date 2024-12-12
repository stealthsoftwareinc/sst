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
import {} from "../test_e.mjs";

import {} from "./dump.mjs";

globalThis.sst = globalThis.sst || {};
sst.json = sst.json || {};

sst.json.get_as_file = async function(json, file, options = {}) {
  SST_ASSERT((arguments.length >= 2));
  SST_ASSERT((arguments.length <= 3));
  SST_ASSERT((typeof (options) === "object"));
  SST_ASSERT((sst.is_subset(Object.keys(options), [
    "async",
    "atomic",
  ])));
  if (options.async !== undefined) {
    SST_ASSERT((typeof (options.async) === "boolean"));
  }
  if (options.atomic !== undefined) {
    SST_ASSERT((typeof (options.atomic) === "boolean"));
  }

  if (!options.async) {
    throw new Error(
        "sst.json.get_as_file(): async=false is not supported yet");
  }

  const dump = sst.json.dump(json);

  if (typeof (file) === "string") {
    const fsp = await import("node:fs/promises");
    if (options.atomic) {
      const crypto = await import("node:crypto");
      while (true) {
        const tmp = file + "." + crypto.randomUUID().slice(-12);
        if (await sst.test_e(tmp, false)) {
          continue;
        }
        try {
          await fsp.writeFile(tmp, dump);
          await fsp.rename(tmp, file);
        } catch (e) {
          await fsp.unlink(tmp).catch(e => undefined);
          throw e;
        }
        break;
      }
    } else {
      await fsp.writeFile(file, dump);
    }
  } else {
    SST_ASSERT((false));
  }
};
