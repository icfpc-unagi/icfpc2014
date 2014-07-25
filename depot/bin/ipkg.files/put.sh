#!/bin/bash

if [ $# -ne 1 ]; then
  echo "Usage: ipkg put <input file>" >&2
  exit 1
fi

PutFragment() {
  local file="${1}"
  local alias="${2}"
  echo "Uploading ${file}..." >&2

  local hash="$(md5 "${file}")"
  throttle
  echo "${hash}"
  [ "$(aws s3 ls "s3://package.imoz.jp/fragment/${hash}")" != "" ] || \
      aws s3 cp "${file}" "s3://package.imoz.jp/fragment/${hash}" >/dev/null &
  if [ "${alias}" != '' ]; then
    echo "Uploading ${alias}..." >&2
    aws s3 cp "${file}" "s3://package.imoz.jp/alias/${alias}" >/dev/null &
  fi
}

PutPackage() {
  local file="${1}"
  echo "Splitting ${file}..." >&2
  split -b 500000 "${file}" "${TMPDIR}/fragment-"
  cd "${TMPDIR}"
  for file in fragment-*; do PutFragment "${file}" ''; done >list.txt; wait
  PutFragment list.txt "${FLAGS_alias}"; wait
}

PutPackage "$@"
