# iBUS JOYSTICK

This software allow you to use any FlySky iBUS receiver to use your FlySky transmitter as a USB gamepad to controls your FPV simulator.

# WHAT YOU NEED
## USB SERIAL ADAPTER
You need a USB serial adapter, can be used also an arduino, with the RST pin connected to GND.
## FlySky receiver
You need a FlySky receiver with iBUS, it is work only with iBUS, so no with SBUS, PPM, PWM, ecc...
Connect the iBUS pin to the pin of serial adapter that receive data, for example in arduino uno is the pin number 1

## Permission to accesso to /dev/uniput
Make sure that the current user can be write on `/dev/uinput`.

if you can't access to `/dev/uinput` can follow this step.
- Create a uinput groups
> sudo groupadd uinput
- Add your user to uinput group
> sudo gpasswd -a $USER uinput

Create new udev rule
- create a new file name: `/etc/udev/rules.d/99-input.rules`
- put this on the file just created
> SUBSYSTEM=="misc", KERNEL=="uinput", MODE="0660", GROUP="uinput"

Run uinput kernel node at boot.
- create a new file name: `/etc/modules-load.d/uinput.conf`
- put this on the file created
> uinput
- Reboot your sytem.
- Check that uinput groups can access to uinput file, so run `ls -l /dev/uinput` , and you could get something like this.
> crw-rw---- 1 root uinput 10, 223 13 apr 10.23 /dev/uinput
Now, your user can access to /dev/uinput file.

# HOW TO COMPILE
To compile you need to run:
> make
# HOW TO RUN
> ./iBUS_js

Default parameters presume that serial adapter is /dev/ttyUSB0, to use another serial adapter, for example /dev/ttyUSB1 run:
> ./iBUS_js --input /dev/ttyUSB1



### Open your FPV simulator to play!

All was tested on arch linux, x6b receiver, an arduino uno as serial adapter and FreeRider simulator
