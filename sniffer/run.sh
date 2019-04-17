#! /bin/bash

if [[ $# -ne 2 ]]; then
    echo "$0 <interval> <test name>"
	exit 1
fi

for i in {2..15}
do
	echo ""
	echo "Starting $i capture..."
	echo ""
	./capture.sh $i 1000 $1 $2
done
