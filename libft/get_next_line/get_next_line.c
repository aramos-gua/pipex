/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:32:26 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/04/15 22:49:24 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	divide(char	*buffer, char **line_to_return)
{
	char	*line_ptr;
	char	*temp;
	size_t	line_len;
	size_t	leftover_len;

	line_ptr = gnl_strchr(buffer, '\n');
	if (!line_ptr)
		return ;
	line_len = gnl_strlen(buffer, '\n') + 1;
	leftover_len = gnl_strlen(buffer, '\0') - line_len;
	temp = gnl_substr(buffer, 0, line_len);
	if (!temp)
		return ;
	if (*line_to_return)
		*line_to_return = gnl_strjoin(*line_to_return, temp);
	else
	{
		*line_to_return = temp;
		temp = NULL;
	}
	free(temp);
	ft_memmove(buffer, line_ptr + 1, leftover_len);
	buffer[leftover_len] = '\0';
}

char	*get_next_line(int fd)
{
	static char	buffer[1024][BUFFER_SIZE + 1];
	char		*line_to_return;
	int			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line_to_return = NULL;
	if (gnl_strlen(buffer[fd], '\0') > 0 && gnl_strchr(buffer[fd], '\n'))
		return (divide(buffer[fd], &line_to_return), line_to_return);
	else if (gnl_strlen(buffer[fd], '\0') > 0 && !gnl_strchr(buffer[fd], '\n'))
		line_to_return = gnl_strjoin(line_to_return, buffer[fd]);
	while (1)
	{
		bytes = read(fd, buffer[fd], BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		buffer[fd][bytes] = '\0';
		if (gnl_strchr(buffer[fd], '\n'))
			return (divide(buffer[fd], &line_to_return), line_to_return);
		line_to_return = gnl_strjoin(line_to_return, buffer[fd]);
	}
	if (!line_to_return || line_to_return[0] == '\0')
		return (free(line_to_return), NULL);
	return (line_to_return);
}
