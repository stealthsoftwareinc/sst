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
import {} from "./SST_ASSERT.mjs";

globalThis.sst = globalThis.sst || {};

sst.debounce = function(...args) {
  let init = undefined;
  let proc = undefined;
  let delay = 1000;
  if (args.length === 1) {
    proc = args[0];
  } else if (args.length === 2) {
    if (typeof (args[1]) === "function") {
      init = args[0];
      proc = args[1];
    } else {
      proc = args[0];
      delay = args[1];
    }
  } else {
    SST_ASSERT((args.length === 3));
    init = args[0];
    proc = args[1];
    delay = args[2];
  }
  SST_ASSERT((init === undefined || typeof (init) === "function"));
  SST_ASSERT((typeof (proc) === "function"));
  SST_ASSERT((typeof (delay) === "number"));
  SST_ASSERT((delay >= 0));
  const cancelers = [];
  let mutex = false;
  return async (...args) => {
    try {
      for (const canceler of cancelers) {
        canceler.cancel = true;
      }
      cancelers.length = 0;
      const canceler = {cancel: false};
      cancelers.push(canceler);
      while (mutex) {
        await new Promise(r => setTimeout(r, 200));
      }
      mutex = true;
      try {
        if (init !== undefined) {
          const r = init(undefined, ...args);
          if (r instanceof Promise) {
            await r;
          }
        }
      } catch (e) {
        try {
          if (sst.in_browser()) {
            console.error(e);
          }
        } catch (e) {
        }
      } finally {
        mutex = false;
      }
      setTimeout(async () => {
        try {
          for (;;) {
            if (canceler.cancel) {
              return;
            }
            if (!mutex) {
              break;
            }
            await new Promise(r => setTimeout(r, 200));
          }
          mutex = true;
          try {
            const r = proc(canceler, ...args);
            if (r instanceof Promise) {
              await r;
            }
          } catch (e) {
            try {
              if (sst.in_browser()) {
                console.error(e);
              }
            } catch (e) {
            }
          } finally {
            mutex = false;
          }
        } catch (e) {
          try {
            if (sst.in_browser()) {
              console.error(e);
            }
          } catch (e) {
          }
        }
      }, delay);
    } catch (e) {
      try {
        if (sst.in_browser()) {
          console.error(e);
        }
      } catch (e) {
      }
    }
  };
}
