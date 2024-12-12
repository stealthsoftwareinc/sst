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

sst.barf = function(message) {
  try {

    // TODO: Color like sst_barf in the Bash library when we're not in a
    //       browser.
    console.error(message);

    if (sst.in_browser()) {
      // TODO: Display a modal instead of nuking <body>? Might as well
      //       let it limp along in case the user can salvage something.
      //       We can display a general warning that the page is kinda
      //       broken now.
      while (document.body.firstChild) {
        document.body.removeChild(document.body.lastChild);
      }
      // TODO: Make the default display style nicer.
      // TODO: If Bootstrap is being used, style for that.
      // TODO: Make sst.logic_exception have a custom display? Or will
      //       it already be doing that by itself via its .toString()?
      document.body.innerText = String(message);

      // TODO: Need idempotency of some sort. Another execution context
      //       may call sst.barf again. I guess we can collect a limited
      //       number of errors to display in that case?

      // Throw an sst.barf_exception to try to stop the current
      // execution context. This is why sst.barf_exception exists.
      throw new sst.barf_exception();

    } else {
      if (process.exitCode === undefined) {
        process.exitCode = 1;
      }
      process.exit();
    }
  } catch (e) {
    try {
      console.error(e);
    } catch (e) {
    }
    try {
      process.exit(1);
    } catch (e) {
    }
  }
}
