#ifndef SERIAL_H
#define SERIAL_H
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>

//연결될 MCP VID, PID 정의
#define ESP32_VID 0x10c4
#define ESP32_PID 0xea60

#define LEONARDO_VID 0x3343
#define LEONARDO_PID 0x803a

#define CANABLE2_VID 0x16d0
#define CANABLE2_PID 0x117e

//리눅스 상의 USB 정보 경로
#define VID_PATH "/sys/bus/usb/devices/*/idVendor"
#define PID_PATH "/sys/bus/usb/devices/*/idProduct"
#define USB_PATH "/sys/bus/usb/devices/"

//시리얼 포트 관련 전역변수
extern char* leonardoPortName;
extern int leonardoPortFd;
extern struct termios old_ter;
extern struct termios new_ter;

//시리얼 포트 상태
typedef enum
{
    INIT_OK = 0,
    SERIAL_PORT_OPEN_FAILED = -1,
    SERIAL_PORT_LOAD_FAILED = -2,
    TERMINULL_LOAD_FAILED = -3,
    TERMINULL_SAVE_FAILED = -4,
} SerialPortState;

extern SerialPortState serialportstate;

//모듈
char* getserialport();
int getserialportstate();

//기능
int startserial();
int senddata(uint8_t data);
uint8_t recvdata();
int endserial();

#endif