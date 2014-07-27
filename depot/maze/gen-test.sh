#!/bin/bash

make

GEN=./build/flame-binary/depot/maze/gen

${GEN} -size=15  -ghosts=2  -powerpills=2  -maker=digger > depot/maze/test-15.txt
${GEN} -size=22  -ghosts=4  -powerpills=4  -maker=digger > depot/maze/test-22.txt
${GEN} -size=32  -ghosts=5  -powerpills=5  -maker=digger > depot/maze/test-32.txt
${GEN} -size=50  -ghosts=6  -powerpills=6  -maker=digger > depot/maze/test-50.txt
${GEN} -size=100 -ghosts=10 -powerpills=7  -maker=digger > depot/maze/test-100.txt
${GEN} -size=150 -ghosts=15 -powerpills=8  -maker=digger > depot/maze/test-150.txt
${GEN} -size=200 -ghosts=25 -powerpills=9  -maker=digger > depot/maze/test-200.txt
${GEN} -size=256 -ghosts=40 -powerpills=10 -maker=digger > depot/maze/test-256.txt

${GEN} -size=22  -ghosts=4  -powerpills=4  -maker=grid > depot/maze/test2-22.txt
${GEN} -size=32  -ghosts=5  -powerpills=5  -maker=grid > depot/maze/test2-32.txt
${GEN} -size=50  -ghosts=6  -powerpills=6  -maker=grid > depot/maze/test2-50.txt
${GEN} -size=100 -ghosts=10 -powerpills=7  -maker=grid > depot/maze/test2-100.txt
${GEN} -size=150 -ghosts=15 -powerpills=8  -maker=grid > depot/maze/test2-150.txt
${GEN} -size=200 -ghosts=25 -powerpills=9  -maker=grid > depot/maze/test2-200.txt
${GEN} -size=256 -ghosts=40 -powerpills=10 -maker=grid > depot/maze/test2-256.txt

if [ -d /dropbox ]; then
  cp -f depot/maze/*.txt /dropbox/maze/
fi
