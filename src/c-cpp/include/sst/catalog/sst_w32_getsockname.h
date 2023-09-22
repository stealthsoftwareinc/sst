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

#ifndef SST_CATALOG_SST_W32_GETSOCKNAME_H
#define SST_CATALOG_SST_W32_GETSOCKNAME_H

/*
 * The purpose of this header is to provide access to a Windows API
 * entity using minimal includes. In particular, this header does not
 * include any Windows API headers. The corresponding .c and/or .cpp
 * files will include the necessary Windows API headers to implement
 * and/or verify the entity.
 */

#include <sst/config.h>

#if SST_WITH_WINDOWS_WS2_32

#include <sst/catalog/SST_EXTERN_C.h>
#include <sst/catalog/sst_w32_SOCKADDR.h>
#include <sst/catalog/sst_w32_SOCKET.h>
#include <sst/private/SST_DLL_EXPORT.h>

SST_EXTERN_C SST_DLL_EXPORT int
sst_w32_getsockname(sst_w32_SOCKET s,
                    sst_w32_SOCKADDR * name,
                    int * namelen);

#endif /* #if SST_WITH_WINDOWS_WS2_32 */

#endif // SST_CATALOG_SST_W32_GETSOCKNAME_H
