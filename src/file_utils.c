/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmacedo- <mmacedo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 18:02:55 by mmacedo-          #+#    #+#             */
/*   Updated: 2025/03/16 21:14:27 by mmacedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "pipex.h"

/* Creates a file with the name given as a parameter (char *file) 
**and returns its descriptor (fd)
*/
int	create_file(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_RDWR, 0666);
	if (fd == -1)
		return (1);
	close(fd);
	return (0);
}

/*Read the contend of the file given as parameters (char *filepath)
**and returns it as a string (char *filecontent)
*/
char	*read_file(const char *filepath)
{
	char	*buffer;
	char	*file_content;
	char	*temp;
	int		fd;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		return (NULL);
	buffer = NULL;
	file_content = malloc(1);
	if (file_content == NULL)
		return (NULL);
	file_content[0] = '\0';
	while (1)
	{
		buffer = get_next_line(fd);
		if (buffer == NULL)
			break ;
		temp = ft_strjoin(file_content, buffer);
		free(file_content);
		file_content = temp;
		free(buffer);
	}
	close(fd);
	return (file_content);
}
