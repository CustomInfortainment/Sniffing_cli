#ifndef CANTYPE_H
#define CANTYPE_H

#include <fcntl.h>
#include <stdio.h>

#define RING_BUF_SIZE 40

typedef struct
{
    int id;
    FILE* fp;
    char filename[256];
} IDFile;

typedef struct
{
    int id;
    int dlc;
    char raw_data[256];
} CANFrame;

//버퍼 구조체
typedef struct
{
    CANFrame* buf[RING_BUF_SIZE];
    unsigned int head;
    unsigned int tail;
} RingBuffer;

#endif