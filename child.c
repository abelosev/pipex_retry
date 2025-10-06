#include "pipex.h"

// использовать флаги, чтобы переписать закрытие fd короче

void	child1(t_data *data, char **av, char **envp)
{
	char **args;

	close_fd(&data->fd[0]);
	close_fd(&data->out);
	args = get_args(av, envp, 2);
	if (!args)
		exit_process(data, args, 127); 	// временно, пока не напиан get_path
	if (dup2(data->in.fd, STDIN_FILENO) < 0)
		exit_process(data, args, errno);
	close_fd(&data->in);
	if (dup2(data->fd[1].fd, STDOUT_FILENO) < 0)
		exit_process(data, args, errno);
	close_fd(&data->fd[1]);
	if (execve(args[0], args + 1, envp) < 0)
		exit_process(data, args, 127);
}

void	child2(t_data *data, char **av, char **envp)
{
	char **args;

	close_fd(&data->fd[1]);
	close_fd(&data->in);
	args = get_args(av, envp, 3);
	if (!args)
		exit_process(data, args, 127);
	if (dup2(data->fd[0].fd, STDIN_FILENO) < 0)
		exit_process(data, args, errno);
	close_fd(&data->fd[0]);
	if (dup2(data->out.fd, STDOUT_FILENO) < 0)
		exit_process(data, args, errno);
	close_fd(&data->out);
	if (execve(args[0], args + 1, envp) < 0)
		exit_process(data, args, 127);
}