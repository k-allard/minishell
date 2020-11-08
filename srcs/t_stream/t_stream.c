#include "../minishell.h"
#include "t_stream.h"

t_stream** t_stream_init_streams()
{
    t_stream **streams;

    streams = (t_stream **)(malloc(3*sizeof(t_stream *)));
    if(streams)
    {
        streams[INPUT_index] = t_stream_init_input_stream();
        streams[OUTPUT_index] = t_stream_init_output_stream();
        streams[ERROR_index] = t_stream_init_error_stream();
    }
    return streams;
}

t_stream* t_stream_init_input_stream()
{
    t_stream *stream;

    stream = t_stream_init_stream();
    stream->index = INPUT_index;
    return stream;
}

t_stream* t_stream_init_output_stream()
{
    t_stream *stream;

    stream = t_stream_init_stream();
    stream->index = OUTPUT_index;
    return stream;
}

t_stream* t_stream_init_error_stream()
{
    t_stream *stream;

    stream = t_stream_init_stream();
    stream->index = ERROR_index;
    return stream;
}

t_stream* t_stream_init_stream()
{
    t_stream *stream;

    stream = (t_stream *)(malloc(sizeof(t_stream)));
    if(stream)
    {
        stream->fd = DEFAULT_FD;
        stream->streamType = is_default_stream;
        stream->redirectType = is_not_redirect;
        stream->redirectFilename = NULL;
        stream->redirectInputString = NULL;
    }
    return stream;
}

t_stream* t_stream_first_open(t_stream *stream)
{
    if(stream->streamType)
    {

    }
    return stream;
}



int t_stream_get_fd(t_stream *stream)
{
    if(stream->fd == DEFAULT_FD)
    {
        stream = t_stream_first_open(stream);
    }
    return stream->fd;
}
