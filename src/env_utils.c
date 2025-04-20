#include "pipex.h"
#include <unistd.h>


void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

static char	*build_path(char *dir, char *command)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, command);
	free(temp);
	if (!full_path)
		return (NULL);
	return (full_path);
}
char	*get_path(char *command, char **envp)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	i = 0;
	path = NULL;
	while (paths[i])
	{
		path = build_path(paths[i], command);
		if (path && access(path, F_OK) == 0)
			break ;
		free(path);
		path = NULL;
		i++;
	}
	free_paths(paths);
	return (path);
}

int	exec_command(char *command, char **envp)
{
	char	**command_array;
	char	*path;

	command_array = ft_split(command, ' ');
	path = get_path(command_array[0], envp);
	if (path)	
		execve(path, command_array, envp);
	free_paths(command_array);
	return (0);
}