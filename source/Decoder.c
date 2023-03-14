#include "Decoder.h"

const int MAX_STRING_LENGTH = 21;

void DecodeCommand(const uint8_t* command, FullCommand *commandTranslated)
{
    uint8_t hashTagsIndex[6] = {0};
    uint8_t hashTagIndexCounter = 0;
    uint8_t cmd[5] = {0};
    uint8_t param1[5] = {0};
    uint8_t param2[5] = {0};
    uint8_t copyCounter = 0;
    uint32_t result = 1;

    for (int i = 0; i < MAX_STRING_LENGTH; i++)
    {
        if (command[i] == '#')
        {
            hashTagsIndex[hashTagIndexCounter] = i;
            hashTagIndexCounter++;
        }
    }

    for (int i = (hashTagsIndex[0]+1); i < hashTagsIndex[1]; i++)
    {
        cmd[copyCounter] = command[i];
        copyCounter++;
    }
    copyCounter = 0;
    for (int i = (hashTagsIndex[2]+1); i < hashTagsIndex[3]; i++)
    {
        param1[copyCounter] = command[i];
        copyCounter++;
    }
    copyCounter = 0;
    for (int i = (hashTagsIndex[4]+1); i < hashTagsIndex[5]; i++)
    {
        param2[copyCounter] = command[i];
        copyCounter++;
    }

    result = strcmp(cmd, "START");
    if (result == 0)
    {
        commandTranslated->commands = CMD_START;
        commandTranslated->param1 = ceilf(atof(param1) * 100.0) / 100.0;
        commandTranslated->param2 = 0;
        return;
    }

    result = strcmp(cmd, "STOP");
    if (result == 0)
    {
        commandTranslated->commands = CMD_STOP;
        commandTranslated->param1 = 0;
        commandTranslated->param2 = 0;
        return;
    }

    result = strcmp(cmd, "PLUS");
    if (result == 0)
    {
        commandTranslated->commands = CMD_START;
        commandTranslated->param1 = 0;
        commandTranslated->param2 = 0;
        return;
    }

    result = strcmp(cmd, "MINUS");
    if (result == 0)
    {
        commandTranslated->commands = CMD_START;
        commandTranslated->param1 = 0;
        commandTranslated->param2 = 0;
        return;
    }

    result = strcmp(cmd, "STRRG");
    if (result == 0)
    {
        commandTranslated->commands = CMD_START;
        commandTranslated->param1 = ceilf(atof(param1) * 100.0) / 100.0;
        commandTranslated->param2 = ceilf(atof(param1) * 100.0) / 100.0;
        return;
    }

    result = strcmp(cmd, "STRG");
    if (result == 0)
    {
        commandTranslated->commands = CMD_START;
        commandTranslated->param1 = 0;
        commandTranslated->param2 = 0;
        return;
    }

    result = strcmp(cmd, "CLRRG");
    if (result == 0)
    {
        commandTranslated->commands = CMD_START;
        commandTranslated->param1 = 0;
        commandTranslated->param2 = 0;
        return;
    }


}