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

#ifndef SST_CATALOG_SST_NARGS_H
#define SST_CATALOG_SST_NARGS_H

#include <sst/catalog/SST_HAVE_VA_OPT.h>

/* clang-format off */

#define SST_NARGS_HELPER(                                     \
  X200, X199, X198, X197, X196, X195, X194, X193, X192, X191, \
  X190, X189, X188, X187, X186, X185, X184, X183, X182, X181, \
  X180, X179, X178, X177, X176, X175, X174, X173, X172, X171, \
  X170, X169, X168, X167, X166, X165, X164, X163, X162, X161, \
  X160, X159, X158, X157, X156, X155, X154, X153, X152, X151, \
  X150, X149, X148, X147, X146, X145, X144, X143, X142, X141, \
  X140, X139, X138, X137, X136, X135, X134, X133, X132, X131, \
  X130, X129, X128, X127, X126, X125, X124, X123, X122, X121, \
  X120, X119, X118, X117, X116, X115, X114, X113, X112, X111, \
  X110, X109, X108, X107, X106, X105, X104, X103, X102, X101, \
  X100, X99, X98, X97, X96, X95, X94, X93, X92, X91,          \
  X90, X89, X88, X87, X86, X85, X84, X83, X82, X81,           \
  X80, X79, X78, X77, X76, X75, X74, X73, X72, X71,           \
  X70, X69, X68, X67, X66, X65, X64, X63, X62, X61,           \
  X60, X59, X58, X57, X56, X55, X54, X53, X52, X51,           \
  X50, X49, X48, X47, X46, X45, X44, X43, X42, X41,           \
  X40, X39, X38, X37, X36, X35, X34, X33, X32, X31,           \
  X30, X29, X28, X27, X26, X25, X24, X23, X22, X21,           \
  X20, X19, X18, X17, X16, X15, X14, X13, X12, X11,           \
  X10, X9, X8, X7, X6, X5, X4, X3, X2, X1,                    \
  N, ...                                                      \
) N

#if SST_HAVE_VA_OPT

#define SST_NARGS(...)                                \
  SST_NARGS_HELPER(__VA_ARGS__ __VA_OPT__(,)          \
    200, 199, 198, 197, 196, 195, 194, 193, 192, 191, \
    190, 189, 188, 187, 186, 185, 184, 183, 182, 181, \
    180, 179, 178, 177, 176, 175, 174, 173, 172, 171, \
    170, 169, 168, 167, 166, 165, 164, 163, 162, 161, \
    160, 159, 158, 157, 156, 155, 154, 153, 152, 151, \
    150, 149, 148, 147, 146, 145, 144, 143, 142, 141, \
    140, 139, 138, 137, 136, 135, 134, 133, 132, 131, \
    130, 129, 128, 127, 126, 125, 124, 123, 122, 121, \
    120, 119, 118, 117, 116, 115, 114, 113, 112, 111, \
    110, 109, 108, 107, 106, 105, 104, 103, 102, 101, \
    100, 99, 98, 97, 96, 95, 94, 93, 92, 91,          \
    90, 89, 88, 87, 86, 85, 84, 83, 82, 81,           \
    80, 79, 78, 77, 76, 75, 74, 73, 72, 71,           \
    70, 69, 68, 67, 66, 65, 64, 63, 62, 61,           \
    60, 59, 58, 57, 56, 55, 54, 53, 52, 51,           \
    50, 49, 48, 47, 46, 45, 44, 43, 42, 41,           \
    40, 39, 38, 37, 36, 35, 34, 33, 32, 31,           \
    30, 29, 28, 27, 26, 25, 24, 23, 22, 21,           \
    20, 19, 18, 17, 16, 15, 14, 13, 12, 11,           \
    10, 9, 8, 7, 6, 5, 4, 3, 2, 1,                    \
    0                                                 \
  )

#else

#define SST_NARGS(...)                                \
  SST_NARGS_HELPER(__VA_ARGS__,                       \
    200, 199, 198, 197, 196, 195, 194, 193, 192, 191, \
    190, 189, 188, 187, 186, 185, 184, 183, 182, 181, \
    180, 179, 178, 177, 176, 175, 174, 173, 172, 171, \
    170, 169, 168, 167, 166, 165, 164, 163, 162, 161, \
    160, 159, 158, 157, 156, 155, 154, 153, 152, 151, \
    150, 149, 148, 147, 146, 145, 144, 143, 142, 141, \
    140, 139, 138, 137, 136, 135, 134, 133, 132, 131, \
    130, 129, 128, 127, 126, 125, 124, 123, 122, 121, \
    120, 119, 118, 117, 116, 115, 114, 113, 112, 111, \
    110, 109, 108, 107, 106, 105, 104, 103, 102, 101, \
    100, 99, 98, 97, 96, 95, 94, 93, 92, 91,          \
    90, 89, 88, 87, 86, 85, 84, 83, 82, 81,           \
    80, 79, 78, 77, 76, 75, 74, 73, 72, 71,           \
    70, 69, 68, 67, 66, 65, 64, 63, 62, 61,           \
    60, 59, 58, 57, 56, 55, 54, 53, 52, 51,           \
    50, 49, 48, 47, 46, 45, 44, 43, 42, 41,           \
    40, 39, 38, 37, 36, 35, 34, 33, 32, 31,           \
    30, 29, 28, 27, 26, 25, 24, 23, 22, 21,           \
    20, 19, 18, 17, 16, 15, 14, 13, 12, 11,           \
    10, 9, 8, 7, 6, 5, 4, 3, 2, 1,                    \
    0                                                 \
  )

#endif

/* clang-format on */

/*----------------------------------------------------------------------
// Compile-time tests
//--------------------------------------------------------------------*/

#include <sst/catalog/SST_COMPILE_TIME_TESTS.h>

#if SST_COMPILE_TIME_TESTS

#if SST_HAVE_VA_OPT
#if SST_NARGS() != 0
#error
#endif
#endif

#if SST_NARGS(1) != 1
#error
#endif

#if SST_NARGS(1, 2) != 2
#error
#endif

#if SST_NARGS(1, 2, 3) != 3
#error
#endif

#endif // #if SST_COMPILE_TIME_TESTS

/*--------------------------------------------------------------------*/

#endif // #ifndef SST_CATALOG_SST_NARGS_H
