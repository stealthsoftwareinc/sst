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
  sst_get_prefix \
  sst_jq_expect \
  sst_quote \
;

prelude=$(sst_get_prefix "$0")../preludes/standard.bash
prelude=$(sst_quote "$prelude")
prelude="#! /bin/sh -
. $prelude
sst_import_function sst_jq_expect
"

expect() {
  local code expect actual
  code=$(cat)
  expect=$1
  printf '%s\n%s\n' "$prelude" "$code" >"$tmpdir/script"
  actual=0
  sh "$tmpdir/script" 2>/dev/null || actual=$?
  if [[ "$actual" == "$expect" ]]; then
    printf 'pass: %s exits with status %s\n' "$code" "$expect"
  else
    printf 'fail: %s exits with status %s: got %s instead\n' "$code" "$expect" "$actual"
    exit 1
  fi
}

expect 0 <<'EOF'
sst_jq_expect '. == 0' <<<'0'
EOF

expect 1 <<'EOF'
sst_jq_expect '. == 0' <<<'1'
EOF
