#!/bin/bash

set -e -u

for target in $(find depot -name BUILD.cmake); do
  cat << 'EOM' >"${target%/BUILD.cmake}/Makefile"
all:
	pwd="$$(pwd)"; cd "$${pwd%/depot/*}"; \
	    target="depot/$${pwd##*/depot/}/..."; make "$${target}"
.PHONY: all

EOM
done
