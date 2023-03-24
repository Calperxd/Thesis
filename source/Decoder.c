#include "Decoder.h"

bool DecodeCommand(const uint8_t* command, FullCommand *commandTranslated)
{
    const char *delimiters = "#";
    uint8_t counter = 0;
    uint8_t cmd[6] = {0};
    uint8_t param1[6] = {0};
    uint8_t param2[6] = {0};
    char *save_ptr;
    uint8_t *token = strtok_r((char *)command, delimiters, &save_ptr);
    uint8_t result = 0;

    while (token != NULL)
    {
        if (counter == 0)
        {
            strcpy((char *)cmd, (const char *)token);
        }
        if (counter == 1)
        {
            strcpy((char *)param1,(const char *)token);
        }
        if (counter == 2)
        {
            strcpy((char *)param2,(const char *)token);
        }
        // Chamadas subsequentes para strtok_r com NULL
        token = strtok_r(NULL, delimiters, &save_ptr);
        counter++;
    }

    result = strcmp((const char *)cmd, "START");
    if (result == 0)
    {
        commandTranslated->commands = CMD_START;
        commandTranslated->param1 = atof((const char *)param1);
        commandTranslated->param2 = 0;
        return true;
    }

    result = strcmp((const char *)cmd, "STOP");
    if (result == 0)
    {
        commandTranslated->commands = CMD_STOP;
        commandTranslated->param1 = 0;
        commandTranslated->param2 = 0;
        return true;
    }

    result = strcmp((const char *)cmd, "PLUS");
    if (result == 0)
    {
        commandTranslated->commands = CMD_PLUS;
        commandTranslated->param1 = 0;
        commandTranslated->param2 = 0;
        return true;
    }

    result = strcmp((const char *)cmd, "MINUS");
    if (result == 0)
    {
        commandTranslated->commands = CMD_MINUS;
        commandTranslated->param1 = 0;
        commandTranslated->param2 = 0;
        return true;
    }

    result = strcmp((const char *)cmd, "STRRG");
    if (result == 0)
    {
        commandTranslated->commands = CMD_STRRG;
        commandTranslated->param1 = roundToTwoDecimalPlaces(atof((const char *)param1));
        commandTranslated->param2 = roundToTwoDecimalPlaces(atof((const char *)param2));
        return true;
    }

    result = strcmp((const char *)cmd, "STRG");
    if (result == 0)
    {
        commandTranslated->commands = CMD_STRG;
        commandTranslated->param1 = 0;
        commandTranslated->param2 = 0;
        return true;
    }

    result = strcmp((    const char *)cmd, "CLRRG");
    if (result == 0)
    {
        commandTranslated->commands = CMD_CLRRG;
        commandTranslated->param1 = 0;
        commandTranslated->param2 = 0;
        return true;
    }
    return false;
}