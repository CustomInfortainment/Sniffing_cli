#include "terminal.h"

enum CLI_MODE currentmode;

struct termios old_settings;
struct termios new_settings;

void set_cli_mode(enum CLI_MODE mode)
{
	currentmode = mode;
}

void run_cli_mode(enum CLI_MODE mode)
{
	switch(currentmode)
	{
		case NORMAL:
			handler_normal_mode();
			break;
		case CMD:
			handler_cmd_mode();
			break;
		default:
			break;
	}
}

void prt_prompt()
{
	printf("%s", PROMPT);
}

//논블로킹 입력 구현
void set_keypress()
{
	tcgetattr(STDIN_FILENO, &old_settings);
	tcgetattr(STDIN_FILENO, &new_settings);

	new_settings.c_lflag &= ~(ICANON | ECHO);
	new_settings.c_cc[VMIN] = 0;
	new_settings.c_cc[VTIME] = 0;

	tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);

	//커맨드 모드로 전환
	set_cli_mode(CMD);
}

//논블로킹 -> 기존 터미널 설정으로 복귀
void restore_keypress()
{
	tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);

	//노말 모드로 전환
	set_cli_mode(NORMAL);
}

//사용자로부터 명령어와 canid를 받는다, CMD모드에서만 작동
void get_cmd(char *buf, CMDFrame* frame)
{
	if(frame == NULL)
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

	strcpy(frame->cmd, cmd1);

	if(cmd2 != NULL)
	{
		char* hex_data = cmd2;

		//0x, 0X 부분은 제외
		if(cmd2[0] == '0' && (cmd2[1] == 'x' || cmd2[1] == 'X'))
		{
			hex_data += 2;
		}

		frame->id = 
			HEX_TO_NUM(hex_data[0]) << 8 |
			HEX_TO_NUM(hex_data[1]) << 4 |
			HEX_TO_NUM(hex_data[2]);
	}
}

void check_cmd()
{
    char buf[MAX_CMD_LINE];

    CMDFrame* cmdFrame = (CMDFrame*)malloc(sizeof(CMDFrame));

	if(cmdFrame == NULL)
	{
		prt_log_console("메모리 미할당 오류");
		return;
	}

	//커맨드 모드일 때.
    while(currentmode == CMD)
    {
		//프레임 값 할당
        get_cmd(buf, &cmdFrame);

		if(strcmp(cmdFrame->cmd, CMD_PRT) == 0)
		{
		}
		else if(strcmp(cmdFrame->cmd, CMD_SAVE) == 0)
		{
		}
		else if(strcmp(cmdFrame->cmd, CMD_FILTER) == 0)
		{
		}
		else if(strcmp(cmdFrame->cmd, CMD_UNFILTER) == 0)
		{
		}
		else if(strcmp(cmdFrame->cmd, CMD_MASK) == 0)
		{
		}
		else if(strcmp(cmdFrame->cmd, CMD_UNMASK) == 0)
		{
		}
		else
		{
			prt_log_console("명령이 존재하지 않습니다.");
			continue;
		}
    }
}

void run_terminal()
{
	set_cli_mode(NORMAL);
	check_cmd();
}
