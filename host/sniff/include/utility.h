#ifndef UTLILTY_H
#define UTLILTY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "global.h"

//CHAR -> 16진수 변환
#define HEX_TO_NUM(c) ((c) >= 'a' ? (c) - 'a' + 10 : \
                    (c) >= 'A' ? (c) - 'A' + 10 : \
                    (c) - '0')
                    

//현재 날짜 출력
void get_current_day(char* buf);
void get_current_time(char* buf);

void ringbuf_init(RingBuffer** buf);
int ringbuf_isempty(RingBuffer* buf);
int ringbuf_isfull(RingBuffer* buf);
void ringbuf_register_data(RingBuffer* buf, CANFrame* frame);
void ringbuf_get_data(RingBuffer* buf, CANFrame* frame);

#endif