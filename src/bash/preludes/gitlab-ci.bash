#
# For the copyright information for this file, please search up the
# directory tree for the first COPYING file.
#

#
# Bootstrap into the PATH-resolved bash. Don't unset SST_BASH_BOOTSTRAP
# because this would cause an infinite bootstrap loop with the standard
# prelude when we load it. Only the standard prelude does the unset.
#

case ${SST_BASH_BOOTSTRAP+x}y$# in
  y0) SST_BASH_BOOTSTRAP=x bash - "$0"     ; exit $? ;;
  y*) SST_BASH_BOOTSTRAP=x bash - "$0" "$@"; exit $? ;;
esac

#
# Load the standard prelude.
#

x=$BASH_SOURCE
[[ "$x" == /* ]] || x=$PWD/$x
. "${x%/*}"/standard.bash

#
# Turn on command tracing so we can see what's going on in the job log
# of the GitLab UI. This prepends a green colored "trace: " heading to
# each traced command, which is similar to how GitLab traces the direct
# job commands in green.
#

PS4='+ \[\e[0;32m\]\[\e[1m\]trace:\[\e[0m\] '
set -x

#
# Determine whether we're running on an archivist runner.
#

if test -f /archivist.gitlab-username; then
  archivist=true
else
  archivist=false
fi
readonly archivist

case $archivist in
  true)
    u=$(cat /archivist.gitlab-username)
    docker login \
      --username "$u" \
      --password-stdin \
      registry.stealthsoftwareinc.com \
      </archivist.gitlab-password \
    ;
    unset u
  ;;
esac
