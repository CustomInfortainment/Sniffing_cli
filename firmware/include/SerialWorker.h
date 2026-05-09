#pragma once
#include "BootStrap.h"
#include "CThread.h"
#include "Event.h"
#include "pininfo.h"

class SerialWorker:CThread
{
    private:
    public:
        void SendCommand(char* cmd);
        void RecvCommand();
        bool CheckHeartBeat();                          //시리얼 통신이 유효한지 지속적으로 확인                
        void OnUpdate() override;   
};  