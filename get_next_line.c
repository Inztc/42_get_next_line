/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btiewcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 19:43:45 by btiewcha          #+#    #+#             */
/*   Updated: 2022/09/03 15:07:12 by btiewcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_grab_line(char *save)
{
	int		i;
	char	*s;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	s = (char *)malloc(sizeof(char) * (i + 2));
	if (!s)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		s[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		s[i] = save[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_record(char *record)
{
	int		i;
	int		c;
	char	*s;

	i = 0;
	while (record[i] && record[i] != '\n')
		i++;
	if (!record[i])
	{
		free(record);
		return (NULL);
	}
	s = (char *)malloc(sizeof(char) * (ft_strlen(record) - i + 1));
	if (!s)
		return (NULL);
	i++;
	c = 0;
	while (record[i])
		s[c++] = record[i++];
	s[c] = '\0';
	free(record);
	return (s);
}

char	*ft_grab_and_record(int fd, char *save)
{
	int		read_bytes;
	char	*buffer;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(save, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		save = ft_strjoin(save, buffer);
	}
	free (buffer);
	return (save);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	save = ft_grab_and_record(fd, save);
	if (!save)
		return (NULL);
	line = ft_grab_line(save);
	save = ft_record(save);
	return (line);
}
