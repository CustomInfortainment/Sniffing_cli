#ifndef POWER_H
#define POWER_H

#include <stdio.h>
#include <stdint.h>

typedef uint8_t PowerCmd;
#define CMD_ACC_ON 0x01
#define CMD_ACC_OF 0x02
#define CMD_SHUTDOWN 0x03
#define CMD_SLEEP 0x04
#define CMD_HIBERNATE 0x05

#endif