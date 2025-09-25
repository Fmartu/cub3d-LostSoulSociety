/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:00:00 by fabi              #+#    #+#             */
/*   Updated: 2025/01/20 10:00:00 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

char	*get_line_from_buffer(char *buffer)
{
	char	*line;
	int		i;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = ft_substr(buffer, 0, i);
	return (line);
}

char	*update_static_buffer(char *buffer)
{
	char	*new_buffer;
	int		i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = ft_strdup(buffer + i + 1);
	free(buffer);
	return (new_buffer);
}

int	read_to_buffer(char **buffer, int fd)
{
	char	*temp;
	char	*old_buffer;
	int		bytes_read;

	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (-1);
	bytes_read = read(fd, temp, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(temp);
		return (bytes_read);
	}
	temp[bytes_read] = '\0';
	old_buffer = *buffer;
	*buffer = ft_strjoin(old_buffer, temp);
	free(old_buffer);
	if (!*buffer)
		return (free(temp), -1);
	free(temp);
	return (bytes_read);
}
