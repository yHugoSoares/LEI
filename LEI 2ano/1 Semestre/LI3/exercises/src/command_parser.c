#include "command_parser.h"

// struct cmd
// {
//     char *command;
//     int *args;
//     int nargs;
// } Cmd;

void processCommand(Deque *deque, Cmd *cmd)
{

}

Cmd* parseLine(char* line)
{
    // Initialize CMD struct
    Cmd* cmd = malloc(sizeof(Cmd));
    cmd->args = NULL;
    cmd->nargs = 0;

    // Separate in tokens
    char* str = strdup(line);
    char* token = strsep(&str, "");

    // Cicle through tokens
    while (token)
    {
        if (strlen(token) > 0)
        {
            if (!cmd->command)
            {
                cmd->command = strdup(token);
            }
            else if(!cmd->args)
            {
                cmd->args = malloc(sizeof(int));
                cmd->args[cmd->nargs] = atoi(token);
            }
            // Fill args with token
            else
            {
                cmd->args = realloc(sizeof(int), (cmd->nargs+1));
                cmd->args[cmd->nargs] = atoi(token);
                cmd->nargs++;
            }

            cmd->nargs++;
        }
        token = strsep(&str, "");
    }
    

    return NULL;
}