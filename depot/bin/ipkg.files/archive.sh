#!/bin/bash

if [ $# -lt 1 ]; then
  echo "Usage: ipkg archive -- <command> ..." >&2
  exit 1
fi

ArchivePackage() {
  mkdir -p "${TMPDIR}/package"
  ( echo '#!/bin/bash'; echo "$@" ) >"${TMPDIR}/package/bootstrap.sh"
  chmod +x "${TMPDIR}/package/bootstrap.sh"
  for file in *; do
    ln -s "$(pwd)/${file}" "${TMPDIR}/package/${file}"
  done
  cd "${TMPDIR}/package"
  echo "Compressing..." >&2
  tar Jcvfh ../package.tar.xz * >&2
  ipkg put --alias="${FLAGS_alias}" ../package.tar.xz
}

ArchivePackage "$@"
