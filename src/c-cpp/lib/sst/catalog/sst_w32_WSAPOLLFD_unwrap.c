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
#include <sst/catalog/sst_w32_WSAPOLLFD_unwrap.h>
/* Include twice to test idempotence. */
#include <sst/catalog/sst_w32_WSAPOLLFD_unwrap.h>
/**/

#include <sst/config.h>

#if SST_WITH_WINDOWS_WS2_32

#include <winsock2.h>
#include <windows.h>

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/sst_w32_WSAPOLLFD.h>
#include <sst/catalog/sst_w32_WSAPOLLFD_wrapper.h>

void sst_w32_WSAPOLLFD_unwrap(
    sst_w32_WSAPOLLFD_wrapper const * const src,
    sst_w32_WSAPOLLFD * const dst) {
  sst_w32_WSAPOLLFD const zero = {0};
  SST_ASSERT((src != NULL));
  SST_ASSERT((dst != NULL));
  *dst = zero;
  dst->fd = src->fd;
  dst->events = src->events;
  dst->revents = src->revents;
}

#endif /* #if SST_WITH_WINDOWS_WS2_32 */