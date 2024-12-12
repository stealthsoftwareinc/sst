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

import {} from "./in_browser.mjs";

globalThis.sst = globalThis.sst || {};

if (!sst.in_browser()) {

  const fs = await import("node:fs");
  const fsPromises = await import("node:fs/promises");
  const os = await import("node:os");
  const path = await import("node:path");

  globalThis.sst.tmpdir = async () => {
    if (typeof(globalThis.sst._tmpdirPath) === "undefined") {
      const d = await fsPromises.mkdtemp(path.join(os.tmpdir(), "tmp"));
      await fsPromises.chmod(d, 0o700);
      process.once("exit", () => {
        try {
          fs.rmSync(d, {force: true, recursive: true});
        } catch (e) {
        }
      });
      globalThis.sst._tmpdirPath = d;
    }
    return globalThis.sst._tmpdirPath;
  };

}
