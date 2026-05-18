#include "file.h"
#include "utility.h"

IDFile idfiles[MAX_IDS];

int ids_index = 0;

int check_dir(char* name)
{
    struct stat st;
    char buf[256];
    snprintf(buf, sizeof(buf), "%s/%s", SAVE_PATH, name);
    return (stat(buf, &st) == 0 && S_ISDIR(st.st_mode));
}

FILE* check_file(int id)
{
    for(int i = 0; i < MAX_IDS; i++)
    {
        if(idfiles[i].id == id)
        {
            return idfiles[i].fp;
        }
    }
    return NULL;
}

FILE* get_file(int id)
{
    int isdir = 0;
    FILE* isfile = NULL;

    char buf[256];
    const char* dirname = get_current_day();

    //저장할 디렉터리 및 파일이 있는지 확인
    isdir = check_dir(dirname);
    isfile = check_file(id);

    //디렉터리가 없다면 새로 만듦
    if(isdir == 0)
    {
        snprintf(buf, sizeof(buf), "mkdir -p %s/%s", SAVE_PATH, dirname);
        system(buf);
    }

    //파일이 없다면 새로 생성
    if(isfile == NULL && ids_index < MAX_IDS)
    {
        IDFile* entry = &idfiles[ids_index++];

        entry->id = id;
        memset(buf, '\0', sizeof(buf));
        snprintf(buf, sizeof(buf), "%s/%s/CAN_%3X.txt", SAVE_PATH, dirname, id);
        snprintf(entry->filename, sizeof(entry->filename), "CAN_%3X.txt", id);
        entry->fp = fopen(buf, "a");

        return entry->fp;
    }
    else 
    {
        return isfile;
    }
    return NULL;
}

void all_exit_files()
{
    for(int i = 0; i < ids_index; i++)
    {
        if(idfiles[i].fp != NULL) fclose(idfiles[i].fp);
    }
}