#include "parser.h"
#include "handler.h"
#include "canid.h"
#include "utility.h"

int get_rpm_data(int id, char* data)
{
    if(id != ID_ENGINE_RPM)
    {
        return -1;
    }

    int rpm_hex1 = (HEX_TO_NUM(data[2]) << 4) | HEX_TO_NUM(data[3]);
    int rpm_hex2 = (HEX_TO_NUM(data[4]) << 4) | HEX_TO_NUM(data[5]);

    int rpm_result = (rpm_hex1 << 8 | rpm_hex2);

    return rpm_result / 4;
}

int get_coolent_data(int id, char* data)
{
    if(id != ID_COOLENT_TEMP)
    {
        return -1;
    }

    int coolent_hex = (HEX_TO_NUM(data[2]) << 4) | HEX_TO_NUM(data[3]);

    return coolent_hex - 40;
}