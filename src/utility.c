#include "utility.h"
#include "handler.h"
#include "sniffing.h"

//-------- 오늘 날짜 출력 ----------
void get_current_time(char* buf)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    snprintf(buf, sizeof(tm), "%d:%d;%d", 
    tm.tm_hour, 
    tm.tm_min, 
    tm.tm_sec);
}

//--------- 링버퍼 구현부 -----------

void ringbuf_init(RingBuffer** ringbuf)
{
    char log[256];

    snprintf(log, sizeof(log), "링버퍼 초기화 중...");
    prt_log_console(log);

    *ringbuf = malloc(sizeof(RingBuffer));

    if(*ringbuf != NULL)
    {
        (*ringbuf)->head = 0;
        (*ringbuf)->tail = 0;
        memset((*ringbuf)->buf, 0, sizeof((*ringbuf)->buf));

        snprintf(log, sizeof(log), "링버퍼 초기화 완료");
        prt_log_console(log);
    }
}

int ringbuf_isempty(RingBuffer* ringbuf)
{
    if(ringbuf->head == ringbuf->tail)
    {
        return 1;
    }
    return 0;
}

int ringbuf_isfull(RingBuffer* ringbuf)
{
    if(((ringbuf->head + 1) % RING_BUF_SIZE) == ringbuf->tail)
    {
        return 1;
    }
    return 0;
}

//버퍼에 저장
void ringbuf_register_data(RingBuffer* ringbuf, CANFrame* frame)
{
    if(ringbuf_isfull(ringbuf) == 1) //오버플로우 상태라면
    {
        return;
    }
    memcpy(&ringbuf->buf[ringbuf->head], frame, sizeof(CANFrame));
    ringbuf->head = (ringbuf->head + 1) % RING_BUF_SIZE;
}

//버퍼 -> outframe
void ringbuf_get_data(RingBuffer* ringbuf, CANFrame* outframe)
{
    if(ringbuf_isempty(ringbuf) == 1) //언더플로우 상태라면
    {
        return;
    }
    int idx = ringbuf->tail;
    ringbuf->tail = (ringbuf->tail + 1) % RING_BUF_SIZE;

    memcpy(outframe, &ringbuf->buf[idx], sizeof(CANFrame));
}

//연결리스트 구현부
void list_init(ListNode** head)
{
    *head = NULL;
}

void list_addnode(ListNode** head, ListNode** tail, int id)
{
    ListNode *node = (ListNode*)malloc(sizeof(ListNode));

    if(node == NULL)
        return;

    node->id = id;
    node->prev = NULL;
    node->next = NULL;
    
    if(*head == NULL)
    {
        *tail = node;
        *head = node;
    }
    else
    {
        node->prev = *tail;
        (*tail)->next = node;
        *tail = node;
    }
}

void list_deletenode(ListNode** head, ListNode** tail, int id)
{
    ListNode *curnode;
    curnode = *head;

    if((*head)->id == id)
    {
        free(*head);
    }

    while(curnode != NULL)
    {
        if(curnode->id == id)
        {
            if(curnode->next != NULL)
            {
                *tail = curnode->prev;
                curnode->prev = curnode->next;
            }
            free(curnode);
            return;
        }
        curnode = curnode->next;
    }
}

void list_clear(ListNode** head)
{
}