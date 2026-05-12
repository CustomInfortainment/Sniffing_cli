#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_CNT 256            // 명령어 결과 담을 변수 최대 크기

const char* send_linux_command(char* cmd);

#endif