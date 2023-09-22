#! /bin/sh -

#
# Copyright (C) 2012-2023 Stealth Software Technologies, Inc.
#
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without
# restriction, including without limitation the rights to use,
# copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following
# conditions:
#
# The above copyright notice and this permission notice (including
# the next paragraph) shall be included in all copies or
# substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
# OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.
#
# SPDX-License-Identifier: MIT
#

#
# This script uses the SST Bash library to bootstrap from /bin/sh into
# bash. See the Bash library > Bootstrapping section of the SST manual
# for more information.
#

#-----------------------------------------------------------------------
# Include the SST Bash library
#-----------------------------------------------------------------------
#
# Include the first sst.bash file found by searching up the directory
# tree starting from the location of this script file. If no such file
# is found, fall back to including plain sst.bash with PATH resolution.
#
# This section is written in portable shell to ensure it works properly
# in any shell.
#

case ${SST_SEARCH_UP_X-} in '')
  case $0 in /*)
    SST_SEARCH_UP_X=$0
  ;; *)
    SST_SEARCH_UP_X=./$0
  esac
  SST_SEARCH_UP_R='\(.*/\)'
  SST_SEARCH_UP_X=`
    expr "x${SST_SEARCH_UP_X?}" : "x${SST_SEARCH_UP_R?}"
  `. || exit $?
  unset SST_SEARCH_UP_R
  SST_SEARCH_UP_X=`
    cd "${SST_SEARCH_UP_X?}" || exit $?
    while :; do
      if test -f sst.bash; then
        case ${PWD?} in *[!/]*)
          printf '%s\n' "${PWD?}"/ || exit $?
        ;; *)
          printf '%s\n' "${PWD?}" || exit $?
        esac
        exit
      fi
      case ${PWD?} in *[!/]*)
        cd ..
      ;; *)
        exit
      esac
    done
  ` || exit $?
  export SST_SEARCH_UP_X
esac
set -e || exit $?
. "${SST_SEARCH_UP_X?}"sst.bash
unset SST_SEARCH_UP_X

#-----------------------------------------------------------------------

