#include "pipex.h"

void	free_tab(char **tab)
{
	int i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	error_msg_exit(int flag)
{
	if (flag == 127)
		ft_putstr_fd("Command not found\n", STDERR_FILENO);
	else
	{
		perror("Error");
		flag = 1;
	}
	exit(flag);
}

void	close_fd(t_fd *fd)
{
	if (fd->fl)
	{
		close(fd->fd);
		fd->fl = 0;
	}
}

void	exit_process(t_data *data, char **args, int flag)
{
	int flag_copy;

	flag_copy = flag;
	free_tab(args);
	close_fd(&data->in);
	close_fd(&data->out);
	close_fd(&data->fd[0]);
	close_fd(&data->fd[1]);
	if (data->pid[1] == -1 || data->pid[1] == 0)
		waitpid(data->pid[0], NULL, 0);			// что будет, если этот waitpid вернет -1 ?
	if (flag_copy)
		error_msg_exit(flag_copy);
}