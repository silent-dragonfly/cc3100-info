# cc3100-info
This program prints information of cc3100  

## Used Modules
	
 Where used the `simple_link - CC3100 driver` to connect and control the cc3100Boost + EMUBoost to `windows 10`  environment.

 [Simple link cc3100 Diver](https://passive-scan.std12.os3.su/simplelink_api/html/index.html) were developed to allow adding Wi-Fi and Networking capabilities for embeded devices; To find a more detailed description of the whole set of drivers supported there is a section `Module Names` on the [Simple Link](https://passive-scan.std12.os3.su/simplelink_api/html/index.html) web page were will found among the following and other related cc3100 information:

* `Device` - Which controls the behavior of the hardware 
* `Wlan` - Controls the use of Wi-Fi on the cc3100, including `Connection Features` and `Advanced WLAN features`
* `Sockets` - This controls the standard options and capabilities for client and server programing
	
 The previous modules will be used to start gattering information from the cc3100 for more detailed module information and other not listed here can review the [Simple Link](https://passive-scan.std12.os3.su/simplelink_api/html/index.html) web site. 

## How to run cc3100-info

To review the previous steps requiered to run this sample please `Refer the Setting up a work station` on section [Run Test Project](https://github.com/silent-dragonfly/docs/blob/master/00-setup-workstation/set-up-workstation.md#run-test-project).

In the simple_link folder there sould be simple_link driver and libraries that can be retrieved from cc3100SDK, there are list of required files with their respective SHA-512 hashes.

## Gattering the cc3100 information
Modifying the sample code as requiered, taking as base the previously described modules it was possible to retrieve the infromation from the cc3100 board.

The specific modules used were:	
	
* `sl_DevGet` - Function to Get the basic device version information
* `sl_WlanGet` - This function was used to get Wi-Fi settings
* `sl_GetSocketOpt` - This function was used to get the physic parameters of socket opened in transmiter mode
	
Output exapmle:

```

Device information: 
CHIP 67108864
MAC 31.1.2.0.2
PHY 1.0.3.23
NWP 2.2.0.1
ROM 13107
HOST 1.0.1.11

SCAN_APRAMS:
G_Channels_mask: 8191
rssiThershold: -95 
Access Point TX power: 0 (0-15, as dB offset from max power (0 will set MAX power) )
Station TX power: 0 (0-15, as dB offset from max power (0 will set MAX power))
Country code: US

Print PHY socket options:
Rate 5
TX power 7 (0-15), 0 - MAX, 15 - MIN
Number of frames: 1
Channel: 7

```
