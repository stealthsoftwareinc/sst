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

#ifndef SST_CATALOG_SST_W32_SOCKADDR_IN6_WRAPPER_H
#define SST_CATALOG_SST_W32_SOCKADDR_IN6_WRAPPER_H

#include <sst/config.h>

#if SST_WITH_WINDOWS_WS2_32

#include <sst/catalog/sst_w32_ADDRESS_FAMILY.h>
#include <sst/catalog/sst_w32_ULONG.h>
#include <sst/catalog/sst_w32_USHORT.h>

typedef struct sst_w32_SOCKADDR_IN6_wrapper {
  sst_w32_ADDRESS_FAMILY sin6_family;
  sst_w32_USHORT sin6_port;
  sst_w32_ULONG sin6_flowinfo;
  unsigned char sin6_addr[16];
  sst_w32_ULONG sin6_scope_id;
} sst_w32_SOCKADDR_IN6_wrapper;

#endif /* #if SST_WITH_WINDOWS_WS2_32 */

#endif // #ifndef SST_CATALOG_SST_W32_SOCKADDR_IN6_WRAPPER_H
