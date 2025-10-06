#include "pipex.h"

// void	init_files(t_data *data, char **av)
// {
// 	data->in.fl = 0;
// 	data->out.fl = 0;
// 	data->in.fd = open(av[1], O_RDONLY);
// 	if (data->in.fd < 0)
// 	{
// 		perror("Error");
// 		exit(1);
// 	}
// 	data->in.fl = 1;
// 	data->out.fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644); //-rw-r--r--
// 	if (data->out.fd < 0)
// 	{
// 		perror("Error");
// 		exit(1);
// 	}
// 	data->out.fl = 1;
// }

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
	//init_files(data, av);	// это нужно исправить
}