#!/bin/bash

make

GEN=./build/flame-binary/depot/maze/gen

${GEN} -size=15  -ghosts=2  -powerpills=2  -maker=digger > depot/maze/test-15.txt
${GEN} -size=22  -ghosts=4  -powerpills=4  -maker=digger > depot/maze/test-22.txt
${GEN} -size=32  -ghosts=5  -powerpills=5  -maker=digger > depot/maze/test-32.txt
${GEN} -size=40  -ghosts=5  -powerpills=5  -maker=digger > depot/maze/test-40.txt
${GEN} -size=50  -ghosts=6  -powerpills=6  -maker=digger > depot/maze/test-50.txt
${GEN} -size=70  -ghosts=8  -powerpills=7  -maker=digger > depot/maze/test-70.txt
${GEN} -size=100 -ghosts=10 -powerpills=7  -maker=digger > depot/maze/test-100.txt
${GEN} -size=150 -ghosts=15 -powerpills=8  -maker=digger > depot/maze/test-150.txt
${GEN} -size=200 -ghosts=20 -powerpills=9  -maker=digger > depot/maze/test-200.txt
${GEN} -size=256 -ghosts=30 -powerpills=10 -maker=digger > depot/maze/test-256.txt

${GEN} -size=22  -ghosts=4  -powerpills=4  -maker=grid > depot/maze/test2-22.txt
${GEN} -size=32  -ghosts=5  -powerpills=5  -maker=grid > depot/maze/test2-32.txt
${GEN} -size=40  -ghosts=5  -powerpills=5  -maker=grid > depot/maze/test2-40.txt
${GEN} -size=50  -ghosts=6  -powerpills=6  -maker=grid > depot/maze/test2-50.txt
${GEN} -size=70  -ghosts=8  -powerpills=7  -maker=grid > depot/maze/test2-70.txt
${GEN} -size=100 -ghosts=10 -powerpills=7  -maker=grid > depot/maze/test2-100.txt
${GEN} -size=150 -ghosts=15 -powerpills=8  -maker=grid > depot/maze/test2-150.txt
${GEN} -size=200 -ghosts=20 -powerpills=9  -maker=grid > depot/maze/test2-200.txt
${GEN} -size=256 -ghosts=30 -powerpills=10 -maker=grid > depot/maze/test2-256.txt

${GEN} -size=32  -ghosts=7  -powerpills=5  -maker=arena > depot/maze/arena-32.txt
${GEN} -size=50  -ghosts=8  -powerpills=6  -maker=arena > depot/maze/arena-50.txt
${GEN} -size=70  -ghosts=10 -powerpills=7  -maker=arena > depot/maze/arena-70.txt
${GEN} -size=100 -ghosts=15 -powerpills=7  -maker=arena > depot/maze/arena-100.txt
${GEN} -size=150 -ghosts=20 -powerpills=8  -maker=arena > depot/maze/arena-150.txt
${GEN} -size=200 -ghosts=30 -powerpills=9  -maker=arena > depot/maze/arena-200.txt
${GEN} -size=256 -ghosts=40 -powerpills=10 -maker=arena > depot/maze/arena-256.txt

${GEN} -width=40  -height=20  -ghosts=5 -powerpills=3 -maker=digger > depot/maze/rect-40x20.txt
${GEN} -width=80  -height=20  -ghosts=6 -powerpills=6 -maker=digger > depot/maze/rect-80x20.txt
${GEN} -width=160 -height=20  -ghosts=8 -powerpills=7 -maker=digger > depot/maze/rect-160x20.txt
${GEN} -width=20  -height=40  -ghosts=5 -powerpills=3 -maker=digger > depot/maze/rect-20x40.txt
${GEN} -width=20  -height=80  -ghosts=6 -powerpills=6 -maker=digger > depot/maze/rect-20x80.txt
${GEN} -width=20  -height=160 -ghosts=8 -powerpills=7 -maker=digger > depot/maze/rect-20x160.txt

