#include "pipex.h"

char **get_path_tab(char **envp)
{
	char **path_tab;
	int len;
	int i;

	path_tab = NULL;
	len = ft_strlen("PATH=");
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", len))
			break ;
		i++;
	}
	if (i >= 0 && envp[i][len])
	{
		path_tab = ft_split(envp[i] + len, ':');
		if (!path_tab)
			return (NULL);
	}
	return (path_tab);
}

char *ft_boucle(char *pathname, char **path_tab, char *tmp)
{
	int		i;

	i = 0;
	while (path_tab[i])
	{
		pathname = ft_strjoin(path_tab[i], tmp);
		if (!pathname)
			return (NULL);
		if (!access(pathname, X_OK))
			break ;
		free(pathname);
		pathname = NULL;
		i++;
	}
	return (pathname);
}

char *get_pathname(char **args, char **envp)
{
	char	*pathname;
	char	**path_tab;
	char	*tmp;
	
	pathname = NULL;
	tmp = ft_strjoin("/", args[0]);
	if (!tmp)
		return (NULL);
	path_tab = get_path_tab(envp);
	if (!path_tab)
		return (free(tmp), NULL);
	pathname = ft_boucle(pathname, path_tab, tmp);
	free_tab(path_tab);
	free(tmp);
	return (pathname);
}

char **get_res_tab(char *pathname, char **args)
{
	int i;
	int k;
	char **res;

	i = 0;
	while (args[i])
		i++;
	res = malloc(sizeof(char *) * (i + 2));
	if (!res)
		return (NULL);
	res[0] = ft_strdup(pathname);
	if (!res[0])
		return (free(res), NULL);
	k = 1;
	while (k < i + 1)
	{
		res[k] = ft_strdup(args[k - 1]);
		if (!res[k])
			return (free_tab(res), NULL);
		k++;
	}
	res[k] = NULL;
	return (res);
}

char **get_args(char **av, char **envp, int id)
{
	char	*pathname;
	char	**args;
	char	**res;

	args = ft_split(av[id], ' ');
	if (!args || !*args || !**args) // проверка для случая, если split вернет пустую строку
		return (NULL);
	if (ft_strchr(args[0], '/'))
		pathname = ft_strdup(args[0]);
	else
		pathname = get_pathname(args, envp);
	if (!pathname)
		return (free_tab(args), NULL);
	if (access(pathname, X_OK) < 0)
		return (free(pathname), free(args), NULL);
	res = get_res_tab(pathname, args);
	if (!res)
		return (free(pathname), free_tab(args), NULL);
	free(pathname);
	return (free_tab(args), res);
}