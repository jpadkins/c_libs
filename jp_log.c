
///////////////////////////////////////////////////////////////////////////////
/// @file	jp_log.h
/// @author	Jacob Adkins (jpadkins)
/// @brief	API for logging information and possibly halting execution
///////////////////////////////////////////////////////////////////////////////
#include "jp_log.h"

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////
// Defines
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @brief Size of buffer for jpLog_*Fmt* functions
///////////////////////////////////////////////////////////////////////////////
#define MSGBUFF_SIZE 1024

///////////////////////////////////////////////////////////////////////////////
// Public functions
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
void jpLog__info(
        const char *file,
        const char *func,
        int line,
        const char *msg,
        ...)
{
    va_list ap;
    char msgbuff[MSGBUFF_SIZE];

    va_start(ap, msg);
    vsprintf(msgbuff, msg, ap);
    va_end(ap);

    fprintf(
            stdout,
            "[\33[34;1mINFO\33[0m][%s][%s][%d]: %s\n",
            file,
            func,
            line,
            msgbuff
            );
}

///////////////////////////////////////////////////////////////////////////////
void jpLog__warn(
        const char *file,
        const char *func,
        int line,
        const char *msg,
        ...)
{
    va_list ap;
    char msgbuff[MSGBUFF_SIZE];

    va_start(ap, msg);
    vsprintf(msgbuff, msg, ap);
    va_end(ap);

    fprintf(
            stderr,
            "[\33[33;1mWARN\33[0m][%s][%s][%d]: %s\n",
            file,
            func,
            line,
            msgbuff
            );
}

///////////////////////////////////////////////////////////////////////////////
void jpLog__exit(
        const char *file,
        const char *func,
        int line,
        const char *msg,
        ...)
{
    va_list ap;
    char msgbuff[MSGBUFF_SIZE];

    va_start(ap, msg);
    vsprintf(msgbuff, msg, ap);
    va_end(ap);

    fprintf(
            stderr,
            "[\33[31;1mEXIT\33[0m][%s][%s][%d]: %s\n",
            file,
            func,
            line,
            msgbuff
            );

    exit(EXIT_FAILURE);
}

