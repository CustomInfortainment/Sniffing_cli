#pragma once

#include "pininfo.h"
#include "CThread.h"

class GPIOWorker : CThread
{
    public :
        bool GetCarPowerState();
        bool GetSBCPowerState();
        void OnUpdate() override;
};