

I/O pinout control
===================

1  cd /sys/class/gpio
2  echo 49 > export
3  cd gpio49
4  cat direction
5  echo out > direction
6  echo 1 > value
7  echo 0 > value
8  echo 49 > unexport


current pins configuration
-----------------------------------

cd /sys/kernel/debug/pinctrl/
ls
cd 44e10800.pinmux/
ls
more pins
cat pinmux‐pins


----------------------------------------------

device tree overlay DTO    >>> see anice presentation: https://www.youtube.com/watch?v=TfDE1s6EaG0
----------------------------------

               [http://embedded-basics.blogspot.ro/2014/10/enabling-spi0-on-beaglebone-black.html]

nano BB-SPI0-01-00A0.dts  
dtc -O dtb -o BB-SPI0-01-00A0.dtbo -b 0 -@ BB-SPI0-01-00A0.dts
cp BB-SPI0-01-00A0.dtbo /lib/firmware/ 


export SLOTS=/sys/devices/bone_capemgr.9/slots
export PINS=/sys/kernel/debug/pinctrl/44e10800.pinmux/pins

cat $SLOTS

echo "BB-SPI0-01" > $SLOTS

----->>> currently  echo "BB-SPIDEV1" > $SLOTS
                    echo "BB-SPIDEV0" > $SLOTS

        Now go into the file name uEnv.txt.  The appears in the external device BEAGLEBONE if you have the 
        board plugged into a computer.  If using an external monitor go to Computer click the BEAGLEBONE 
        device and open uEnv.txt with gedit.

        Delete any lines that may appear in uEnv.txt and add the following and save.  This change will tell 
        the board to apply the SPI0 Device Tree Overlay we created on startup.

----------------------------------------------------------------------------

uEnv.txt:

optargs=quiet drm.debug=7 capemgr.enable_partno=BB-SPIDEV0


