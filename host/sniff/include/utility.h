#ifndef UTLILTY_H
#define UTLILTY_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RING_BUF_SIZE 40
#define FRAME_SIZE 40

//CHAR -> 16진수 변환
#define HEX_TO_NUM(c) ((c) >= 'a' ? (c) - 'a' + 10 : \
                    (c) >= 'A' ? (c) - 'A' + 10 : \
                    (c) - '0')
                    

//현재 날짜 출력
void get_current_day(char* buf);
void get_current_time(char* buf);

//링 버퍼 구현
typedef struct
{
    char buf[RING_BUF_SIZE][FRAME_SIZE];
    unsigned int head;
    unsigned int tail;
} RingBuffer;
void ringbuf_init(RingBuffer* buf);
int ringbuf_isempty(RingBuffer* buf);
int ringbuf_isfull(RingBuffer* buf);
void ringbuf_register_data(RingBuffer* buf, char* frame);
void ringbuf_get_data(RingBuffer* buf, char* outframe);

#endif