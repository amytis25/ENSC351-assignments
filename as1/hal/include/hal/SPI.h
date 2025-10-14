#ifndef SPI_H
#define SPI_H

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#define SPI_DEV_PATH "/dev/spidev0.0"

typedef struct  {
    int x; // normalized x value (-100 to 100)
    int y; // normalized y value (-100 to 100)
} joystick_values;

static int read_ch(int fd, int ch, uint32_t speed_hz);

joystick_values Read_ADC_Values(void);

#endif