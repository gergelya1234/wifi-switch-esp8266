# wifi-switch-esp8266

## Installation

Just set your wifi router IP address, SSID and password in the source code to be able to connect.

Check the MAC address of your ESP8266. You can do that on your router web interface by listing the active wifi connections. Maybe the MAC address is already printed on your PCB or on the chip case. 
Set a fix IP address for this MAC address in your router. Check DHCP settings for the related sections.
I case if you want to controll a RGB led strip set a connection with arduino RGB controller on HW serial port. For the arduino the source code is rgb_arduino.ino
The Arduino pins are the followings:

- PIN 5 = RED
- PIN 6 = GREEN
- PIN 3 = BLUE

You can change of course.


## Usage

Check your esp8266 connection state on your router or by reading the messages on the serial.
If everything seems to be fine, check with a browser by entering the IP address of the controller.
You should get the following message:

```html
Hello
ESP8266 webserver, commands: /on, /off, or /st
```

Try to switch the connected relay by entering the above mentioned commands in a browser.
You may also use the following native application on your mobile to manage the controller, or controllers in case you have many.
<a href='https://play.google.com/store/apps/details?id=co.gergely.iotnetswitcher'><img alt='Get it on Google Play' src='https://play.google.com/intl/en_us/badges/images/generic/en_badge_web_generic.png' width='260px'/></a>

## Usage examples:

I use the mentioned wifi switch for many devices, including:

- to control my lights
- to switch on / off my heating system
- to open / close my garage door

## Warnings

The program and controller communication is not encrypted, the https protocol is not implemented, and they are not controlled by any authentication method. Please make sure that your network is inaccessible from the internet, and the controller is still connected to your own DMZ network protected by your own wifi router.
 
