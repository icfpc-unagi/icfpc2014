#!/bin/bash

set -e -u

for target in $(find depot -name BUILD.cmake); do
  cat << 'EOM' >"${target%/BUILD.cmake}/Makefile"
SHELL := /bin/bash

all:
	pwd="$$(pwd)"; cd "$${pwd%/depot/*}"; \
	    target="depot/$${pwd##*/depot/}/..."; make "$${target}"
.PHONY: all

test: all
	pwd="$$(pwd)"; \
	for test in "$${pwd/\/depot\///build/flame-binary/depot/}"/*_test; do \
	  "$${test}"; \
	done
.PHONY: test

EOM
done
