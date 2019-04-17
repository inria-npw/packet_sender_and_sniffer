interface=$(./get_interface.sh)
echo $interface
sudo airmon-ng start $interface
mon=$(./get_interface.sh)
echo $mon
sudo iwconfig $mon channel 1
