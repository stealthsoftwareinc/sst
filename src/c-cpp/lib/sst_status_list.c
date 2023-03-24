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

#include <src/sst_status_list.h>
#include <src/sst_status_list.h>

/* begin_includes */

#include <src/sst_status_item.h>
#include <src/sst_status_item_ut.h>
#include <sst/SST_ALLOCATION_FAILED.h>
#include <sst/SST_ALLOCATION_IMPOSSIBLE.h>
#include <sst/SST_ALWAYS_FAILS.h>
#include <sst/SST_EC_ALLOCATION_FAILED_STATUS.h>
#include <sst/SST_EC_ALLOCATION_IMPOSSIBLE_STATUS.h>
#include <sst/SST_EC_ALWAYS_FAILS_STATUS.h>
#include <sst/SST_EC_FAILURE_STATUS.h>
#include <sst/SST_EC_INTEGER_OVERFLOW_STATUS.h>
#include <sst/SST_EC_INTERNAL_ERROR_STATUS.h>
#include <sst/SST_EC_INVALID_ALIASING_STATUS.h>
#include <sst/SST_EC_INVALID_ARGUMENT_STATUS.h>
#include <sst/SST_EC_INVALID_ARRAY_INDEX_STATUS.h>
#include <sst/SST_EC_INVALID_ARRAY_SIZE_STATUS.h>
#include <sst/SST_EC_INVALID_LIST_INDEX_STATUS.h>
#include <sst/SST_EC_INVALID_LIST_SIZE_STATUS.h>
#include <sst/SST_EC_INVALID_OPERAND_STATUS.h>
#include <sst/SST_EC_INVALID_OPERATION_STATUS.h>
#include <sst/SST_EC_INVALID_OPTION_NAME_STATUS.h>
#include <sst/SST_EC_INVALID_OPTION_STATUS.h>
#include <sst/SST_EC_INVALID_OPTION_VALUE_STATUS.h>
#include <sst/SST_EC_INVALID_POINTER_STATUS.h>
#include <sst/SST_EC_LIMIT_EXCEEDED_STATUS.h>
#include <sst/SST_EC_LONGPTR_NOT_SUPPORTED_STATUS.h>
#include <sst/SST_EC_MISSING_ARRAY_SENTINEL_STATUS.h>
#include <sst/SST_EC_MISSING_CASE_STATUS.h>
#include <sst/SST_EC_MISSING_LIST_SENTINEL_STATUS.h>
#include <sst/SST_EC_MISSING_OPTION_VALUE_STATUS.h>
#include <sst/SST_EC_NEGATIVE_ARRAY_INDEX_STATUS.h>
#include <sst/SST_EC_NEGATIVE_ARRAY_SIZE_STATUS.h>
#include <sst/SST_EC_NEGATIVE_LIST_INDEX_STATUS.h>
#include <sst/SST_EC_NEGATIVE_LIST_SIZE_STATUS.h>
#include <sst/SST_EC_NONNULL_POINTER_STATUS.h>
#include <sst/SST_EC_NOT_IMPLEMENTED_STATUS.h>
#include <sst/SST_EC_NOT_SUPPORTED_STATUS.h>
#include <sst/SST_EC_NULL_POINTER_STATUS.h>
#include <sst/SST_EC_OUT_OF_MEMORY_STATUS.h>
#include <sst/SST_EC_OUT_OF_RANGE_STATUS.h>
#include <sst/SST_EC_OVERSIZE_ARRAY_INDEX_STATUS.h>
#include <sst/SST_EC_OVERSIZE_LIST_INDEX_STATUS.h>
#include <sst/SST_EC_PARSE_FAILURE_STATUS.h>
#include <sst/SST_EC_WILD_POINTER_STATUS.h>
#include <sst/SST_EC_ZERO_ARRAY_INDEX_STATUS.h>
#include <sst/SST_EC_ZERO_ARRAY_SIZE_STATUS.h>
#include <sst/SST_EC_ZERO_LIST_INDEX_STATUS.h>
#include <sst/SST_EC_ZERO_LIST_SIZE_STATUS.h>
#include <sst/SST_FAILURE.h>
#include <sst/SST_INTEGER_OVERFLOW.h>
#include <sst/SST_INTERNAL_ERROR.h>
#include <sst/SST_INVALID_ALIASING.h>
#include <sst/SST_INVALID_ARGUMENT.h>
#include <sst/SST_INVALID_ARRAY_INDEX.h>
#include <sst/SST_INVALID_ARRAY_SIZE.h>
#include <sst/SST_INVALID_LIST_INDEX.h>
#include <sst/SST_INVALID_LIST_SIZE.h>
#include <sst/SST_INVALID_OPERAND.h>
#include <sst/SST_INVALID_OPERATION.h>
#include <sst/SST_INVALID_OPTION.h>
#include <sst/SST_INVALID_OPTION_NAME.h>
#include <sst/SST_INVALID_OPTION_VALUE.h>
#include <sst/SST_INVALID_POINTER.h>
#include <sst/SST_LIMIT_EXCEEDED.h>
#include <sst/SST_LONGPTR_NOT_SUPPORTED.h>
#include <sst/SST_MISSING_ARRAY_SENTINEL.h>
#include <sst/SST_MISSING_CASE.h>
#include <sst/SST_MISSING_LIST_SENTINEL.h>
#include <sst/SST_MISSING_OPTION_VALUE.h>
#include <sst/SST_NEGATIVE_ARRAY_INDEX.h>
#include <sst/SST_NEGATIVE_ARRAY_SIZE.h>
#include <sst/SST_NEGATIVE_LIST_INDEX.h>
#include <sst/SST_NEGATIVE_LIST_SIZE.h>
#include <sst/SST_NONNULL_POINTER.h>
#include <sst/SST_NOT_IMPLEMENTED.h>
#include <sst/SST_NOT_SUPPORTED.h>
#include <sst/SST_NULL_POINTER.h>
#include <sst/SST_OUT_OF_MEMORY.h>
#include <sst/SST_OUT_OF_RANGE.h>
#include <sst/SST_OVERSIZE_ARRAY_INDEX.h>
#include <sst/SST_OVERSIZE_LIST_INDEX.h>
#include <sst/SST_PARSE_FAILURE.h>
#include <sst/SST_STATUS_MAXVAL.h>
#include <sst/SST_SUCCESS.h>
#include <sst/SST_UNKNOWN.h>
#include <sst/SST_WILD_POINTER.h>
#include <sst/SST_ZERO_ARRAY_INDEX.h>
#include <sst/SST_ZERO_ARRAY_SIZE.h>
#include <sst/SST_ZERO_LIST_INDEX.h>
#include <sst/SST_ZERO_LIST_SIZE.h>
#include <sst/sst_status.h>

