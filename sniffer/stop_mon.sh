interface=$(./get_interface.sh)
echo $interface
sudo airmon-ng stop $interface
mon=$(./get_interface.sh)
echo $mon