/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_status_implies.h>
#include <sst/sst_status_implies.h>

/* begin_includes */

#include <sst/SST_ALLOCATION_FAILED.h>
#include <sst/SST_ALLOCATION_IMPOSSIBLE.h>
#include <sst/SST_ALWAYS_FAILS.h>
#include <sst/SST_FAILURE.h>
#include <sst/SST_FALSE.h>
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
#include <sst/SST_TRUE.h>
#include <sst/SST_WILD_POINTER.h>
#include <sst/SST_ZERO_ARRAY_INDEX.h>
#include <sst/SST_ZERO_ARRAY_SIZE.h>
#include <sst/SST_ZERO_LIST_INDEX.h>
#include <sst/SST_ZERO_LIST_SIZE.h>
#include <sst/sst_bool.h>
#include <sst/sst_status.h>

/* end_includes */

sst_bool (sst_status_implies)(
  sst_status const s1,
  sst_status const s2
) {
  if (s1 > SST_STATUS_MAXVAL) {
    return SST_FALSE;
  }
  if (s2 > SST_STATUS_MAXVAL) {
    return SST_FALSE;
  }
  if (s1 == s2) {
    return SST_TRUE;
  }
  switch (s1) {
    default: {
    #define P(p) } break; case p: switch (s2) {
    #define Q(q) case q: return SST_TRUE;

    /*
     * The list of implication definitions is below this comment. To
     * sort the list in Vim, put your cursor on any of the following
     * lines and type {y}}:@" and press enter:

             let sst_status_implies_view = winsaveview()
             let sst_status_implies_home = getcurpos()
             call setpos('.', sst_status_implies_home)
             /\mP/,/\m#/-1g/\mP(.*\n.*Q(/.+1,/\m^$/-1sort u
             call setpos('.', sst_status_implies_home)
             /\mP/,/\m#/-1s/\m\n\(.*Q(\)/\b\1/
             call setpos('.', sst_status_implies_home)
             /\mP/,/\m#/-1g/\m^$/d _
             call setpos('.', sst_status_implies_home)
             /\mP/,/\m#/-1sort u
             call setpos('.', sst_status_implies_home)
             /\mP/,/\m#/-1s/\m$/\r/
             call setpos('.', sst_status_implies_home)
             /\mP/,/\m#/-1s/\m\b/\r/g
             call histdel('search', -1)
             call winrestview(sst_status_implies_view)
             unlet sst_status_implies_home
             unlet sst_status_implies_view

     */

    P(SST_ALLOCATION_FAILED)
      Q(SST_FAILURE)
      Q(SST_OUT_OF_MEMORY)

    P(SST_ALLOCATION_IMPOSSIBLE)
      Q(SST_FAILURE)
      Q(SST_LIMIT_EXCEEDED)
      Q(SST_OUT_OF_MEMORY)

    P(SST_ALWAYS_FAILS)
      Q(SST_FAILURE)

    P(SST_FAILURE)

    P(SST_INTEGER_OVERFLOW)
      Q(SST_FAILURE)

    P(SST_INTERNAL_ERROR)
      Q(SST_FAILURE)

    P(SST_INVALID_ALIASING)
      Q(SST_FAILURE)
      Q(SST_INVALID_ARGUMENT)
      Q(SST_INVALID_POINTER)
      Q(SST_NONNULL_POINTER)

    P(SST_INVALID_ARGUMENT)
      Q(SST_FAILURE)

    P(SST_INVALID_ARRAY_INDEX)
      Q(SST_FAILURE)
      Q(SST_INVALID_ARGUMENT)
      Q(SST_INVALID_LIST_INDEX)

    P(SST_INVALID_ARRAY_SIZE)
      Q(SST_FAILURE)
      Q(SST_INVALID_ARGUMENT)
      Q(SST_INVALID_LIST_SIZE)

    P(SST_INVALID_LIST_INDEX)
      Q(SST_FAILURE)
      Q(SST_INVALID_ARGUMENT)

    P(SST_INVALID_LIST_SIZE)
      Q(SST_FAILURE)
      Q(SST_INVALID_ARGUMENT)

    P(SST_INVALID_OPERAND)
      Q(SST_FAILURE)
      Q(SST_INVALID_ARGUMENT)

    P(SST_INVALID_OPERATION)
      Q(SST_FAILURE)
      Q(SST_INVALID_ARGUMENT)

    P(SST_INVALID_OPTION)
      Q(SST_FAILURE)
      Q(SST_INVALID_ARGUMENT)

    P(SST_INVALID_OPTION_NAME)
      Q(SST_FAILURE)
      Q(SST_INVALID_ARGUMENT)
      Q(SST_INVALID_OPTION)

    P(SST_INVALID_OPTION_VALUE)
      Q(SST_FAILURE)
      Q(SST_INVALID_ARGUMENT)
      Q(SST_INVALID_OPTION)

    P(SST_INVALID_POINTER)
      Q(SST_FAILURE)
      Q(SST_INVALID_ARGUMENT)

    P(SST_LIMIT_EXCEEDED)
      Q(SST_FAILURE)

    P(SST_LONGPTR_NOT_SUPPORTED)
      Q(SST_FAILURE)
      Q(SST_INVALID_ARGUMENT)
      Q(SST_NOT_SUPPORTED)

    P(SST_MISSING_ARRAY_SENTINEL)
      Q(SST_FAILURE)
      Q(SST_INVALID_ARGUMENT)
      Q(SST_MISSING_LIST_SENTINEL)

    P(SST_MISSING_CASE)
      Q(SST_FAILURE)
      Q(SST_INTERNAL_ERROR)

    P(SST_MISSING_LIST_SENTINEL)
      Q(SST_FAILURE)
      Q(SST_INVALID_ARGUMENT)

    P(SST_MISSING_OPTION_VALUE)
      Q(SST_FAILURE)
      Q(SST_INVALID_ARGUMENT)
      Q(SST_INVALID_OPTION)

    P(SST_NEGATIVE_ARRAY_INDEX)
      Q(SST_FAILURE)
      Q(SST_INVALID_ARGUMENT)
      Q(SST_INVALID_ARRAY_INDEX)
      Q(SST_INVALID_LIST_INDEX)
      Q(SST_NEGATIVE_LIST_INDEX)

    P(SST_NEGATIVE_ARRAY_SIZE)
      Q(SST_FAILURE)
      Q(SST_INVALID_ARGUMENT)
      Q(SST_INVALID_ARRAY_SIZE)
      Q(SST_INVALID_LIST_SIZE)
      Q(SST_NEGATIVE_LIST_SIZE)

    P(SST_NEGATIVE_LIST_INDEX)
      Q(SST_FAILURE)
      Q(SST_INVALID_ARGUMENT)
      Q(SST_INVALID_LIST_INDEX)

    P(SST_NEGATIVE_LIST_SIZE)
      Q(SST_FAILURE)
      Q(SST_INVALID_ARGUMENT)
      Q(SST_INVALID_LIST_SIZE)

    P(SST_NONNULL_POINTER)
      Q(SST_FAILURE)
      Q(SST_INVALID_ARGUMENT)
      Q(SST_INVALID_POINTER)

    P(SST_NOT_IMPLEMENTED)
      Q(SST_FAILURE)
      Q(SST_INTERNAL_ERROR)

    P(SST_NOT_SUPPORTED)
      Q(SST_FAILURE)
      Q(SST_INVALID_ARGUMENT)

    P(SST_NULL_POINTER)
      Q(SST_FAILURE)
      Q(SST_INVALID_ARGUMENT)
      Q(SST_INVALID_POINTER)

    P(SST_OUT_OF_MEMORY)
      Q(SST_FAILURE)

    P(SST_OUT_OF_RANGE)
      Q(SST_FAILURE)
      Q(SST_INTEGER_OVERFLOW)

    P(SST_OVERSIZE_ARRAY_INDEX)
      Q(SST_FAILURE)
      Q(SST_INVALID_ARGUMENT)
      Q(SST_INVALID_ARRAY_INDEX)
      Q(SST_INVALID_LIST_INDEX)
      Q(SST_OVERSIZE_LIST_INDEX)

    P(SST_OVERSIZE_LIST_INDEX)
      Q(SST_FAILURE)
      Q(SST_INVALID_ARGUMENT)
      Q(SST_INVALID_LIST_INDEX)

    P(SST_PARSE_FAILURE)
      Q(SST_FAILURE)

    P(SST_SUCCESS)

    P(SST_WILD_POINTER)
      Q(SST_FAILURE)
      Q(SST_INVALID_ARGUMENT)
      Q(SST_INVALID_POINTER)
      Q(SST_NONNULL_POINTER)

    P(SST_ZERO_ARRAY_INDEX)
      Q(SST_FAILURE)
      Q(SST_INVALID_ARGUMENT)
      Q(SST_INVALID_ARRAY_INDEX)
      Q(SST_INVALID_LIST_INDEX)
      Q(SST_ZERO_LIST_INDEX)

    P(SST_ZERO_ARRAY_SIZE)
      Q(SST_FAILURE)
      Q(SST_INVALID_ARGUMENT)
      Q(SST_INVALID_ARRAY_SIZE)
      Q(SST_INVALID_LIST_SIZE)
      Q(SST_ZERO_LIST_SIZE)

    P(SST_ZERO_LIST_INDEX)
      Q(SST_FAILURE)
      Q(SST_INVALID_ARGUMENT)
      Q(SST_INVALID_LIST_INDEX)

    P(SST_ZERO_LIST_SIZE)
      Q(SST_FAILURE)
      Q(SST_INVALID_ARGUMENT)
      Q(SST_INVALID_LIST_SIZE)

    #undef Q
    #undef P
    } break;
  }
  return SST_FALSE;
}
