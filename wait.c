#include "pipex.h"

void	ft_wait(t_data *data)
{
	int status;

	waitpid(data->pid[0], NULL, 0);
	waitpid(data->pid[1], &status, 0);
	if (WIFEXITED(status))
		data->exitCode = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->exitCode = 128 + WTERMSIG(status);
}