#ifndef SNIFFING_H
#define SNIFFING_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

#include "global.h"

#define SERIAL_PORT_PATH "/dev/cu.usbmodem2056369243431"

void all_init();
void data_save(CANFrame* frame);
void data_recv();
void all_disconnect_serialport();

#endif