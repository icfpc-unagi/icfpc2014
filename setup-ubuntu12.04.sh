#!/bin/bash

set -e -u

export TMPDIR="$(mktemp -d "${TMPDIR:-/tmp}/gbash.XXXXXX")"
trap "rm -rf ${TMPDIR}" EXIT

apt-get update -qq
apt-get install -y --force-yes git clang-3.4 cmake wget make g++ curl
pushd "${TMPDIR}"
wget http://www.cmake.org/files/v2.8/cmake-2.8.12.1.tar.gz
tar xvf cmake-2.8.12.1.tar.gz
cd cmake-2.8.12.1
cmake . && make -j 8
make install
popd
