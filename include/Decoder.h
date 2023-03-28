#ifndef DECODER_H
#define DECODER_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "floatpointUtils.h"
#include "setup.h"



typedef enum
{
    CMD_START = 1,
    CMD_STOP,
    CMD_PLUS,
    CMD_MINUS,
    CMD_STRRG,
    CMD_STRG,
    CMD_CLRRG

}Commands;

typedef struct
{
    Commands commands;
    float param1;
    float param2;
}FullCommand;

bool DecodeCommand(const uint8_t* command, FullCommand *commandTranslated);


#endif
