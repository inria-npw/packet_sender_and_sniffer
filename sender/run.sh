#! /bin/sh
for i in `seq 2 15`
do
	./a.out 10.42.0.1 5020 $1 $i 1000
	read -p "Enter to continue..." test
done
