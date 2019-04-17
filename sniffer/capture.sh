#!/bin/bash
#read -p "Train size: " trainSize
#read -p "Amount of trains: " amount

if [[ $# -ne 4 ]]; then
    echo "$0 <train size> <amount> <interval> <test name>"
	exit 1
fi

ip="10.42.0.54"

trainSize=$1
amount=$2
interval=$3
currentTest=$4
total=$(($trainSize * $amount))
currentDate=`date '+%Y-%m-%d-%H-%M'`
fileName="tests/${currentTest}/${interval}/${currentDate}_${trainSize}_${amount}.pcapng"
interface=$(./get_interface.sh)

mkdir -p tests/$currentTest/$interval
touch $fileName
chmod 666 $fileName
sudo tshark -i $interface -f "net $ip and udp port 5020" -w $fileName -F pcapng -c $total

# Uncomment this if you want to auto-upload your test
#scp $fileName USER@IP:~/tests/$currentTest/$interval
