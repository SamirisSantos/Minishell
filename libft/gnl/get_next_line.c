/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-13 14:28:34 by cpinho-c          #+#    #+#             */
/*   Updated: 2024-12-13 14:28:34 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

static char	*read_file(int fd, char *buffer, char *stash)
{
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read > 0 && !(ft_strchr(stash, '\n')))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(stash);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		if (stash == NULL)
			stash = ft_strdup(buffer);
		else
		{
			temp = ft_strjoin(stash, buffer);
			free(stash);
			stash = temp;
		}
	}
	return (stash);
}

static char	*cp_line(char **stash, int *i)
{
	char	*temp;
	char	*line;
	size_t	r_len;

	r_len = ft_strlen(*stash) - (*i + 1);
	line = ft_substr(*stash, 0, *i + 1);
	if (r_len == 0)
	{
		free(*stash);
		*stash = NULL;
	}
	else
	{
		temp = ft_substr(*stash, *i + 1, r_len);
		free(*stash);
		*stash = temp;
	}
	return (line);
}

static char	*get_line(char **stash)
{
	int		i;
	char	*line;

	i = 0;
	if (!*stash || **stash == '\0')
		return (NULL);
	while ((*stash)[i] && (*stash)[i] != '\n')
		i++;
	if (ft_strchr(*stash, '\n'))
	{
		line = cp_line(stash, &i);
	}
	else
	{
		line = ft_strdup(*stash);
		free(*stash);
		*stash = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	stash = read_file(fd, buffer, stash);
	if (!stash)
	{
		free(buffer);
		return (NULL);
	}
	free(buffer);
	line = get_line(&stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	return (line);
}

//read(fd, void *buffer, BUFFER_SIZE);
// #include <stdio.h>
// int main()
// {
// 	char *line;
// 	int fd = open("maps/map1.ber", O_RDONLY);
// 	if (fd < 0)
// 		return (1);
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return(0);
// }