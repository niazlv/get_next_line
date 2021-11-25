#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE

#  define BUFFER_SIZE 42

# endif
char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
int		ft_strchr_i(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_shrink_buffer(char *buf, char *line);
char	*ft_expand_buffer(char *buf, int fd);
char	*ft_newread(int fd);

#endif