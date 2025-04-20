/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmacedo- <mmacedo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:58:40 by mmacedo-          #+#    #+#             */
/*   Updated: 2025/03/18 08:02:50 by mmacedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int	main(int argc, char **argv, char **envp)
{
	
	int		fd[2];
	int		error;
	pid_t	pid;
	
	if (argc == 5)
	{		
		error = pipex_check(argv, envp);
		if ( error != 0)
			return (error); 
		if (pipe(fd) == -1)
			return (-1);
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
			child(argv, envp, fd);
		waitpid(pid, NULL, 0);
		parent(argv, envp, fd);
	}
	ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
	return (0);
}

