#ifndef COMMADS_H
#define COMMADS_H
#include <stddef.h>


#define CMD_ARGS_ARR_SIZE 2
#define INVALID_ARG -1

enum COMMAND_TYPE {
    INSERT,
    PRINT,
    PRINT_BUILDING
};

typedef struct command
{
    unsigned int arrival_time;
    COMMAND_TYPE cmd_type;
    int arg1;
    int arg2;
    command(unsigned int ar_time, COMMAND_TYPE ct , int arg1, int arg2)
    {
        this->arrival_time = ar_time;
        this->cmd_type = ct;
        this->arg1 = arg1;
        this->arg2 = arg2;
    }

}command;

#endif // COMMADS_H
