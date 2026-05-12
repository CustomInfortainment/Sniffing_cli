#ifndef SERIAL_H
#define SERIAL_H

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

#define ESP32_VID 0x10c4
#define ESP32_PID 0xea60

#define VID_PATH "/sys/bus/usb/devices/*/idVendor"
#define PID_PATH "/sys/bus/usb/devices/*/idProduct"
#define USB_PATH "/sys/bus/usb/devices/"

void ping();

char* getesp32port();

void senddata();
void recvdata();

#endif