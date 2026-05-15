#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_LINE_CNT 256            // 명령어 결과 담을 변수 최대 크기

//전원 관련 명령 시그널
typedef uint8_t PowerCmd;
#define CMD_ACC_ON 0x01
#define CMD_ACC_OFF 0x02
#define CMD_SHUTDOWN 0x03
#define CMD_SLEEP 0x04
#define CMD_HIBERNATE 0x05

//시리얼 통신 응답 시그널
typedef uint8_t AckCmd;
#define ACK_OK 0xAA
#define ACK_FAIL 0xFF

extern int process_exit_code;

const char* send_linux_command(char* cmd);

char* getpowercmdtostr(uint8_t sig);
char* getpowercmdtolinux(uint8_t sig);


#endif