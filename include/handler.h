#ifndef HANDLER_H
#define HANDLER_H

#include <stdio.h>
#include "terminal.h"
#include "log.h"
#include "global.h"

//각 명령마다 실행할 핸들러를 모아둠

//--------CLI모드 핸들러 구현부---------
void handler_cmd_mode(CMDFrame** frame);
void handler_running_mode();

//--------일반 명령 핸들러 구현부---------
void handler_cmd_prt(CMDFrame* frame);
void handler_cmd_save(CMDFrame* frame);
void handler_cmd_filter(CMDFrame* frame);
void handler_cmd_unfilter(CMDFrame* frame);
void handler_cmd_mask(CMDFrame* frame);
void handler_cmd_unmask(CMDFrame* frame);

#endif