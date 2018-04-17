
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <fcntl.h>
#include <time.h>
#include <sys/ioctl.h>
#include <linux/ioctl.h>
#include <sys/stat.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#include <iostream>
#include <sstream>
#include "../library/bus/SPIDevice.h"
#include "../library/display/Max7219.h"

#include <sys/time.h>

using namespace std;
using namespace exploringBB;





static const char *device = "/dev/spidev1.1";
static uint32_t mode;
static uint8_t bits = 8;
static char *input_file;
static char *output_file;
static uint32_t speed = 500000;
static uint16_t delay;
static int verbose;
static int transfer_size;
static int iterations;
static int interval = 5; /* interval in seconds for showing transfer rate */


int main()
{

        SPIDevice *busDevice = new SPIDevice(1,0); //Using second SPI bus (both loaded)

        /* init Display ... */
        Max7219_Init(busDevice);

        /* lights on all LED's */
        Max7219_Set_to_Display_Test();

        return 0;

}
