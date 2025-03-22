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
**an error if needed 
**return 1 if the input file doesn't exist
**return 2 if the input file doesn't have read access
**create the output file if it doesn't exist
**return 4 if the output file doesn't have write access
**return 0 if everything is ok
*/
int	check_files(char **argv)
{
	if (check_path_access(argv[1]) == 1)
		return (print_error(1, argv[1]), 1);
	if (check_path_access(argv[1]) == 2)
		return (print_error(2, argv[1]), 2);
	if (check_path_access(argv[4]) == 1)
		create_file(argv[4]);
	if (access(argv[4], W_OK) == -1)
		return (print_error(4, argv[4]), 4);
	return (0);
}

/*Check if the command (char *command) exists
**via the check_path_access(char *path) function and print an error if needed 
**return the first path the function found
**return NULL if the command doesn't exist or doesn't have execute access
*/
char	*check_command_access(char *command)
{
	const char	*path_set[3];
	char		*path;
	int			i;

	i = 0;
	path_set[0] = "/sbin/";
	path_set[1] = "/bin/";
	path_set[2] = "/usr/bin/";
	while (i < 3)
	{
		path = ft_strjoin(path_set[i], command);
		if (check_path_access(path) == 0)
			return (path);
		free(path);
		i++;
	}
	return (print_error(4, command), NULL);
}

/*Prints an error message depending on the error code (int error)
**and the argv parameter
*/
void	print_error(int error, char *argv)
{
	ft_printf("pipex: ");
	if (error == 1)
		ft_printf("%s : No such file or directory\n", argv);
	if (error == 2)
		ft_printf("%s : Permission denied\n", argv);
	if (error == 3)
		ft_printf(": pipe error\n");
	if (error == 4)
		ft_printf("%s : command not found\n", argv);
}

/*check files and command access
**return 1 if there is an error
**return 0 if everything is ok 
*/
int	pipex_check(char **argv)
{
	char	*path;

	if (check_files(argv) != 0)
		return (1);
	path = check_command_access(argv[2]);
	if (path == NULL)
		return (free(path), 1);
	free(path);
	path = check_command_access(argv[3]);
	if (path == NULL)
		return (free(path), 1);
	free(path);
	return (0);
}
