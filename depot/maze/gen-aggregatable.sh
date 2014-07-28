#!/bin/bash

make

GEN=./build/flame-binary/depot/maze/gen

for seed in {0..9}; do
	${GEN} -seed=$i -size=32 -ghosts=5  -powerpills=5  -maker=digger > depot/maze/test-32---$i.txt
	${GEN} -seed=$i -size=32 -ghosts=5  -powerpills=5  -maker=grid > depot/maze/grid-32---$i.txt
	${GEN} -seed=$i -size=33 -ghosts=5  -powerpills=5  -maker=grid2 -grid2_density=0.2 > depot/maze/grid2-0.2-33---$i.txt
	${GEN} -seed=$i -size=33 -ghosts=5  -powerpills=5  -maker=grid2 -grid2_density=0.8 > depot/maze/grid2-0.8-33---$i.txt
done

if [ -d /dropbox ]; then
  cp -f depot/maze/*.txt /dropbox/maze/
fi
