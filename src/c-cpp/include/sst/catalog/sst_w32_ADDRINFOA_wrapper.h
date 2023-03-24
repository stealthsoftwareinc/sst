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

#ifndef SST_CATALOG_SST_W32_ADDRINFOA_WRAPPER_H
#define SST_CATALOG_SST_W32_ADDRINFOA_WRAPPER_H

#include <sst/config.h>

#if SST_WITH_WINDOWS_WS2_32

#include <stddef.h>

#include <sst/catalog/sst_w32_ADDRINFOA.h>
#include <sst/catalog/sst_w32_SOCKADDR.h>

typedef struct sst_w32_ADDRINFOA_wrapper {
  int ai_flags;
  int ai_family;
  int ai_socktype;
  int ai_protocol;
  size_t ai_addrlen;
  char * ai_canonname;
  sst_w32_SOCKADDR * ai_addr;
  sst_w32_ADDRINFOA * ai_next;
} sst_w32_ADDRINFOA_wrapper;

#endif /* #if SST_WITH_WINDOWS_WS2_32 */

#endif // #ifndef SST_CATALOG_SST_W32_ADDRINFOA_WRAPPER_H
