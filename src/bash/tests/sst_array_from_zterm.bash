#! /bin/sh -
#
# For the copyright information for this file, please search up the
# directory tree for the first COPYING file.
#

# Load the prelude.
case $0 in /*) x=$0 ;; *) x=./$0 ;; esac
x=`dirname "$x"` || exit $?
set -e || exit $?
. "$x"/../preludes/standard.bash

sst_import_function \
  sst_array_from_zterm \
  sst_array_to_string \
  sst_barf \
;

check() {
  local line
  local cmp
  local expect_str
  local actual_str
  line=$(caller)
  line=${line%% *}
  cmp=$(sst_array_cmp expect actual)
  expect_str=$(sst_array_to_string expect)
  if ((cmp == 0)); then
    printf 'pass: line %4s: expect %s\n' \
           "$line" "$expect_str"
  else
    actual_str=$(sst_array_to_string actual)
    printf 'fail: line %4s: expect %s, actual %s\n' \
           "$line" "$expect_str" "$actual_str"
    sst_barf 'a test failed'
  fi
}

unset expect
unset actual

(
  >"$tmpdir"/x
  sst_array_from_zterm actual <"$tmpdir"/x
  check
)

(
  expect=()
  >"$tmpdir"/x
  sst_array_from_zterm actual <"$tmpdir"/x
  check
)

(
  expect=('')
  printf '\0' >"$tmpdir"/x
  sst_array_from_zterm actual <"$tmpdir"/x
  check
)

(
  expect=('' '')
  printf '\0\0' >"$tmpdir"/x
  sst_array_from_zterm actual <"$tmpdir"/x
  check
)

(
  expect=(a)
  printf 'a\0' >"$tmpdir"/x
  sst_array_from_zterm actual <"$tmpdir"/x
  check
)

(
  expect=(a)
  printf 'a' >"$tmpdir"/x
  sst_array_from_zterm actual <"$tmpdir"/x
  check
)

(
  expect=(' ')
  printf ' \0' >"$tmpdir"/x
  sst_array_from_zterm actual <"$tmpdir"/x
  check
)

(
  expect=(' ')
  printf ' ' >"$tmpdir"/x
  sst_array_from_zterm actual <"$tmpdir"/x
  check
)

(
  expect=(a b)
  printf 'a\0b\0' >"$tmpdir"/x
  sst_array_from_zterm actual <"$tmpdir"/x
  check
)

(
  expect=(a b)
  printf 'a\0b' >"$tmpdir"/x
  sst_array_from_zterm actual <"$tmpdir"/x
  check
)

(
  expect=(' ' ' ')
  printf ' \0 ' >"$tmpdir"/x
  sst_array_from_zterm actual <"$tmpdir"/x
  check
)

(
  expect=('\' '\')
  printf '\\\0\\' >"$tmpdir"/x
  sst_array_from_zterm actual <"$tmpdir"/x
  check
)
