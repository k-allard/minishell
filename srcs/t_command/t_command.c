//# include "../minishell.h"
//#include <assert.h>
//#include "../t_stream/t_stream.h"
//#include "t_command.h"
//
//
///**
// * Выделение памяти и инициализация пустыми значениями нового элемента command
// * @return NULL, если память не было выделена, t_command, если память была выделена
// */
//t_command* t_command_init()
//{
//    t_command *command;
//
//    command = (t_command *)malloc(sizeof(t_command));
//    if(command != NULL)
//    {
//        command->name = t_lexema_init();
//        command->arguments = NULL;
//        command->streams = t_stream_init_streams();
//        command->command_prev = NULL;
//        command->command_next = NULL;
//    }
//    return command;
//}
//
//
//void t_command_free(t_command *command)
//{
//
//}
