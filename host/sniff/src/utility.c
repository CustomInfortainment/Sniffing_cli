#include "utility.h"
#include "handler.h"

void get_current_day(char* buf)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    snprintf(buf, sizeof(tm), "%d-%d-%d", 
    tm.tm_year+1900, 
    tm.tm_mon+1, 
    tm.tm_mday);
}

//--------- 링버퍼 구현부 -----------

void ringbuf_init(RingBuffer* ringbuf)
{
    char log[256];

    snprintf(log, sizeof(log), "버퍼 초기화 중...");
    prt_log_console(log);

    if(ringbuf != NULL)
    {
        ringbuf->head = 0;
        ringbuf->tail = 0;
        memset(ringbuf->buf, 0, sizeof(ringbuf->buf));

        snprintf(log, sizeof(log), "버퍼 초기화 완료");
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

void ringbuf_register_data(RingBuffer* ringbuf, char* frame)
{
    if(ringbuf_isfull(ringbuf) == 1) //오버플로우 상태라면
    {
        return;
    }
    snprintf(ringbuf->buf[ringbuf->head], FRAME_SIZE, "%s", frame);
    ringbuf->head = (ringbuf->head + 1) % RING_BUF_SIZE;
}

char* ringbuf_get_data(RingBuffer* ringbuf, char* outframe)
{
    if(ringbuf_isempty(ringbuf) == 1) //오버플로우 상태라면
    {
        return;
    }
    int idx = ringbuf->tail;
    ringbuf->tail = (ringbuf->tail + 1) % RING_BUF_SIZE;

    snprintf(outframe, FRAME_SIZE, "%s", ringbuf->buf[idx]);
}