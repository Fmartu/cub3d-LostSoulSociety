/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 10:00:00 by fabi              #+#    #+#             */
/*   Updated: 2025/09/20 13:59:42 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static int	handle_cleanup_or_error(char **buffer, int fd, char **line)
{
	if (fd < 0 && !line && *buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (-1);
}

static int	determine_return_value(char *buffer, char **line, int bytes_read)
{
	if (bytes_read > 0)
		return (1);
	if (buffer && ft_strlen(buffer) > 0)
		return (1);
	if (*line && ft_strlen(*line) > 0)
		return (1);
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*buffer = NULL;
	int			bytes_read;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (handle_cleanup_or_error(&buffer, fd, line));
	if (!buffer)
		buffer = ft_strdup("");
	bytes_read = read_to_buffer(&buffer, fd);
	if (bytes_read == -1)
		return (-1);
	*line = get_line_from_buffer(buffer);
	if (!*line)
		return (-1);
	buffer = update_static_buffer(buffer);
	return (determine_return_value(buffer, line, bytes_read));
}

void	get_next_line_cleanup(void)
{
	get_next_line(-1, NULL);
}
