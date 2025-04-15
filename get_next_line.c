/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:42:37 by vimazuro          #+#    #+#             */
/*   Updated: 2024/11/15 16:25:30 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_read_line(char *line)
{
	int		i;
	char	*read_line;

	if (!line || !line[0])
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	read_line = (char *)malloc((i + 2) * sizeof(char));
	if (!read_line)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		read_line[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
	{
		read_line[i] = '\n';
		i++;
	}
	read_line[i] = '\0';
	return (read_line);
}

static char	*ft_move_start(char *line)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	while (line && line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\0')
	{
		free(line);
		return (NULL);
	}
	new_line = (char *)malloc((ft_strlen(line) - i) * sizeof(char));
	if (!new_line)
		return (NULL);
	i++;
	j = 0;
	while (line[i + j])
	{
		new_line[j] = line[i + j];
		j++;
	}
	new_line[j] = '\0';
	free(line);
	return (new_line);
}

static char	*ft_read_join(int fd, char *line, char *tmp)
{
	int	fd_read;

	fd_read = 1;
	while (!(ft_strchr(line, '\n')) && fd_read != 0)
	{
		fd_read = read(fd, tmp, BUFFER_SIZE);
		if (fd_read == -1)
		{
			free(line);
			return (NULL);
		}
		tmp[fd_read] = '\0';
		line = ft_strjoin(line, tmp);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*tmp;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!line)
	{
		line = (char *)malloc(1);
		if (!line)
			return (NULL);
		line[0] = '\0';
	}
	tmp = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	line = ft_read_join(fd, line, tmp);
	free(tmp);
	if (!line)
		return (NULL);
	result = ft_read_line(line);
	line = ft_move_start(line);
	return (result);
}
