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
  sst_array_to_string \
  sst_barf \
;

expect() {
  eval "
    [[ $1 == xs ]] || local -n xs=$1
  "
  local actual
  local expect
  actual=$(sst_array_to_string xs)
  expect=$2
  if [[ "$actual" == "$expect" ]]; then
    printf 'pass: %s\n' "$expect"
  else
    printf 'fail: expected %s, got %s\n' "$expect" "$actual"
    sst_barf 'test failed'
  fi
}

unset xs

(
  expect xs "()"
)

(
  xs=(a)
  expect xs "([0]='a')"
)

(
  xs=(a b)
  expect xs "([0]='a' [1]='b')"
)

(
  xs[4]=b
  xs[2]=a
  expect xs "([2]='a' [4]='b')"
)

(
  declare -A xs
  xs[hello]=a
  expect xs "(['hello']='a')"
)

(
  declare -A xs
  xs[11]=a
  expect xs "([11]='a')"
)
