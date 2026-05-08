#include "GPIOWorker.h"

bool GPIOWorker::GetCarPowerState()
{
    if(digitalRead(PIN_ACC) == HIGH)
    {
        Serial.println("차량으로부터 ACC 전원 받음");
    }
}

bool GPIOWorker::GetSBCPowerState()
{
    uint8_t S0 = digitalRead(PIN_S0);
    uint8_t S3 = digitalRead(PIN_S3);
    uint8_t S4 = digitalRead(PIN_S4);

    if(S0 == HIGH)
    {
        Serial.println("SBC 전원 상태 : S0");
        return true;
    }
    return false;
}

void GPIOWorker::OnUpdate()
{

}