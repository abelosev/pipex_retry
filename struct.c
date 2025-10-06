#include "pipex.h"

void	init_struct(t_data *data)
{
	data->exitCode = 0;
	data->pid[0] = -2;
	data->pid[1] = -2;
	data->fd[0].fd = -1;
	data->fd[1].fd = -1;
	data->fd[0].fl = 0;
	data->fd[1].fl = 0;
	data->in.fd = -1;
	data->out.fd = -1;
	data->in.fl = 0;
	data->out.fl = 0;
}