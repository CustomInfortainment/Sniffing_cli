#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include "global.h"

int get_rpm_data(int id, char* data); //차량 RPM 파싱
int get_coolent_data(int id, char* data); //차량 수온 파싱

#endif