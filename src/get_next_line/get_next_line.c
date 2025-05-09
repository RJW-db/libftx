/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:34:29 by rjw           #+#    #+#                 */
/*   Updated: 2025/05/09 15:24:41 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <limits.h>
#include <stdint.h>

//	Static Functions
static char
*str_merge(const char *nl, char *buff, bool *nl_check, ssize_t rd);
static size_t	str_len_newline(const char *str);
static size_t	copy_check(char *dest, const char *src, bool *nl_check);

/*
	get_next_line

	Used functions:
	- malloc
	- free
	- read
	- ft_strlen
	- free_str
*/
char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*new_line;
	bool		nl_check;
	ssize_t		rd;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
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
char	*get_next_line_fds(int fd)
{
	static char	buff[MAX_FD][BUFFER_SIZE + 1];
	char		*new_line;
	bool		nl_check;
	ssize_t		rd;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
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

static char	*str_merge(const char *nl, char *buff, bool *nl_check, ssize_t rd)
{
	char	*ret;
	size_t	len;

	buff[rd] = '\0';
	if (buff[0] == '\0')
		return ((char *)nl);
	len = str_len_newline(nl) + str_len_newline(buff);
	ret = (char *)malloc((len + 1) * sizeof(char));
	if (ret == NULL)
		return (free_str((char **)&nl));
	len = copy_check(ret, nl, nl_check);
	len = copy_check(ret + len, buff, nl_check);
	while (*(buff + len) != '\0')
	{
		*buff = *(buff + len);
		++buff;
	}
	*buff = '\0';
	free((char *)nl);
	return (ret);
}

static size_t	str_len_newline(const char *str)
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

static size_t	copy_check(char *dest, const char *src, bool *nl_check)
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
