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
  sst_quote \
  sst_underscore_slug \
;

expect() {
  local e x y
  e=$(cat)
  x=$(eval "$e" | sst_quote)
  y=$(sst_quote <<<"$1")
  if [[ "$x" == "$y" ]]; then
    printf 'pass: $(%s) == %s\n' "$e" "$y"
  else
    printf 'fail: $(%s) == %s, got %s\n' "$e" "$y" "$x"
    exit 1
  fi
}

expect '' <<'EOF'
sst_underscore_slug </dev/null
EOF

expect '' <<'EOF'
sst_underscore_slug ''
EOF

expect foo <<'EOF'
sst_underscore_slug foo
EOF

expect _ <<'EOF'
sst_underscore_slug -
EOF

expect foo_bar <<'EOF'
sst_underscore_slug foo bar
EOF

expect foo_bar <<'EOF'
sst_underscore_slug foo-bar
EOF

expect __foo__bar_ <<'EOF'
sst_underscore_slug --foo -bar-
EOF
