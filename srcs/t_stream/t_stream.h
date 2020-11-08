# include "../minishell.h"

#ifndef FT_MINISHELL_T_STREAM_H
#define FT_MINISHELL_T_STREAM_H

#define DEFAULT_FD -1

typedef enum STREAM
{
    INPUT_index = 0,
    OUTPUT_index,
    ERROR_index
} e_stream;

typedef enum STREAM_TYPE
{
    is_default_stream = 0,
    is_pipe_stream,
    is_redirect_stream
} e_stream_type;

/**
 * is_output_create_or_truncate         : command > filename   # create or truncate output file
 * is_output_create_or_append           : command >> filename  # create or append output file
 * is_output_filedescriptor_aggregation : command >&2          # redidect stdout to stderror
 *                                        command >&1          # redirect stdout to stdout
 *                                        command 2>&1         # redirect stderror to stdout
 *                                        command 2>error.log  # redirect stderror to file
 *                                        command 1>output.log # redirect stdout to file
 *
 * is_input_from_file                   : command < filename        # redirect file content to stdin
 * is_input_from_string                 : command <<< 'content'     # redirect string content to stdin
 * is_input_from_multiple_string        : command <<EOF content     # redirect miltiline string to stdin
 *                                        content
 *                                        EOF
 */
typedef enum STREAM_REDIRECT_TYPE
{
    is_not_redirect = 0,
    is_output_create_or_truncate,
    is_output_create_or_append,
    is_output_filedescriptor_aggregation,
    is_input_from_file,
    is_input_from_string,
    is_input_from_multiple_string,
} e_stream_redirect_type;

typedef struct s_stream
{
    int fd;

    e_stream index;
    e_stream_type streamType;
    e_stream_redirect_type redirectType;

    t_lexema *redirectFilename;
    t_lexema *redirectInputString;

} t_stream;

t_stream** t_stream_init_streams();
t_stream* t_stream_init_input_stream();
t_stream* t_stream_init_output_stream();
t_stream* t_stream_init_error_stream();
t_stream* t_stream_init_stream();
t_stream* t_stream_first_open(t_stream *stream);

int t_stream_get_fd(t_stream *stream);



#endif //FT_MINISHELL_T_STREAM_H
