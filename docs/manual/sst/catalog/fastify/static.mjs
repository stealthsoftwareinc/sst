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
// The sst.fastify.static function adds routing to an existing Fastify
// server that serves a directory or a single file at a given url.
//
// For example, here's how to serve the /foo/bar/ directory as / on the
// server:
//
//       sst.fastify.static(server, "/foo/bar/", "/");
//
// And here's how to additionally serve the single /baz.html file as
// /baz.html on the server (overriding /foo/bar/baz.html if it exists):
//
//       sst.fastify.static(server, "/baz.html", "/baz.html");
//
// Directory mode vs. single file mode is controlled by the presence of
// the trailing slash in the src parameter.
//
// For maximum performance, all served files are cached in memory. Each
// cache entry is checked every time that file is served, and the file
// is only read in again if the last modified time has increased.
//
// For .html files, the literal string "{{root}}" in the file will be
// replaced with a relative path leading upward to the root directory of
// the server, regardless of where the file was loaded from on disk. For
// example:
//
//       /foo.html              will have {{root}} = .
//       /foo/bar.html          will have {{root}} = ..
//       /foo/bar/baz.html      will have {{root}} = ../..
//       /foo/bar/baz/qux.html  will have {{root}} = ../../..
//
// Directories will serve index.html. Omitting the trailing slash on a
// directory will 302 redirect to have the trailing slash. Explicitly
// requesting index.html will 302 redirect to the directory.
//
// You can safely override children of directory mode routes with single
// file mode routes, as these are implemented with wildcard and static
// routes, respectively, and Fastify gives the latter precedence over
// the former.
//

// TODO: Allow better caching? We're doing one cache per call, but it
//       should be possible to use the same cache over multiple calls.

import {} from "../is_subset.mjs";
import {} from "../SST_ASSERT.mjs";

globalThis.sst = globalThis.sst || {};
sst.fastify = sst.fastify || {};

const content_types = {
  ".css": "text/css; charset=utf-8",
  ".gif": "image/gif",
  ".html": "text/html; charset=utf-8",
  ".jpeg": "image/jpeg",
  ".jpg": "image/jpeg",
  ".js": "text/javascript; charset=utf-8",
  ".mjs": "text/javascript; charset=utf-8",
  ".otf": "font/otf",
  ".png": "image/png",
  ".svg": "image/svg+xml",
  ".ttf": "font/ttf",
  ".woff": "font/woff",
  ".woff2": "font/woff2",
};

sst.fastify.static = function(server, src, dst, options = {}) {
  SST_ASSERT((arguments.length >= 3));
  SST_ASSERT((arguments.length <= 4));
  SST_ASSERT((typeof (options) === "object"));
  SST_ASSERT((sst.is_subset(Object.keys(options), [])));

  options = Object.assign({}, options);

  SST_ASSERT((typeof (src) === "string"));
  SST_ASSERT((src !== ""));

  SST_ASSERT((typeof (dst) === "string"));
  SST_ASSERT((dst.startsWith("/")));
  SST_ASSERT((!dst.includes("//")));
  SST_ASSERT((!dst.includes("/./")));
  SST_ASSERT((!dst.endsWith("/.")));
  SST_ASSERT((!dst.includes("/../")));
  SST_ASSERT((!dst.endsWith("/..")));

  if (src.endsWith("/")) {
    if (!dst.endsWith("/")) {
      dst += "/";
    }
  } else {
    if (dst.endsWith("/index.html")) {
      dst = dst.slice(0, -"index.html".length);
    }
  }

  const cache = {};

  server.route({
    method: ["GET", "HEAD"],
    url: dst.endsWith("/") ? dst + "*" : dst,
    handler: async (request, reply) => {
      let query_pos = request.url.indexOf("?");
      if (query_pos === -1) {
        query_pos = request.url.length;
      }
      const path = request.url.slice(0, query_pos);
      const query = request.url.slice(query_pos);
      if (path.includes("/./") || path.endsWith("/.")
          || path.includes("/../") || path.endsWith("/..")) {
        reply.code(400);
        reply.header("content-type", "text/plain; charset=utf-8");
        return "sst.fastify.static 400";
      }
      if (path.includes("//")) {
        reply.redirect(path.replace(/\/{2,}/g, "/") + query);
        return;
      }
      if (path.endsWith("/index.html")) {
        reply.redirect(path.slice(0, -"index.html".length) + query);
        return;
      }
      let tail;
      let file;
      if (src.endsWith("/")) {
        tail = path.slice(dst.length);
        if (tail === "" || tail.endsWith("/")) {
          tail += "index.html";
        }
        file = src + tail;
      } else {
        file = src;
      }
      const fsp = await import("node:fs/promises");
      const stat = await fsp.stat(file).catch(e => e);
      if (stat instanceof Error) {
        if (stat.code === "ENOENT") {
          reply.code(404);
          reply.header("content-type", "text/plain; charset=utf-8");
          return "sst.fastify.static 404";
        }
        throw stat;
      }
      if (stat.isDirectory()) {
        if (src.endsWith("/")) {
          reply.redirect(dst + tail + "/" + query);
          return;
        }
        reply.code(404);
        reply.header("content-type", "text/plain; charset=utf-8");
        return "sst.fastify.static 404";
      }
      let extension = file.match(/\.[^.\/]+$/);
      if (extension) {
        extension = extension[0];
      }
      let depth;
      let key;
      if (extension === ".html") {
        depth = path.slice(1).replace(/[^\/]/g, "");
        key = file + depth;
      } else {
        key = file;
      }
      let entry = cache[key];
      if (entry === undefined || entry.stat.mtimeMs < stat.mtimeMs) {
        let body;
        if (extension === ".html") {
          body = await fsp.readFile(file, {encoding: "utf8"});
          const root = depth.length === 0 ?
                           "." :
                           ".." +
                               "/..".repeat(depth.length - 1);
          body = body.replace(/\{\{root\}\}/g, root);
          body = Buffer.from(body);
        } else {
          body = await fsp.readFile(file);
        }
        const content_type =
            extension ? content_types[extension] : undefined;
        const last_modified = new Date().toGMTString();
        entry = {
          stat,
          body,
          content_type,
          last_modified,
        };
        cache[key] = entry;
      }
      if (entry.content_type !== undefined) {
        reply.header("content-type", entry.content_type);
      }
      reply.header("content-length", entry.body.length);
      reply.header("last-modified", entry.last_modified);
      if (request.method === "GET") {
        return entry.body;
      }
    }
  });

  if (dst.endsWith("/") && dst !== "/") {
    const url = dst.slice(0, -1);
    server.route({
      method: ["GET", "HEAD"],
      url: url,
      handler: (request, reply) => {
        reply.redirect(dst + request.url.slice(url.length));
      }
    });
  }

  // TODO: Return something to allow cache clearing?
};
