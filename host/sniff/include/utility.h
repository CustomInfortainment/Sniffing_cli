#ifndef UTLILTY_H
#define UTLILTY_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RING_BUF_SIZE 40
#define FRAME_SIZE 40

void get_current_day(char* buf);

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