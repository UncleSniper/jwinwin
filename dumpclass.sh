#!/bin/bash

if [ $# != 1 ]; then
	echo "Usage: $(basename -- "${BASH_SOURCE-$0}") <class-basename>" >&2
	exit 1
fi

javap -cp bin -v org.unclesniper.winwin."$1"
