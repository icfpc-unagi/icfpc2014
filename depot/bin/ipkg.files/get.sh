#!/bin/bash

if [ $# -ne 2 ]; then
  echo "Usage: ipkg get <package ID> <output file>" >&2
  exit 1
fi

if [ ! -d /mnt/ipkg_cache ]; then
  sudo mkdir -p /mnt/ipkg_cache || true
  sudo chmod 777 /mnt/ipkg_cache || true
fi

DownloadFragment() {
  local hash="$1"
  local local_cache="/mnt/ipkg_cache/${hash}"

  if [ -f "${local_cache}" ]; then
    local local_hash="$(md5 "${local_cache}")"
    if [ "${hash}" == "${local_hash}" ]; then
      cp "${local_cache}" "${TMPDIR}/${hash}"
      return
    else
      echo "Local cache is broken: ${local_cache}" >&2
      rm "${local_cache}"
    fi
  fi
  echo "Downloading from ${IPKG_HOST}/fragment/${hash}..." >&2
  curl --silent -o "${TMPDIR}/${hash}" "${IPKG_HOST}/fragment/${hash}"
  cp "${TMPDIR}/${hash}" "${local_cache}" || true
}

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
      DownloadFragment "${hash}" &
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
