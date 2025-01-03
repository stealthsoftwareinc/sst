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

globalThis.sst = globalThis.sst || {};

sst.fetch_slurp = function(url, init) {
  return (function f(url, init, transform, results) {
    return fetch(url, init).then(response => {
      if (!response.ok) {
        return new Promise((resolve, reject) => { reject(response); });
      }
      results = new Promise(resolve => {
        resolve(results.then(results => {
          return transform(response).then(result => {
            results.push(result);
            return results;
          });
        }));
      });
      let next = response.headers.get("Link");
      if (next !== null) {
        next = next.match(
            /.*<[\t ]*([^\t >]+)[\t ]*>[\t ]*;[\t ]*rel[\t ]*=[\t ]*"[\t ]*next[\t ]*".*/i);
        if (next !== null) {
          return f(next[1], init, transform, results);
        }
      }
      return results;
    });
  })(url,
     init,
     typeof init === "object" && "transform" in init
             && typeof init.transform === "function" ?
         init.transform :
         response => response.text(),
     new Promise(resolve => { resolve([]); }));
};
