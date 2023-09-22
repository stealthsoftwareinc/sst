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

#ifndef SST_TIME_H
#define SST_TIME_H

#include <sst/config.h>

/*----------------------------------------------------------------------
// C and C++
//--------------------------------------------------------------------*/

/*----------------------------------------------------------------------
// C only
//--------------------------------------------------------------------*/
#ifndef __cplusplus

/*----------------------------------------------------------------------
// C++ only
//--------------------------------------------------------------------*/
#elif SST_WITH_BUILD_GROUP_CPP_AUTOTOOLS

#include <sst/catalog/asctime.hpp>
#include <sst/catalog/ctime.hpp>
#include <sst/catalog/gmtime.hpp>
#include <sst/catalog/localtime.hpp>
#include <sst/catalog/mono_time.hpp>
#include <sst/catalog/mono_time_d.hpp>
#include <sst/catalog/mono_time_ms.hpp>
#include <sst/catalog/mono_time_ms_t.hpp>
#include <sst/catalog/mono_time_ns.hpp>
#include <sst/catalog/mono_time_ns_t.hpp>
#include <sst/catalog/mono_time_s.hpp>
#include <sst/catalog/mono_time_s_t.hpp>
#include <sst/catalog/mono_time_us.hpp>
#include <sst/catalog/mono_time_us_t.hpp>
#include <sst/catalog/mono_time_zero.hpp>
#include <sst/catalog/time.hpp>
#include <sst/catalog/unix_time.hpp>
#include <sst/catalog/unix_time_d.hpp>
#include <sst/catalog/unix_time_ms.hpp>
#include <sst/catalog/unix_time_ms_t.hpp>
#include <sst/catalog/unix_time_ns.hpp>
#include <sst/catalog/unix_time_ns_t.hpp>
#include <sst/catalog/unix_time_s.hpp>
#include <sst/catalog/unix_time_s_t.hpp>

/*--------------------------------------------------------------------*/
#endif

#endif // SST_TIME_H
