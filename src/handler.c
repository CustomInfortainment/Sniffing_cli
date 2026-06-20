#include "handler.h"

//명령 입력 받음
void handler_cmd_mode(CMDFrame** frame)
{
    printf("sniffer > ");

    *frame = (CMDFrame*)malloc(sizeof(CMDFrame));
    char buf[MAX_CMD_LINE];

    if(*frame == NULL)
	{
		prt_log_console("메모리 미할당 오류");
		return;
	}
	if(fgets(buf, MAX_CMD_LINE, stdin) == NULL)
	{
		return;
	}

	//명령, 인자
	char* cmd1 = strtok(buf, " \n");
	char* cmd2 = strtok(NULL, " \n");

    if(cmd1 != NULL)
    {
        strcpy((*frame)->cmd, cmd1);
        if(cmd2 != NULL)
        {
            char* hex_data = cmd2;

            //0x, 0X 부분은 제외
            if(cmd2[0] == '0' && (cmd2[1] == 'x' || cmd2[1] == 'X'))
            {
                hex_data += 2;
            }

            (*frame)->id = 
                HEX_TO_NUM(hex_data[0]) << 8 |
                HEX_TO_NUM(hex_data[1]) << 4 |
                HEX_TO_NUM(hex_data[2]);
        }
        prt_log_console("러닝 상태로 전환");
        set_cli_mode(RUNNING);
    }
    else
    {
        free(*frame);
        return;
    }
}

void handler_running_mode()
{
    char cmd;
	int n = read(STDIN_FILENO, &cmd, 1);

	//커맨드 모드로 전환 및 따옴표 입력 받으면 전환
	if(n > 0 && cmd == ':')
		set_cli_mode(CMD);
}