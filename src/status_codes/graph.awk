#
# Copyright (C) 2012-2024 Stealth Software Technologies, Inc.
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
# This script reads through a graph.txt file, calling on_node(name,
# value) for each "<value> <name>" line and on_edge(name1, name2) for
# each "<name1> <name2>" line. The on_node and on_edge functions should
# be defined by another script foo.awk, which can be run in combination
# with this script with a command like "awk -f graph.awk -f foo.awk".
#
# All functions and global variables used by this script are prefixed
# with "ga_" to help prevent name collisions.
#
# The ga_file variable can optionally be set to the name of the file
# being processed to make the file name be displayed in error messages.
# This is typically done with a command like "awk -v ga_file=graph.txt".
#
# This script is written in portable awk. It should work with any awk
# implementation.
#

function ga_barf(message, line) {
  if (line) {
    message = line ":" message;
  }
  if (ga_file) {
    message = ga_file ":" message;
  }
  print message | "cat >&2";
  exit 1;
}

function ga_is_name(x) {
  return x ~ /^SST_[A-Z][0-9A-Z_]*$/;
}

function ga_is_value(x) {
  return x ~ /^(0|[1-9][0-9]*)$/;
}

function ga_expect_name(x) {
  if (!ga_is_name(x)) {
    ga_barf("invalid name: " x, NR);
  }
}

function ga_expect_nf(n) {
  if (NF != n) {
    ga_barf("expected " n " fields", NR);
    exit 1;
  }
}

{
  if (NF == 0 || $1 ~ /^#/) {
    next;
  } else if (ga_is_value($1)) {
    ga_expect_nf(2);
    name = $2;
    value = $1;
    ga_expect_name(name);
    x = ga_name_to_value[name];
    if (x != "" && x != value) {
      ga_barf(name " was already given the value " \
              x " on line " ga_name_to_line[name], NR);
    }
    x = ga_value_to_name[value];
    if (x != "" && x != name) {
      ga_barf(value " was already given the name " \
              x " on line " ga_value_to_line[value], NR);
    }
    ga_name_to_value[name] = value;
    ga_name_to_line[name] = NR;
    ga_value_to_name[value] = name;
    ga_value_to_line[value] = NR;
    on_node(name, value);
  } else {
    ga_expect_nf(2);
    name1 = $1;
    name2 = $2;
    ga_expect_name(name1);
    ga_expect_name(name2);
    if (ga_name_to_value[name1] == "") {
      ga_name_to_value[name1] = "";
    }
    if (ga_name_to_value[name2] == "") {
      ga_name_to_value[name2] = "";
    }
    if (!ga_name_pairs[name1, name2]) {
      on_edge(name1, name2);
      ga_name_pairs[name1, name2] = 1;
    }
  }
}

END {
  for (name in ga_name_to_value) {
    if (ga_name_to_value[name] == "") {
      ga_barf(name " is missing a value");
    }
  }
}
