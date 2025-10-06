#ifndef PIPEX_H
# define PIPEX_H

#include "ft_printf.h"
#include "libft.h"
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>

typedef struct s_fd
{
	int fd;
	int fl;
} t_fd;

typedef struct s_data 
{
	pid_t pid[2];
	t_fd fd[2];
	t_fd in;
	t_fd out;
	int exitCode;
} t_data;

void	init_struct(t_data *data, char **av);
void	child1(t_data *data, char **av, char **envp);
void	child2(t_data *data, char **av, char **envp);
void	ft_wait(t_data *data);
void	exit_process(t_data *data, char **args, int flag);
void	close_fd(t_fd *fd);
void	free_tab(char **tab);
char	**get_args(char **av, char **envp, int id);


#endif
