/*
 * Copyright (C) 2012-2023 Stealth Software Technologies, Inc.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice (including
 * the next paragraph) shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 */

/* Include first to test independence. */
#include <sst/catalog/sst_w32_SOCKADDR_IN6_wrap.h>
/* Include twice to test idempotence. */
#include <sst/catalog/sst_w32_SOCKADDR_IN6_wrap.h>
/**/

#include <sst/config.h>

#if SST_WITH_WINDOWS_WS2_32

#include <string.h>

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/sst_w32_SOCKADDR_IN6.h>
#include <sst/catalog/sst_w32_SOCKADDR_IN6_wrapper.h>

void sst_w32_SOCKADDR_IN6_wrap(
    sst_w32_SOCKADDR_IN6 const * const src,
    sst_w32_SOCKADDR_IN6_wrapper * const dst) {
  sst_w32_SOCKADDR_IN6_wrapper const zero = {0};
  SST_ASSERT((src != NULL));
  SST_ASSERT((dst != NULL));
  *dst = zero;
  dst->sin6_family = src->sin6_family;
  dst->sin6_port = src->sin6_port;
  dst->sin6_flowinfo = src->sin6_flowinfo;
  memcpy(&dst->sin6_addr, &src->sin6_addr, sizeof(dst->sin6_addr));
  dst->sin6_scope_id = src->sin6_scope_id;
}

#endif /* #if SST_WITH_WINDOWS_WS2_32 */
