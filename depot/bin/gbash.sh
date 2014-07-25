#!/bin/bash
#
# Flag definitions
# ----------------
# There are four flag definitions DEFINE_int, DEFINE_string, DEFINE_bool,
# DEFINE_double.
#
# Usage
# -----
#   source gbash.sh || exit
#
#   # Write flag definitions here.
#
#   gbash::init_google "$@"
#   set -- "${GBASH_ARGV[@]}"
#   set -e -u

# Mac OSX's getopt does not supprot long flags, so this uses gnu-getopt instead
# if it is available.
if which /usr/local/opt/gnu-getopt/bin/getopt >/dev/null; then
  export PATH="/usr/local/opt/gnu-getopt/bin:${PATH}"
fi

source "$(cd $(dirname ${BASH_SOURCE:-$0}); pwd)"/shflags

__gbash_boolean_flags=()

DEFINE_bool() {
  __gbash_boolean_flags=("${__gbash_boolean_flags[@]}" "${1}")
  DEFINE_boolean "$@"
}

DEFINE_int() { DEFINE_integer "$@"; }
DEFINE_double() { DEFINE_float "$@"; }

gbash::init_google() {
  FLAGS "$@" || exit $?;
  eval GBASH_ARGV=("${FLAGS_ARGV}")

  for boolean_flag in "${__gbash_boolean_flags[@]}"; do
    if [ "$(eval echo '$FLAGS_'${boolean_flag})" == "${FLAGS_TRUE}" ]; then
      eval "FLAGS_${boolean_flag}"=1
    else
      eval "FLAGS_${boolean_flag}"=0
    fi
  done

  export TMPDIR="$(mktemp -d "${TMPDIR:-/tmp}/gbash.XXXXXX")"
  trap "rm -rf ${TMPDIR}" EXIT
}

AssertCommandsExist() {
  for command in "$@"; do
    if ! which "${command}" >/dev/null; then
      echo "A required command is not available: ${command}" >&2
      exit 2
    fi
  done
}

RequireRootPrivilege() {
  if [ "$(whoami)" != 'root' ]; then
    echo 'This program requires the root privilege' >&2
    exit 2
  fi
}

md5() { php -r 'echo md5_file($argv[1]);' "${1}"; }

throttle() {
  local counter=0
  while [ $(ps -o ppid,pid | grep ^$$ | wc -l) -gt 32 ]; do
    ((counter+=1))
    sleep "$(echo "${counter}*0.1" | bc)"
  done
}

Execute() {
  if (( FLAGS_silent )); then
    "$@" >/dev/null 2>/dev/null
  else
    "$@"
  fi
}

Escape() {
  local single_quote="'"
  local escaped_single_quote="'\"'\"'"
  for arg in "$@"; do
    echo -n "'${arg//${single_quote}/${escaped_single_quote}}' "
  done
}
