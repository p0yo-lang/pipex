/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmacedo- <mmacedo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 21:16:11 by mmacedo-          #+#    #+#             */
/*   Updated: 2025/03/18 08:09:24 by mmacedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Sets up the child process to execute the first command.
 * Redirects output from the pipe and input to the given file.
 * Returns -1 if the input file can't be opened.
 */
int	child(char **argv, char **envp, int *fd)
{
	int		filein;

	filein = open(argv[1], O_RDONLY, 0777);
	if (filein == -1)
		return (-1);
	dup2(fd[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(fd[0]);
	exec_command(argv[2], envp);
	return (0);
}
/**
 * Sets up the parent process to execute the second command.
 * Redirects input from the pipe and output to the given file.
 * Returns -1 if the output file can't be opened.
 */
int	parent(char **argv, char **envp, int *fd)
{
	int		fileout;

	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
		return (-1);
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fd[1]);
	exec_command(argv[3], envp);
	return (0);
}