${GEN} -size=15  -ghosts=2  -powerpills=5  -maker=grid2 -grid2_density=0.2 > depot/maze/grid2-0.2-15.txt
${GEN} -size=33  -ghosts=5  -powerpills=6  -maker=grid2 -grid2_density=0.2 > depot/maze/grid2-0.2-33.txt
${GEN} -size=55  -ghosts=6  -powerpills=7  -maker=grid2 -grid2_density=0.2 > depot/maze/grid2-0.2-55.txt
${GEN} -size=77  -ghosts=8  -powerpills=7  -maker=grid2 -grid2_density=0.2 > depot/maze/grid2-0.2-77.txt
${GEN} -size=99  -ghosts=10 -powerpills=8  -maker=grid2 -grid2_density=0.2 > depot/maze/grid2-0.2-99.txt
${GEN} -size=111 -ghosts=12 -powerpills=9  -maker=grid2 -grid2_density=0.2 > depot/maze/grid2-0.2-111.txt
${GEN} -size=155 -ghosts=30 -powerpills=9  -maker=grid2 -grid2_density=0.2 > depot/maze/grid2-0.2-155.txt
${GEN} -size=255 -ghosts=30 -powerpills=10 -maker=grid2 -grid2_density=0.2 > depot/maze/grid2-0.2-255.txt
${GEN} -size=15  -ghosts=2  -powerpills=5  -maker=grid2 -grid2_density=0.2 > depot/maze/grid2-0.5-15.txt
${GEN} -size=33  -ghosts=5  -powerpills=6  -maker=grid2 -grid2_density=0.2 > depot/maze/grid2-0.5-33.txt
${GEN} -size=55  -ghosts=6  -powerpills=7  -maker=grid2 -grid2_density=0.2 > depot/maze/grid2-0.5-55.txt
${GEN} -size=77  -ghosts=8  -powerpills=7  -maker=grid2 -grid2_density=0.2 > depot/maze/grid2-0.5-77.txt
${GEN} -size=99  -ghosts=10 -powerpills=8  -maker=grid2 -grid2_density=0.2 > depot/maze/grid2-0.5-99.txt
${GEN} -size=111 -ghosts=12 -powerpills=9  -maker=grid2 -grid2_density=0.2 > depot/maze/grid2-0.5-111.txt
${GEN} -size=155 -ghosts=30 -powerpills=9  -maker=grid2 -grid2_density=0.2 > depot/maze/grid2-0.5-155.txt
${GEN} -size=255 -ghosts=30 -powerpills=10 -maker=grid2 -grid2_density=0.2 > depot/maze/grid2-0.5-255.txt
${GEN} -size=15  -ghosts=2  -powerpills=5  -maker=grid2 -grid2_density=0.8 > depot/maze/grid2-0.8-15.txt
${GEN} -size=33  -ghosts=5  -powerpills=6  -maker=grid2 -grid2_density=0.8 > depot/maze/grid2-0.8-33.txt
${GEN} -size=55  -ghosts=6  -powerpills=7  -maker=grid2 -grid2_density=0.8 > depot/maze/grid2-0.8-55.txt
${GEN} -size=77  -ghosts=8  -powerpills=7  -maker=grid2 -grid2_density=0.8 > depot/maze/grid2-0.8-77.txt
${GEN} -size=99  -ghosts=10 -powerpills=8  -maker=grid2 -grid2_density=0.8 > depot/maze/grid2-0.8-99.txt
${GEN} -size=111 -ghosts=12 -powerpills=9  -maker=grid2 -grid2_density=0.8 > depot/maze/grid2-0.8-111.txt
${GEN} -size=155 -ghosts=30 -powerpills=9  -maker=grid2 -grid2_density=0.8 > depot/maze/grid2-0.8-155.txt
${GEN} -size=255 -ghosts=30 -powerpills=10 -maker=grid2 -grid2_density=0.8 > depot/maze/grid2-0.8-255.txt

if [ -d /dropbox ]; then
  cp -f depot/maze/*.txt /dropbox/maze/
fi
