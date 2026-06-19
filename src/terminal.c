#include "terminal.h"

int input_from_user(char *buf1, char* buf2, CMDFrame* frame)
{
    if(fgets(buf1, MAX_CMD_LINE, stdin) == NULL)
    {
        prt_log_console("명령을 다시 입력해주세요.");
        return 0;
    }
    else
    {
        frame = (CMDFrame*)malloc(sizeof(CMDFrame));
        if(frame == NULL)
        {
            prt_log_console("CMD 구조체 메모리 할당 실패");
            return 0;
        }
        else
        {
            
        }
    }
    return 1;
}

void get_cmd()
{
    char buf1[MAX_CMD_LINE];
    char buf2[MAX_CMD_LINE];

    CMDFrame* cmdFrame;

    while(1)
    {
        int input = input_from_user(buf1, buf2, &cmdFrame);

        if(input == 0)
        {
            continue;
        }
        else
        {
            if(strcmp(buf1, CMD_PRT) == 0)
            {
                prt_log_console("명령을 출력 하시겠나요?(y/n)");
            }
            else if(strcmp(buf1, CMD_FILTER) == 0)
            {

            }
            else if(strcmp(buf1, CMD_MASK) == 0)
            {

            }
            else if(strcmp(buf1, CMD_SAVE) == 0)
            {

            }
            else if(strcmp(buf1, CMD_UNFILTER) == 0)
            {

            }
            else if(strcmp(buf1, CMD_UNMASK) == 0)
            {

            }
            else
            {
                prt_log_console("해당 명령은 존재하지 않습니다.");
            }
        }
    }
}