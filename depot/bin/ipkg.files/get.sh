#!/bin/bash

if [ $# -ne 2 ]; then
  echo "Usage: ipkg get <package ID> <output file>" >&2
  exit 1
fi

GetPackage() {
  local package_id="${1}"
  local output_file="${2}"

  local url="${IPKG_HOST}/alias/${package_id}"
  if [[ "${package_id}" =~ ^[0-9a-f]{32,}$ ]]; then
    url="${IPKG_HOST}/fragment/${package_id}"
  fi
  local hashes=($(curl --silent "${url}"))
  if [ "${#hashes[@]}" -eq 0 ]; then
    echo "No such pckage." >&2
    exit 2
  fi

  for hash in "${hashes[@]}"; do
    if [[ "${hash}" =~ ^[0-9a-f]{32,}$ ]]; then
      echo "Loading ${hash}..." >&2
      throttle
      curl --silent -o "${TMPDIR}/${hash}" "${IPKG_HOST}/fragment/${hash}" &
    else
      echo "Bad hash key: ${hash}" >&2
      exit 2
    fi
  done
  wait
  for hash in "${hashes[@]}"; do
    if [ ! -f "${TMPDIR}/${hash}" ]; then
      echo "Fragment is missing: ${hash}" >&2
      exit 2
    fi
    if [ "$(md5 "${TMPDIR}/${hash}")" != "${hash}" ]; then
      echo "File is broken: ${hash}" >&2
      ls -l "${TMPDIR}/${hash}" >&2
      echo "MD5 hash: $(md5 "${TMPDIR}/${hash}")" >&2
      exit 2
    fi
    cat "${TMPDIR}/${hash}"
  done >"${output_file}"
}

GetPackage "$@"
