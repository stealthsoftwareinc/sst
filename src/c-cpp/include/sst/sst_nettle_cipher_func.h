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

#ifndef SST_SST_NETTLE_CIPHER_FUNC_H
#define SST_SST_NETTLE_CIPHER_FUNC_H

#include <sst/SST_WITH_SST_NETTLE_CIPHER_FUNC.h>
#include <sst/SST_WITH_NETTLE_CIPHER_FUNC.h>

#if SST_WITH_SST_NETTLE_CIPHER_FUNC

#include <nettle/nettle-types.h>

#if (SST_WITH_NETTLE_CIPHER_FUNC)
  typedef nettle_cipher_func sst_nettle_cipher_func;
#else
  typedef nettle_crypt_func sst_nettle_cipher_func;
#endif

#endif

#endif // #ifndef SST_SST_NETTLE_CIPHER_FUNC_H