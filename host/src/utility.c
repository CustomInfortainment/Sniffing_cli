#include "utility.h"
#include "log.h"

void* resize_memory(void* ptr, size_t cursize)
{
    void* save = realloc(ptr, cursize * 2);

    if(save == NULL)
    {
        prt_logconsole("메모리 할당에 실패했습니다.");
        return NULL;
    }
    return save;
}