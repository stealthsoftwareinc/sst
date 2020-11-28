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
  sst_array_cmp \
  sst_array_to_string \
  sst_barf \
;

expect() {
  local expect="$1"
  local actual="$2"
  local xs_str
  local ys_str
  xs_str=$(sst_array_to_string xs)
  ys_str=$(sst_array_to_string ys)
  if [[ "$expect" == "$actual" ]]; then
    printf 'pass: (%s <=> %s) == %s\n' \
           "$xs_str" "$ys_str" "$expect"
  else
    printf 'fail: (%s <=> %s) == %s, got %s\n' \
           "$xs_str" "$ys_str" "$expect" "$actual"
    sst_barf 'a test failed'
  fi
}

unset xs
unset ys

(
  r=$(sst_array_cmp xs ys)
  expect 0 "$r"
)

(
  xs=()
  r=$(sst_array_cmp xs ys)
  expect 0 "$r"
)

(
  ys=()
  r=$(sst_array_cmp xs ys)
  expect 0 "$r"
)

(
  xs=()
  ys=()
  r=$(sst_array_cmp xs ys)
  expect 0 "$r"
)

(
  xs=(a)
  r=$(sst_array_cmp xs ys)
  expect 1 "$r"
)

(
  ys=(a)
  r=$(sst_array_cmp xs ys)
  expect -1 "$r"
)

(
  xs=(a)
  ys=(a)
  r=$(sst_array_cmp xs ys)
  expect 0 "$r"
)

(
  xs=(a)
  ys=()
  r=$(sst_array_cmp xs ys)
  expect 1 "$r"
)

(
  xs=()
  ys=(a)
  r=$(sst_array_cmp xs ys)
  expect -1 "$r"
)

(
  xs=(a)
  ys=(b)
  r=$(sst_array_cmp xs ys)
  expect -1 "$r"
)

(
  xs=(b)
  ys=(a)
  r=$(sst_array_cmp xs ys)
  expect 1 "$r"
)

(
  xs=(a)
  ys=(a a)
  r=$(sst_array_cmp xs ys)
  expect -1 "$r"
)

(
  xs=(a a)
  ys=(a)
  r=$(sst_array_cmp xs ys)
  expect 1 "$r"
)

(
  xs=(a a)
  ys=(a a)
  r=$(sst_array_cmp xs ys)
  expect 0 "$r"
)

(
  xs[0]=b
  ys[1]=a
  r=$(sst_array_cmp xs ys)
  expect -1 "$r"
)

(
  xs[1]=b
  ys[1]=a
  r=$(sst_array_cmp xs ys)
  expect 1 "$r"
)

(
  declare -A xs
  r=$(sst_array_cmp xs ys)
  expect 0 "$r"
)

(
  declare -A ys
  r=$(sst_array_cmp xs ys)
  expect 0 "$r"
)

(
  declare -A xs
  declare -A ys
  r=$(sst_array_cmp xs ys)
  expect 0 "$r"
)

(
  declare -A ys
  ys=([a]=b)
  r=$(sst_array_cmp xs ys)
  expect -1 "$r"
)

(
  declare -A xs
  xs=([a]=b)
  r=$(sst_array_cmp xs ys)
  expect 1 "$r"
)

(
  declare -A xs
  declare -A ys
  xs=([a]=b)
  ys=([b]=a)
  r=$(sst_array_cmp xs ys)
  expect -1 "$r"
)

(
  xs=(hello)
  declare -A ys
  ys=(['0']=hello)
  r=$(sst_array_cmp xs ys)
  expect 0 "$r"
)
