#!/bin/bash

make

GEN=./build/flame-binary/depot/maze/gen

for seed in {0..9}; do
  ${GEN} --maker=world-classic --ghosts=2 --powerpills=2 --seed=$seed \
      > depot/maze/world-classic-few-ghosts-$seed.txt
done
for seed in {0..9}; do
  ${GEN} --maker=world-classic --ghosts=4 --powerpills=4 --seed=$seed \
      > depot/maze/world-classic-$seed.txt
done
for seed in {0..9}; do
  ${GEN} --maker=world-classic --ghosts=6 --powerpills=4 --seed=$seed \
      > depot/maze/world-classic-many-ghosts-$seed.txt
done

for seed in {0..9}; do
  ${GEN} --maker=new-world --ghosts=8 --powerpills=12 --seed=$seed \
      > depot/maze/new-world-$seed.txt
done
