/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 14:58:02 by abourdar          #+#    #+#             */
/*   Updated: 2020/12/14 14:47:06 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_fd(char *dst, int fd)
{
	char	*buf;
	int		ret;

	if (fd < 0 || BUFFER_SIZE <= 0
		|| !(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (NULL);
	if (dst == NULL)
		dst = ft_strdup("");
	while (!(ft_strchr(dst, '\n')))
	{
		if ((ret = read(fd, buf, BUFFER_SIZE)) < 0)
			return (NULL);
		buf[ret] = '\0';
		dst = ft_strjoin(dst, buf);
		if (ret == 0)
			break ;
	}
	free(buf);
	return (dst);
}

int		get_next_line(int fd, char **line)
{
	static char	*dst;
	char		*ptr;
	char		*tmp;

	if (!(dst = ft_read_fd(dst, fd)) || !line)
		return (-1);
	if ((ptr = ft_strchr(dst, '\n')))
	{
		tmp = dst;
		*line = ft_substr(tmp, 0, ptr - dst);
		dst = ft_strdup(dst + (ptr - dst) + 1);
		free(tmp);
		return (1);
	}
	else
	{
		*line = ft_strdup(dst);
		free(dst);
		dst = NULL;
		return (0);
	}
}