function main {

  local archive_file
  local archive_name
  local archive_tmpdir
  local base
  local compiler
  local compilers
  local -a entities
  local entity_regex
  local file_regex
  local ident
  local namespace
  local namespace_regex
  local parse_options
  local -a seen_array
  local seen_list
  local suffix
  local x
  local y
  local ys
  local z

  #---------------------------------------------------------------------

  base=$(sst_get_prefix "$BASH_SOURCE")
  readonly base

  if [[ "$base" != src/c-cpp/ ]]; then
    sst_barf "You must run this script from the root of the project."
  fi

  ident='[A-Z_a-z][0-9A-Z_a-z]*'
  readonly ident

  entity_regex="^(sst(::$ident)+(\\.cpp)?|(sst|SST)_$ident(\\.c(pp)?)?)\$"
  readonly entity_regex

  file_regex="^$base(include|lib)/sst(/$ident(-$ident)*)+\\.([ch](pp)?|c\\.c)\$"
  readonly file_regex

  namespace_regex="^$ident(::$ident)*\$"
  readonly namespace_regex

  namespace=sst
  entities=()

  parse_options=1
  set x "$@"
  while shift && (($# > 0)); do

    if ((parse_options)); then

      #-----------------------------------------------------------------
      # Options terminator
      #-----------------------------------------------------------------

      sst_parse_opt -- forbidden : "$@"
      eval "$pop"
      if ((got)); then
        parse_options=
        continue
      fi

      #-----------------------------------------------------------------
      # --help
      #-----------------------------------------------------------------

      sst_parse_opt --help forbidden : "$@"
      eval "$pop"
      if ((got)); then
        sst_ihs <<<"
          Usage: $0 [--namespace=<namespace=sst>] [<entity>]...
        "
        exit 0
      fi

      #-----------------------------------------------------------------
      # --namespace
      #-----------------------------------------------------------------

      sst_parse_opt --namespace : "$@"
      eval "$pop"
      if ((got)); then
        namespace=$arg
        if [[ ! "$namespace" =~ $namespace_regex ]]; then
          namespace=$(sst_smart_quote "$namespace")
          sst_barf "Invalid --namespace: $namespace"
        fi
        continue
      fi

      #-----------------------------------------------------------------
      # Unknown options
      #-----------------------------------------------------------------

      sst_unknown_opt "$1"

      #-----------------------------------------------------------------

    fi

    entities+=("$1")

  done
  readonly parse_options

  readonly namespace
  readonly entities

  archive_name=${namespace//::/_}
  readonly archive_name

  archive_file=$archive_name.tar.gz
  readonly archive_file

  archive_tmpdir=$sst_tmpdir/$archive_name
  readonly archive_tmpdir

  y=build-aux/autogen.started
  z=build-aux/autogen.success
  if [[ ! -f $y ]]; then
    sst_info "Running ./autogen because $y does not exist."
    ./autogen
  fi
  if [[ ! -f $z ]]; then
    sst_barf "$y exists without $z."
  fi

  y=build-aux/configure.started
  z=build-aux/configure.success
  if [[ ! -f $y ]]; then
    sst_info "Running ./configure because $y does not exist."
    ./configure --with-build-groups=cpp SUBSET_LIBRARY=1
  fi
  if [[ ! -f $z ]]; then
    sst_barf "$y exists without $z."
  fi

  x=$(./config.status --config)
  if [[ "$x" != *'SUBSET_LIBRARY=1'* ]]; then
    sst_info \
      "Rerunning ./configure because the previous run was not used to" \
      "build a subset library. The command-line arguments from the" \
      "previous run will be reused." \
    ;
    eval ./configure "$x" SUBSET_LIBRARY=1
  fi

  make ${base}all_sources

  seen_array=()
  seen_list=

  set x "${entities[@]}"
  shift
  while (($# > 0)); do

    x=$1
    shift

    #-------------------------------------------------------------------
    # Entity name operands
    #-------------------------------------------------------------------
    #
    # Replace any entity name operand with the path to its catalog
    # header and loop back to the top of the operand processing loop.
    # The operand can be suffixed with ".c" or ".cpp" to disambiguate
    # between C and C++ (e.g., for SST_ASSERT).
    #

    if [[ "$x" =~ $entity_regex ]]; then
      if [[ $x == *.c ]]; then
        x=${x%.*}
        x=${base}include/sst/catalog/$x.h
      elif [[ $x == *.cpp ]]; then
        x=${x%.*}
        x=${x//::/\/}
        x=${base}include/sst/catalog/${x#sst/}.hpp
      elif [[ $x == @(sst|SST)_* ]]; then
        y=$x
        x=${base}include/sst/catalog/$x.h
        if [[ ! -f $x ]]; then
          x+=pp
        elif [[ -f ${x}pp ]]; then
          sst_barf \
            "Ambiguous entity name: $y. Both $x and ${x}pp exist." \
            "Specify $y.c or $y.cpp instead." \
          ;
        fi
      else
        x=${x//::/\/}
        x=${base}include/sst/catalog/${x#sst/}.hpp
      fi
      set $x "$@"
      continue
    fi

    #-------------------------------------------------------------------
    # Source file operands
    #-------------------------------------------------------------------
    #
    # Any operand that is not an entity name must be a path to a source
    # file to process.
    #

    if [[ ! "$x" =~ $file_regex ]]; then
      x=$(sst_quote "$x")
      y=$(sst_quote "$file_regex")
      sst_barf "Invalid file path: $x. File paths must match the" \
               "following regular expression: $y."
    fi

    if [[ "$seen_list" == *" $x "* ]]; then
      continue
    fi
    seen_list+=" $x "
    seen_array+=(${x#$base})

    if [[ ! -f $x ]]; then
      sst_barf "File not found: $x"
    fi

    if [[ $x == *.h* ]]; then
      y=${x#"$base"*/}
      y=${y%.*}
      for z in c cpp c.c; do
        z=${base}lib/$y.$z
        if [[ -f "$z" ]]; then
          set -- "$z" "$@"
        fi
      done
      for z in ${base}lib/$y/**/*.@(c|cpp); do
        set -- "$z" "$@"
      done
    fi

    ys=$(sed -n '
      s|^ *# *include *<\(sst/[^>]*\)>.*|'$base'include/\1|p
    ' $x)
    for y in $ys; do
      z=${y/#"$base"include/"$base"lib}
      if [[ -f "$y" ]]; then
        if [[ -f "$z" ]]; then
          y=$(sst_quote "$y")
          z=$(sst_quote "$z")
          sst_barf "Both $y and $z exist."
        fi
      elif [[ -f "$z" ]]; then
        y=$z
      else
        y=$(sst_quote "$y")
        z=$(sst_quote "$z")
        sst_barf "Neither $y nor $z exists."
      fi
      set x "$y" "$@"
      shift
    done

  done

  readonly seen_array
  readonly seen_list

  (cd $base; tar c "${seen_array[@]}") | (

    mkdir "$archive_tmpdir"
    cd "$archive_tmpdir"
    tar x

    if [[ $namespace != sst ]]; then

      c_prefix=${namespace//::/_}_
      readonly c_prefix

      m_prefix=$(tr a-z A-Z <<<$c_prefix)
      readonly m_prefix

      dirs=${namespace//::/\/}
      readonly dirs

      ns_open="namespace ${namespace//::/ \{ namespace } {"
      readonly ns_open

      ns_close=${namespace//::/\}}
      ns_close=}${ns_close//[!\}]/}
      ns_close+=" // namespace $namespace"
      readonly ns_close

      for x in **/*.*; do
        awk \
          -v ns=$namespace \
          -v c_prefix=$c_prefix \
          -v m_prefix=$m_prefix \
          -v dirs=$dirs \
          -v ns_open="$ns_open" \
          -v ns_close="$ns_close" \
          '
            BEGIN {
              i = 0;
              ++i;
              xs[i] = "<sst/";
              ys[i] = "<" dirs "/";
              ++i;
              xs[i] = "^(::)?sst::";
              ys[i] = ns "::";
              ++i;
              xs[i] = "^sst_";
              ys[i] = c_prefix;
              ++i;
              xs[i] = "^SST_";
              ys[i] = m_prefix;
              ++i;
              xs[i] = "[^0-9A-Z_a-z](::)?sst::";
              ys[i] = ns "::";
              ++i;
              xs[i] = "[^0-9A-Z_a-z]sst_";
              ys[i] = c_prefix;
              ++i;
              xs[i] = "[^0-9A-Z_a-z]SST_";
              ys[i] = m_prefix;
              ++i;
              xs[i] = "CATALOG_SST_";
              ys[i] = "CATALOG_" m_prefix;
              ++i;
              xs[i] = "PRIVATE_SST_";
              ys[i] = "PRIVATE_" m_prefix;
              ++i;
              xs[i] = "namespace sst {";
              ys[i] = ns_open;
              ++i;
              xs[i] = "} // namespace sst";
              ys[i] = ns_close;
            }
            {
              rest = $0;
              while (1) {
                ri = -1;
                for (i in xs) {
                  match(rest, xs[i]);
                  if (RSTART > 0 && (ri < 0 || RSTART < ri)) {
                    ri = RSTART;
                    rn = RLENGTH;
                    x = xs[i];
                    y = ys[i];
                  }
                }
                if (ri < 0) {
                  break;
                }
                printf "%s", substr(rest, 1, ri - 1);
                rest = substr(rest, ri);
                r = substr(rest, 1, rn);
                if (index(r, "::sst::") > 0) {
                  y = "::" y;
                }
                if (x ~ /^\[/) {
                  y = substr(r, 1, 1) y;
                }
                # Note that these two gsub calls do the right thing for
                # historical AWK, GNU AWK, and POSIX AWK. Do not try to
                # combine them into one gsub call.
                gsub(/\\/, "&&", y);
                gsub(/&/, "\\\\&", y);
                sub(x, y, r);
                printf "%s", r;
                rest = substr(rest, rn + 1);
              }
              print rest;
            }
          ' \
          $x >$x.tmp \
        ;
        mv -f $x.tmp $x
      done

      for x in **/sst_*.*; do
        mv $x ${x/\/sst_/\/$c_prefix}
      done
      for x in **/SST_*.*; do
        mv $x ${x/\/SST_/\/$m_prefix}
      done

      for x in include lib; do
        if [[ -e $x/sst ]]; then
          mkdir -p t/$dirs
          rmdir t/$dirs
          mv -f $x/sst t/$dirs
          mv -f t/* $x
          rmdir t
        fi
      done

    fi

  )

  #---------------------------------------------------------------------
  # Generate CMakeLists.txt
  #---------------------------------------------------------------------

  (
    cd "$archive_tmpdir"
    xs=
    for x in **/*.@(c|cpp); do
      xs+='  '$x$'\n'
    done
    cat >CMakeLists.txt <<EOF
#
# Copyright (C) 2012-2023 Stealth Software Technologies, Inc.
#
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without
# restriction, including without limitation the rights to use,
# copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following
# conditions:
#
# The above copyright notice and this permission notice (including
# the next paragraph) shall be included in all copies or
# substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
# OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.
#
# SPDX-License-Identifier: MIT
#

cmake_minimum_required(VERSION 3.10)

project(
  $archive_name
  LANGUAGES C CXX
)

add_library($archive_name STATIC
$xs)

target_include_directories($archive_name PUBLIC include)
EOF

    if false \
      || [[ -f include/sst/catalog/SST_WITH_OPENSSL_CRYPTO.h ]] \
      || [[ -f include/sst/catalog/SST_WITH_OPENSSL_SSL.h ]] \
    ; then
      x=build-aux/cmake/with_openssl.cmake
      sst_mkdir_p_only $x
      cp "$sst_rundir"/$x $x
      echo "include($x)" >>CMakeLists.txt
    fi

  )

  #---------------------------------------------------------------------

  case $archive_file in *.tar.gz)
    (
      cd "$sst_tmpdir"
      tar c "$archive_name"
    ) | gzip >"$archive_file"
  ;; *)
    x=$(sst_quote "$archive_file")
    sst_barf "Unknown output file type: $x."
  esac

}

main "$@"
