#include <stdio.h>
#include "file.h"
#include "sniffing.h"
#include "utility.h"

RingBuffer* ringbuf;

int main(void)
{
    ringbuf_init(&ringbuf);
    do_sniffing();
    return 0;
}