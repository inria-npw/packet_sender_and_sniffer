echo /sys/class/net/*/wireless | awk -F'/' '{ print $5 }'
