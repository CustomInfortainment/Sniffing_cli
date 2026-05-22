#ifndef HANDLER_H
#define HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define MAX_LOG_LENGTH 256

void can_id_str(int id, char* buf);
void can_dlc_str(int dlc, char* buf);

void prt_log_console(char* log);
void prt_log_console_handler(int id, int dlc, char* data);
void precess_exit_handler(int sig);

#endif