#ifndef SERIAL_H
#define SERIAL_H

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

//연결될 MCP VID, PID 정의
#define ESP32_VID 0x10c4
#define ESP32_PID 0xea60
#define LEONARDO_VID 0x3343
#define LEONARDO_PID 0x803a

#define VID_PATH "/sys/bus/usb/devices/*/idVendor"
#define PID_PATH "/sys/bus/usb/devices/*/idProduct"
#define USB_PATH "/sys/bus/usb/devices/"

void ping();

char* getserialport(unsigned int pid, unsigned int vid);

void senddata();
void recvdata();

#endif