/* end_includes */

sst_status_item const sst_status_list[SST_STATUS_MAXVAL + 1] = {
  {
    /* name = */ "SST_ALLOCATION_FAILED",
    /* value = */ SST_ALLOCATION_FAILED,
    /* ec = */ SST_EC_ALLOCATION_FAILED_STATUS,
  },
  {
    /* name = */ "SST_ALLOCATION_IMPOSSIBLE",
    /* value = */ SST_ALLOCATION_IMPOSSIBLE,
    /* ec = */ SST_EC_ALLOCATION_IMPOSSIBLE_STATUS,
  },
  {
    /* name = */ "SST_ALWAYS_FAILS",
    /* value = */ SST_ALWAYS_FAILS,
    /* ec = */ SST_EC_ALWAYS_FAILS_STATUS,
  },
  {
    /* name = */ "SST_FAILURE",
    /* value = */ SST_FAILURE,
    /* ec = */ SST_EC_FAILURE_STATUS,
  },
  {
    /* name = */ "SST_INTEGER_OVERFLOW",
    /* value = */ SST_INTEGER_OVERFLOW,
    /* ec = */ SST_EC_INTEGER_OVERFLOW_STATUS,
  },
  {
    /* name = */ "SST_INTERNAL_ERROR",
    /* value = */ SST_INTERNAL_ERROR,
    /* ec = */ SST_EC_INTERNAL_ERROR_STATUS,
  },
  {
    /* name = */ "SST_INVALID_ALIASING",
    /* value = */ SST_INVALID_ALIASING,
    /* ec = */ SST_EC_INVALID_ALIASING_STATUS,
  },
  {
    /* name = */ "SST_INVALID_ARGUMENT",
    /* value = */ SST_INVALID_ARGUMENT,
    /* ec = */ SST_EC_INVALID_ARGUMENT_STATUS,
  },
  {
    /* name = */ "SST_INVALID_ARRAY_INDEX",
    /* value = */ SST_INVALID_ARRAY_INDEX,
    /* ec = */ SST_EC_INVALID_ARRAY_INDEX_STATUS,
  },
  {
    /* name = */ "SST_INVALID_ARRAY_SIZE",
    /* value = */ SST_INVALID_ARRAY_SIZE,
    /* ec = */ SST_EC_INVALID_ARRAY_SIZE_STATUS,
  },
  {
    /* name = */ "SST_INVALID_LIST_INDEX",
    /* value = */ SST_INVALID_LIST_INDEX,
    /* ec = */ SST_EC_INVALID_LIST_INDEX_STATUS,
  },
  {
    /* name = */ "SST_INVALID_LIST_SIZE",
    /* value = */ SST_INVALID_LIST_SIZE,
    /* ec = */ SST_EC_INVALID_LIST_SIZE_STATUS,
  },
  {
    /* name = */ "SST_INVALID_OPERAND",
    /* value = */ SST_INVALID_OPERAND,
    /* ec = */ SST_EC_INVALID_OPERAND_STATUS,
  },
  {
    /* name = */ "SST_INVALID_OPERATION",
    /* value = */ SST_INVALID_OPERATION,
    /* ec = */ SST_EC_INVALID_OPERATION_STATUS,
  },
  {
    /* name = */ "SST_INVALID_OPTION",
    /* value = */ SST_INVALID_OPTION,
    /* ec = */ SST_EC_INVALID_OPTION_STATUS,
  },
  {
    /* name = */ "SST_INVALID_OPTION_NAME",
    /* value = */ SST_INVALID_OPTION_NAME,
    /* ec = */ SST_EC_INVALID_OPTION_NAME_STATUS,
  },
  {
    /* name = */ "SST_INVALID_OPTION_VALUE",
    /* value = */ SST_INVALID_OPTION_VALUE,
    /* ec = */ SST_EC_INVALID_OPTION_VALUE_STATUS,
  },
  {
    /* name = */ "SST_INVALID_POINTER",
    /* value = */ SST_INVALID_POINTER,
    /* ec = */ SST_EC_INVALID_POINTER_STATUS,
  },
  {
    /* name = */ "SST_LIMIT_EXCEEDED",
    /* value = */ SST_LIMIT_EXCEEDED,
    /* ec = */ SST_EC_LIMIT_EXCEEDED_STATUS,
  },
  {
    /* name = */ "SST_LONGPTR_NOT_SUPPORTED",
    /* value = */ SST_LONGPTR_NOT_SUPPORTED,
    /* ec = */ SST_EC_LONGPTR_NOT_SUPPORTED_STATUS,
  },
  {
    /* name = */ "SST_MISSING_ARRAY_SENTINEL",
    /* value = */ SST_MISSING_ARRAY_SENTINEL,
    /* ec = */ SST_EC_MISSING_ARRAY_SENTINEL_STATUS,
  },
  {
    /* name = */ "SST_MISSING_CASE",
    /* value = */ SST_MISSING_CASE,
    /* ec = */ SST_EC_MISSING_CASE_STATUS,
  },
  {
    /* name = */ "SST_MISSING_LIST_SENTINEL",
    /* value = */ SST_MISSING_LIST_SENTINEL,
    /* ec = */ SST_EC_MISSING_LIST_SENTINEL_STATUS,
  },
  {
    /* name = */ "SST_MISSING_OPTION_VALUE",
    /* value = */ SST_MISSING_OPTION_VALUE,
    /* ec = */ SST_EC_MISSING_OPTION_VALUE_STATUS,
  },
  {
    /* name = */ "SST_NEGATIVE_ARRAY_INDEX",
    /* value = */ SST_NEGATIVE_ARRAY_INDEX,
    /* ec = */ SST_EC_NEGATIVE_ARRAY_INDEX_STATUS,
  },
  {
    /* name = */ "SST_NEGATIVE_ARRAY_SIZE",
    /* value = */ SST_NEGATIVE_ARRAY_SIZE,
    /* ec = */ SST_EC_NEGATIVE_ARRAY_SIZE_STATUS,
  },
  {
    /* name = */ "SST_NEGATIVE_LIST_INDEX",
    /* value = */ SST_NEGATIVE_LIST_INDEX,
    /* ec = */ SST_EC_NEGATIVE_LIST_INDEX_STATUS,
  },
  {
    /* name = */ "SST_NEGATIVE_LIST_SIZE",
    /* value = */ SST_NEGATIVE_LIST_SIZE,
    /* ec = */ SST_EC_NEGATIVE_LIST_SIZE_STATUS,
  },
  {
    /* name = */ "SST_NONNULL_POINTER",
    /* value = */ SST_NONNULL_POINTER,
    /* ec = */ SST_EC_NONNULL_POINTER_STATUS,
  },
  {
    /* name = */ "SST_NOT_IMPLEMENTED",
    /* value = */ SST_NOT_IMPLEMENTED,
    /* ec = */ SST_EC_NOT_IMPLEMENTED_STATUS,
  },
  {
    /* name = */ "SST_NOT_SUPPORTED",
    /* value = */ SST_NOT_SUPPORTED,
    /* ec = */ SST_EC_NOT_SUPPORTED_STATUS,
  },
  {
    /* name = */ "SST_NULL_POINTER",
    /* value = */ SST_NULL_POINTER,
    /* ec = */ SST_EC_NULL_POINTER_STATUS,
  },
  {
    /* name = */ "SST_OUT_OF_MEMORY",
    /* value = */ SST_OUT_OF_MEMORY,
    /* ec = */ SST_EC_OUT_OF_MEMORY_STATUS,
  },
  {
    /* name = */ "SST_OUT_OF_RANGE",
    /* value = */ SST_OUT_OF_RANGE,
    /* ec = */ SST_EC_OUT_OF_RANGE_STATUS,
  },
  {
    /* name = */ "SST_OVERSIZE_ARRAY_INDEX",
    /* value = */ SST_OVERSIZE_ARRAY_INDEX,
    /* ec = */ SST_EC_OVERSIZE_ARRAY_INDEX_STATUS,
  },
  {
    /* name = */ "SST_OVERSIZE_LIST_INDEX",
    /* value = */ SST_OVERSIZE_LIST_INDEX,
    /* ec = */ SST_EC_OVERSIZE_LIST_INDEX_STATUS,
  },
  {
    /* name = */ "SST_PARSE_FAILURE",
    /* value = */ SST_PARSE_FAILURE,
    /* ec = */ SST_EC_PARSE_FAILURE_STATUS,
  },
  {
    /* name = */ "SST_SUCCESS",
    /* value = */ SST_SUCCESS,
    /* ec = */ SST_EC_FAILURE_STATUS,
  },
  {
    /* name = */ "SST_UNKNOWN",
    /* value = */ SST_UNKNOWN,
    /* ec = */ SST_EC_FAILURE_STATUS,
  },
  {
    /* name = */ "SST_WILD_POINTER",
    /* value = */ SST_WILD_POINTER,
    /* ec = */ SST_EC_WILD_POINTER_STATUS,
  },
  {
    /* name = */ "SST_ZERO_ARRAY_INDEX",
    /* value = */ SST_ZERO_ARRAY_INDEX,
    /* ec = */ SST_EC_ZERO_ARRAY_INDEX_STATUS,
  },
  {
    /* name = */ "SST_ZERO_ARRAY_SIZE",
    /* value = */ SST_ZERO_ARRAY_SIZE,
    /* ec = */ SST_EC_ZERO_ARRAY_SIZE_STATUS,
  },
  {
    /* name = */ "SST_ZERO_LIST_INDEX",
    /* value = */ SST_ZERO_LIST_INDEX,
    /* ec = */ SST_EC_ZERO_LIST_INDEX_STATUS,
  },
  {
    /* name = */ "SST_ZERO_LIST_SIZE",
    /* value = */ SST_ZERO_LIST_SIZE,
    /* ec = */ SST_EC_ZERO_LIST_SIZE_STATUS,
  },
};
