#ifndef SNIFFING_H
#define SNIFFING_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

#define SERIAL_PORT_PATH "/dev/cu.usbmodem2056369243431"

void do_sniffing();
void all_disconnect_serialport();

#endif