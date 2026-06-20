#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

#include "log.h"
#include "global.h"
#include "utility.h"
#include "handler.h"

//최대 명령 길이는 256
#define MAX_CMD_LINE 256

enum CLI_MODE
{
    CMD,
    RUNNING
};

//CLI 모드 전환
void set_cli_mode(enum CLI_MODE mode);
void run_cli_mode();

//논블로킹 입력 구현
void set_keypress();
void restore_keypress();

//터미널 실행 함수
void run_terminal();

#endif
