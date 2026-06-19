#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "log.h"
#include "global.h"

//최대 명령 길이는 256
#define MAX_CMD_LINE 256

int input_from_user(char *buf1, char* buf2, CMDFrame* frame);
void get_cmd();

#endif