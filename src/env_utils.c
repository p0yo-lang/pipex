#include "pipex.h"

int	exec_command(char *command, char **envp)
{
	char	**command_array;

	command_array = ft_split(command, ' ');
	execve(command_array[0], command_array, envp);
	free(command_array);
	return (0);
}	

