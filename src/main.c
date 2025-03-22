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
	int	p[2];
	int	pid;
	
	(void)argc;
	if (pipex_check(argv) != 0)
		return (-1);
	pipe(p);
	pid = fork();
	if (pid == 0)
	{
	left_pipe(argv[1], argv[2], argv, p, envp);
	} else 
	{
	right_pipe(argv[4], argv[3], argv, p, envp);
	}
	return (0);
}
