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
#include <sst/catalog/sst_w32_SHORT.h>
/* Include twice to test idempotence. */
#include <sst/catalog/sst_w32_SHORT.h>
/**/

#include <sst/config.h>

#if SST_WITH_WINDOWS_KERNEL32

#include <windows.h>

#include <sst/catalog/SST_STATIC_ASSERT.h>
#include <sst/catalog/sst_w32_SHORT.h>

/* Verify that the types have the same size. */
SST_STATIC_ASSERT((sizeof(sst_w32_SHORT) == sizeof(SHORT)));

/* Verify that the types have the same signedness. */
SST_STATIC_ASSERT((((sst_w32_SHORT)-1 < (sst_w32_SHORT)0)
                   == ((SHORT)-1 < (SHORT)0)));

/* If the types are unsigned, verify that they have the same maximum
 * value. If the types are signed, this assertion is trivially true,
 * even if the types are different. */
SST_STATIC_ASSERT(((sst_w32_SHORT)-1 == (SHORT)-1));

#endif /* #if SST_WITH_WINDOWS_KERNEL32 */
