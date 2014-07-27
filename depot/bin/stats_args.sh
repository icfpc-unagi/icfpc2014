#!/bin/bash

source gbash.sh || exit 1

gbash::init_google "$@"
set -- "${GBASH_ARGV[@]}"
set -e -u

PRESET_GHOSTS=(
	'fickle'
	'chokudai'
	'chokudai,sakichokudai'
	'fichokudai'
)
PRESET_MAZE=(
	'world-classic'
	'world-1'
	'world-2'
	'arena-20'
	'arena-50'
	'arena-70'
	'test-32'
	'test-50'
	'test-70'
	'test2-32'
	'test2-50'
	'test2-70'
	'rect-20x40'
	'rect-80x20'
)
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
