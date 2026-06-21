#ifndef CANTYPE_H
#define CANTYPE_H

#include <fcntl.h>
#include <stdio.h>

#include "log.h"

#define RING_BUF_SIZE 40

//명령어 모음
#define CMD_PRT "print"
#define CMD_SAVE "save"
#define CMD_FILTER "filter"
#define CMD_UNFILTER "unfilter"
#define CMD_MASK "mask"
#define CMD_UNMASK "unmask"

//파일 저장에 쓰이는 구조체
typedef struct
{
    int id;
    FILE* fp;
    char filename[256];
} IDFile;

//CAN프레임 구조체
typedef struct
{
    int id;
    int dlc;
    char raw_data[256];
} CANFrame;

//링버퍼 구조체
typedef struct
{
    CANFrame* buf[RING_BUF_SIZE];
    unsigned int head;
    unsigned int tail;
} RingBuffer;

//CLI툴 명령 구조체
typedef struct
{
    char cmd[256];
    int id; 
} CMDFrame;

//리스트 노드 구조체, Mask, Filter 둘다 같은 거 사용
typedef struct
{
    int id;
    struct ListNode *prev;
    struct ListNode *next;
} ListNode;

#endif
