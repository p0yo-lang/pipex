/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmacedo- <mmacedo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 06:01:03 by mmacedo-          #+#    #+#             */
/*   Updated: 2025/03/18 08:02:06 by mmacedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"

int		check_path_access(char *path);
int		check_files(char **argv);
int		create_file(char *file);
int		pipex_check(char **argv);
char	*check_command_access(char *command);
int		exec_command(char *command, char **envp);
char	*read_file(const char *filepath);
void	print_error(int error, char *argv);
void left_pipe(char *file, char *command, char **args, int pipe_fd[2], char **envp)



#endif  /* PIPEX_H */