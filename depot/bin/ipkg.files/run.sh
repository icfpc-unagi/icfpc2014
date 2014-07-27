#!/bin/bash

if [ $# -lt 1 ]; then
  echo "Usage: ipkg run <package ID> [-- <command> ...]" >&2
  exit 1
fi

PreparePackage() {
  local package_id="${1}"
  shift

  ipkg get "${package_id}" "${TMPDIR}/package.tar.xz"
  mkdir -p "${TMPDIR}/package"
  cd "${TMPDIR}/package"
  tar Jxvf '../package.tar.xz' >&2
  if [ "$#" -gt 0 ]; then
    ( echo '#!/bin/bash'; echo "$*" ) > bootstrap.sh
    chmod +x bootstrap.sh
  fi
  if [ ! -f bootstrap.sh ]; then
    echo "The package does not have bootstrap.sh." >&2
    exit 2
  fi
}

RunPackage() {
  Execute PreparePackage "$@"

  if [ "$(whoami)" == 'root' ]; then
    sudo --user=ninelet /bin/bash bootstrap.sh
  else
    bash bootstrap.sh
  fi
}

ulimit -t "${FLAGS_cpu_limit}"
RunPackage "$@"
