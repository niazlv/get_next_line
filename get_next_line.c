#include "get_next_line.h"
#include <stdio.h>


char	*ft_shrink_buffer(char *buf, char *line)
{
	char	*newbuf;
	int		line_len;

	if (!buf || !line)
		return (buf);
	line_len = ft_strlen(line);
	if ((int)ft_strlen(buf) == line_len)
	{
		free(buf);
		return (NULL);
	}
	newbuf = ft_substr(buf, line_len, ft_strlen(buf) - line_len);
	free(buf);
	return (newbuf);
}

char	*ft_expand_buffer(char *buf, int fd)
{
	char	*newbuf;
	int		newlen;
	char	*aux;

	aux = ft_newread(fd);
	if (!aux)
		return (NULL);
	if (!aux[0])
	{
		free(aux);
		return (buf);
	}
	if (!buf)
		return (aux);
	newlen = ft_strlen(buf) + ft_strlen(aux);
	newbuf = malloc(newlen + 1);
	if (!newbuf)
		return (NULL);
	ft_strlcpy(newbuf, buf, newlen + 1);
	ft_strlcat(newbuf, aux, newlen + 1);
	free(buf);
	free(aux);
	return (newbuf);
}

char	*ft_newread(int fd)
{
	char	*aux;
	int		nbytes;

	aux = malloc(BUFFER_SIZE + 1);
	if (!aux)
		return (NULL);
	nbytes = read(fd, aux, BUFFER_SIZE);
	if (nbytes < 0)
	{
		free(aux);
		return (NULL);
	}
	aux[nbytes] = '\0';
	return (aux);
}

char	*get_next_line(int fd)
{
	static char	*buf[4096];
	char		*line;
	size_t		old_len;

	if (fd < 0 || fd > 4095 || BUFFER_SIZE < 0)
		return (NULL);
	line = NULL;
	if (ft_strchr_i(buf[fd], '\n') == -1)
	{
		old_len = ft_strlen(buf[fd]);
		buf[fd] = ft_expand_buffer(buf[fd], fd);
		if (old_len == ft_strlen(buf[fd]) && buf[fd])
			line = ft_substr(buf[fd], 0, ft_strlen(buf[fd]));
	}
	if (!buf[fd])
		return (NULL);
	if (!line && ft_strchr_i(buf[fd], '\n') != -1)
		line = ft_substr(buf[fd], 0, ft_strchr_i(buf[fd], '\n') + 1);
	if (line)
	{
		buf[fd] = ft_shrink_buffer(buf[fd], line);
		return (line);
	}
	return (get_next_line(fd));
}
