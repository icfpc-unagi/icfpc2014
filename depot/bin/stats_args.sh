#!/bin/bash

source gbash.sh || exit 1

DEFINE_string preset 'regular' ''

gbash::init_google "$@"
set -- "${GBASH_ARGV[@]}"
set -e -u


PRESET_GHOSTS=()
PRESET_MAZE=()
if [ "${FLAGS_preset}" == 'new-world' ]; then
	PRESET_GHOSTS+=(
		'fickle'
		'chokudai'
		'chokudai,sakichokudai'
		'iwi1,chokudai,sakichokudai,fickle'
		'iwi1'
		'iwi5'
		'iwi6'
		'iwi_escape1'
	)
	PRESET_MAZE+=(
		'new-world---0'
		'new-world---1'
		'new-world---2'
		'new-world---3'
		'new-world---4'
		'new-world---5'
		'new-world---6'
		'new-world---7'
		'new-world---8'
		'new-world---9'
	)
elif [ "${FLAGS_preset}" == 'new-world-patch' ]; then
	PRESET_GHOSTS+=(
		'iwi6'
	)
	PRESET_MAZE+=(
		'new-world---0'
		'new-world---1'
		'new-world---2'
		'new-world---3'
		'new-world---4'
		'new-world---5'
		'new-world---6'
		'new-world---7'
		'new-world---8'
		'new-world---9'
	)
elif [ "${FLAGS_preset}" == 'regular-set' ]; then
	PRESET_GHOSTS+=(
		'fickle'
		'iwi6'
		'iwi_escape1'
	)
	PRESET_MAZE+=(
		'test-32---0'
		'test-32---1'
		'test-32---2'
		'test-32---3'
		'test-32---4'
		'test-32---5'
		'test-32---6'
		'test-32---7'
		'test-32---8'
		'test-32---9'
		'grid-32---0'
		'grid-32---1'
		'grid-32---2'
		'grid-32---3'
		'grid-32---4'
		'grid-32---5'
		'grid-32---6'
		'grid-32---7'
		'grid-32---8'
		'grid-32---9'
	)
elif [ "${FLAGS_preset}" == 'grid2-set' ]; then
	PRESET_GHOSTS+=(
		'fickle'
		'iwi6'
		'iwi_escape1'
	)
	PRESET_MAZE+=(
		'grid2-0.2-33---0'
		'grid2-0.2-33---1'
		'grid2-0.2-33---2'
		'grid2-0.2-33---3'
		'grid2-0.2-33---4'
		'grid2-0.2-33---5'
		'grid2-0.2-33---6'
		'grid2-0.2-33---7'
		'grid2-0.2-33---8'
		'grid2-0.2-33---9'
		'grid2-0.8-33---0'
		'grid2-0.8-33---1'
		'grid2-0.8-33---2'
		'grid2-0.8-33---3'
		'grid2-0.8-33---4'
		'grid2-0.8-33---5'
		'grid2-0.8-33---6'
		'grid2-0.8-33---7'
		'grid2-0.8-33---8'
		'grid2-0.8-33---9'
	)
elif [ "${FLAGS_preset}" == 'iwi' ]; then
	PRESET_GHOSTS+=(
		'iwi_escape1'
	)
	PRESET_MAZE+=(
		'new-world---0'
		'new-world---1'
		'new-world---2'
		'new-world---3'
		'new-world---4'
		'new-world---5'
		'new-world---6'
		'new-world---7'
		'new-world---8'
		'new-world---9'
		'test-32---0'
		'test-32---1'
		'test-32---2'
		'test-32---3'
		'test-32---4'
		'test-32---5'
		'test-32---6'
		'test-32---7'
		'test-32---8'
		'test-32---9'
		'grid-32---0'
		'grid-32---1'
		'grid-32---2'
		'grid-32---3'
		'grid-32---4'
		'grid-32---5'
		'grid-32---6'
		'grid-32---7'
		'grid-32---8'
		'grid-32---9'
		'grid2-0.2-33---0'
		'grid2-0.2-33---1'
		'grid2-0.2-33---2'
		'grid2-0.2-33---3'
		'grid2-0.2-33---4'
		'grid2-0.2-33---5'
		'grid2-0.2-33---6'
		'grid2-0.2-33---7'
		'grid2-0.2-33---8'
		'grid2-0.2-33---9'
		'grid2-0.8-33---0'
		'grid2-0.8-33---1'
		'grid2-0.8-33---2'
		'grid2-0.8-33---3'
		'grid2-0.8-33---4'
		'grid2-0.8-33---5'
		'grid2-0.8-33---6'
		'grid2-0.8-33---7'
		'grid2-0.8-33---8'
		'grid2-0.8-33---9'
	)
elif [ "${FLAGS_preset}" == 'regular' ]; then
	PRESET_GHOSTS+=(
		'fickle'
		'chokudai'
		'chokudai,sakichokudai'
		'iwi1,chokudai,sakichokudai,fickle'
		'iwi1'
		'iwi5'
	)
	PRESET_MAZE+=(
		'world-classic'
		'world-1'
		'world-2'
		'ghostbusters'
		'proton-pack'
		'arena-20'
		'arena-32'
		'arena-50'
		'test-32'
		'test-50'
		'test2-32'
		'test2-50'
		'rect-20x40'
		'rect-40x20'
		'rect-80x20'
		'rect-20x80'
		'snake-20'
		'grid2-0.2-15'
		'grid2-0.2-33'
		'grid2-0.2-55'
		'grid2-0.5-15'
		'grid2-0.5-33'
		'grid2-0.5-55'
		'grid2-0.8-15'
		'grid2-0.8-33'
		'grid2-0.8-55'
	)
else
	echo "no such preset: ${FLAGS_preset}" >&2
	exit 1
fi

[ -z "$1" ] && echo "Usage: $0 <lman_name>" && exit 1
lman="$1"

Arg() {
	echo "-silent -noprint_state -print_stats -lman='$1' -ghosts='$2' -maze='/code/depot/maze/${3}.txt'"
}

for maze in ${PRESET_MAZE[@]}; do
	for ghosts in ${PRESET_GHOSTS[@]}; do
		Arg ${lman} ${ghosts} ${maze}
	done
done
