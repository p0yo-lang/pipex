/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmacedo- <mmacedo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 18:06:13 by mmacedo-          #+#    #+#             */
/*   Updated: 2025/03/17 17:14:57 by mmacedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

/*Check if the program has access to the file (path)
**return 1 if the file doesn't exist
**return 2 if the file doesn't have read access
**return 0 if everything is ok
*/
int	check_path_access(char *path)
{
	if (access(path, F_OK) == -1)
		return (1);
	if (access(path, R_OK) == -1)
		return (2);
	return (0);
}

/*Check if output and input files (argv[1] && argv[4]) exist
**via the check_path_access(char *path) function and print 
**an error if needed and a bash like error code is returned
**return 0 if everything is ok
*/
int	check_files(char **argv)
{
	if (check_path_access(argv[1]) == 1)
		return (print_error("no such file or directory ", argv[1]), 127);
	if (check_path_access(argv[1]) == 2)
		return (print_error("persnission denied", argv[1]), 126);
	if (check_path_access(argv[4]) == 1)
		create_file(argv[4]);
	if (access(argv[4], W_OK) == -1)
		return (print_error("permission denied", argv[4]), 126);
	return (0);
}

/*Check if the command (char *command) exists
**via the check_path_access(char *path) function and print an error if needed 
**return the first path the function found
**return NULL if the command doesn't exist or doesn't have execute access
*/
char	*check_command_access(char *command, char **envp)
{
	char		*path;
	char 		**command_array;

	command_array = ft_split(command, ' ');
	path = get_path(command_array[0], envp);
	if (!path)
		print_error("command not found", command_array[0]);
	free_paths(command_array);
	return (path);
}
/*Print an error like bash*/
void	print_error(char *msg, char *arg)
{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(msg, 2);

}

/*check files and command access
**return 127 if the command is not found
**return 0 if everything is ok 
*/
int	pipex_check(char **argv, char **envp)
{
	char	*path;
	int		file_error;

	file_error = check_files(argv);
	if (file_error != 0)
		return (file_error);
	path = check_command_access(argv[2], envp);
	if (path == NULL)
		return (free(path), 127);
	free(path);
	path = check_command_access(argv[3], envp);
	if (path == NULL)
		return (free(path), 127);
	free(path);
	return (0);
}
