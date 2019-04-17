# Sniffer and sender scripts

## Sniffer

To properly use the sniffer script, you must have Linux

### What it does

The sniffer scripts will change your wifi card into monitoring mode and look for certain packets. It will then save it to a `.pcapng` file.

### Requirements
0. A decent WiFi card (or something that matches the one you're sniffing)
   1. We tested with a 54 Mbps card sniffing a 144 Mbps link and it captured 200 of the 2000 packets sent
   2. Not all wifi cards are created equal, our tests show that different cards can have different results
1. `sudo apt install aircrack-ng`: for the monitoring
2. `sudo apt install tshark`: to save to a `.pcapng` file

### Setup
0. MAKE SURE THE WIFI YOU ARE SNIFFING IS UNENCRYPTED
1. Run the `sniffer/start_mon.sh` script
2. It would echo something like `wlan0mon` at the end
   1. It might not be exactly `wlan0mon`, but it should end with `mon`
3. Inside `sniffer/capture.sh`, change the `$ip` variable to the IP of the client
   
If the wireless interface is the wrong one or you need to specify it, change the `sniffer/get-interface.sh` file to echo the correct interface

You can also change which channel you want in the `sniffer/start_mon.sh`, by default it is at channel 1 (2.412 Ghz)

### Running
1. Run the `sniffer/run.sh` script with the correct settings for your test
   1. `sniffer/run.sh 1100 "readme-test"`
   2. The 1100 is in usecs (1.1 millis)
   3. This is will listen for 2000 packets, 3000 packets up to 15000 packets. Each time it will create a new file

If you want more control over how many packets it saves per tests, remove the `-c $total` part of the tshark command. Once your round of testing is done you can simply `control+C` to pass to the next test

### Running a single test
1. Run the `sniffer/capture.sh` with the settings you need
   1. `sniffer/capture.sh 2 100 1100 "readme-test"`
   2. This will sniff for a 100 packet train size of 2 (200 packets total)

### Extra
There is an extra line in `sniffer/capture.sh` to uncomment if you want to upload your file to an SSH server. This is useful to backup/process your results as you do it.

## Sender

### What it does

This program will send udp packet trains at set intervals. An example input of `./program 10.42.0.1 5020 1100 2 100` will send 100 packet trains of size 2 at each 1100 usecs to 10.42.0.1:5020

More info can be found in `main.c`

### Setup
1. `gcc -std=c11 main.c`: compile the program
2. An unencrypted wifi connection so the traffic can get sniffed

### Running
1. Modify `sender/run.sh` to match your network settings
2. Run the `sender/run.sh`

### Running on a phone
Download [CppDroid](https://play.google.com/store/apps/details?id=name.antonsmirnov.android.cppdroid&hl=en_CA) to your phone and put the `main.c` on it. If you getting a compile error for C, try renaming the file to `main.cpp`, this has fixed the issue in the past for me.

### Authors

* **Peter McCormick** - *Initial work*

### License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
