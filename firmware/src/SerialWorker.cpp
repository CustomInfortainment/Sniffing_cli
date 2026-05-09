#include "SerialWorker.h"

void SerialWorker::SendCommand(char* cmd)
{
    Event e = Event::NONE;
    uint8_t send = 0;

    if(strcmp(cmd, sendCommand[0].commandName) == 0)                               //Shutdown
    {
        send = Serial.write(sendCommand[0].linuxCommand);
        e = Event::SHUTDOWN_SEND;
    }
    else if(strcmp(cmd, sendCommand[1].commandName) == 0)                         //Reboot
    {
        send = Serial.write(sendCommand[1].linuxCommand);
        e = Event::REBOOT_SEND;
    }
    else if(strcmp(cmd, sendCommand[2].commandName) == 0)                         //Sleep
    {
        send = Serial.write(sendCommand[2].linuxCommand);
        e = Event::SLEEPING_SEND;
    }
    else if(strcmp(cmd, sendCommand[3].commandName) == 0)                         //Hivernate
    {
        send = Serial.write(sendCommand[3].linuxCommand);
        e = Event::HIVERNATE_SEND;
    }

    // if(send != 0)   //send가 제대로 이루어 졌을 때만 이벤트 큐에 등록함
    //     RegisterPowerEvent(e); 
}

void SerialWorker::RecvCommand()
{
    Event e = Event::NONE;
    int32_t recvsig = 0;

    if(Serial.available() >= 1)
    {
        recvsig = Serial.read();
        if(recvsig != -1)
        {
            e = static_cast<Event>(recvsig);
            // RegisterPowerEvent(e);
        }
    }
}

bool SerialWorker::CheckHeartBeat()
{
    uint8_t send = Serial.write(static_cast<uint8_t>(HeartBeat::SENDING));               //시리얼 연결 유지 시그널을 지속적으로 보낸다.
    if(send != 0)
    {
        int data = Serial.read();

        if(data != -1)
        {
            HeartBeat recvsig = static_cast<HeartBeat>(data);

            if(recvsig == HeartBeat::RECVING)
            {
                return true;
            }
        }
    }
    return false;
}

void SerialWorker::OnUpdate()
{
    // for(;;)
    // {
    //     bool handshake = CheckHeartBeat();  //시리얼 연결 유효성 지속적으로 확인
        
    //     if(handshake) //연결 되어 있는 상태                                                                       
    //     {
            
    //     }
    //     else
    //     {

    //     }
    //     delay(100);
    // }
    bool handshake = CheckHeartBeat();  //시리얼 연결 유효성 지속적으로 확인
}