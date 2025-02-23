/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:34:29 by rjw           #+#    #+#                 */
/*   Updated: 2025/02/23 16:33:54 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <limits.h>
#include <stdint.h>

//	Static Functions
static char		*str_merge(t_cchr *nl, char *buf, bool *nl_check, int32_t rd);
static size_t	str_len_newline(t_cchr *str);
static size_t	copy_check(char *dest, t_cchr *src, bool *nl_check);

/*
	get_next_line

	Used functions:
	- malloc
	- free
	- read
	- ft_strlen
	- free_str
*/
char	*gnl(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*new_line;
	int32_t		rd;
	bool		nl_check;

	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	new_line = NULL;
	rd = BUFFER_SIZE;
	new_line = str_merge(new_line, buff, &nl_check, BUFFER_SIZE);
	if (new_line && nl_check == true)
		return (new_line);
	while (rd == BUFFER_SIZE)
	{
		rd = read(fd, buff, BUFFER_SIZE);
		if (rd >= 0)
			new_line = str_merge(new_line, buff, &nl_check, rd);
		if (rd < 0 || !new_line || *new_line == '\0')
			return (free_str(&new_line));
		if (nl_check == true)
			return (new_line);
	}
	return (new_line);
}

/*
	Used functions:
	- malloc
	- free
	- read
	- ft_strlen
	- free_str
*/
char	*gnl_fds(int fd)
{
	static char	buff[MAX_FD][BUFFER_SIZE + 1];
	char		*new_line;
	int32_t		rd;
	bool		nl_check;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	new_line = NULL;
	rd = BUFFER_SIZE;
	new_line = str_merge(new_line, buff[fd], &nl_check, BUFFER_SIZE);
	if (new_line && nl_check == true)
		return (new_line);
	while (rd == BUFFER_SIZE)
	{
		rd = read(fd, buff[fd], BUFFER_SIZE);
		if (rd >= 0)
			new_line = str_merge(new_line, buff[fd], &nl_check, rd);
		if (rd < 0 || !new_line || *new_line == '\0')
			return (free_str(&new_line));
		if (nl_check == true)
			return (new_line);
	}
	return (new_line);
}

static char	*str_merge(t_cchr *nl, char *buf, bool *nl_check, int32_t rd)
{
	char	*ret;
	size_t	len;

	buf[rd] = '\0';
	if (buf[0] == '\0')
		return ((char *)nl);
	len = str_len_newline(nl) + str_len_newline(buf);
	ret = (char *)malloc((len + 1) * sizeof(char));
	if (ret == NULL)
		return (free_str((char **)&nl));
	len = copy_check(ret, nl, nl_check);
	len = copy_check(ret + len, buf, nl_check);
	while (*(buf + len) != '\0')
	{
		*buf = *(buf + len);
		++buf;
	}
	*buf = '\0';
	free((char *)nl);
	return (ret);
}

static size_t	str_len_newline(t_cchr *str)
{
	size_t	n;

	if (!str)
		return (0);
	n = 0;
	while (str[n] && str[n] != '\n')
		++n;
	if (str[n] == '\n')
		return (n + 1);
	return (n);
}

static size_t	copy_check(char *dest, t_cchr *src, bool *nl_check)
{
	size_t	i;

	i = 0;
	if (src == NULL)
		return (0);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		if (dest[i] == '\n')
		{
			dest[++i] = '\0';
			*nl_check = true;
			return (i);
		}
		++i;
	}
	dest[i] = '\0';
	*nl_check = false;
	return (i);
}
