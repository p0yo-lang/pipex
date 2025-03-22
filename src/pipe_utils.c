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

/* */
void left_pipe(char *file, char *command, int pipe_fd[2], char **envp)
{
	int	fd;

	fd = open(file, O_RDONLY);
	dup2(fd, 0);
	dup2(pipe_fd[1], 1);
	close(pipe_fd[0]);
	exec_command(command, envp);
}

void right_pipe(char *file, char *command, int pipe_fd[2], char **envp)
{
	int	fd;

	fd = open(file, 1);
	dup2(fd, 1);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
	exec_command(command, envp);
}