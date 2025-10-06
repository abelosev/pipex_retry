//./pipex file1 cmd1 cmd2 file2

// < file1 cmd1 | cmd2 > file2

// < input.txt grep "error" | wc -l > output.txt

// ошибки:

// не обрабатывать infile и outfile вместе

// bash-3.2$ ./pipex "" "grep uhuh" "wc -l" out
// Error: No such file or directory
// bash-3.2$ cat out
// cat: out: No such file or directory

// разобраться с выводом на dev/null

// bash-3.2$ ./pipex test.txt "grep haha" "wc -l" dev/null 
// Error: No such file or directory

#include "pipex.h"

void	init_fd(t_data *data, int *tmp)
{
	data->fd[0].fd = tmp[0];
	data->fd[1].fd = tmp[1];
	data->fd[0].fl = 1;
	data->fd[1].fl = 1;
}

int ft_pipex(char **av, char **envp)
{
	t_data data;
	int tmp[2];

	init_struct(&data, av);
	if (pipe(tmp) < 0)
		exit_process(&data, NULL, errno);
	init_fd(&data, tmp);
	data.pid[0] = fork();
	if (data.pid[0] == -1)
		exit_process(&data, NULL, errno);
	else if (data.pid[0] == 0)
		child1(&data, av, envp);
	close_fd(&data.fd[1]); // после fork child1 родитель закрывает fd[1], чтобы child2 корректно получил EOF (???)
	data.pid[1] = fork();
	if (data.pid[1] == -1)
		exit_process(&data, NULL, errno);
	else if (data.pid[1] == 0)
		child2(&data, av, envp);
	exit_process(&data, NULL, 0);
	ft_wait(&data);
	return (data.exitCode);
}

int main(int ac, char **av, char **envp)
{
	if (ac != 5)
	{
		ft_putstr_fd("Incorrect number of args\n", STDERR_FILENO);
		return (1);
	}
	if (!envp || !(*envp))
	{
		ft_putstr_fd("Envp doesn't exist\n", STDERR_FILENO);
		return (1);
	}
	return (ft_pipex(av, envp));
}