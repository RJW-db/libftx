/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_input_buff.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/23 14:49:53 by rjw           #+#    #+#                 */
/*   Updated: 2025/05/09 15:23:25 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <fcntl.h>
#include <stdio.h>
#define MOVE_CURSOR_UP "\033[F"
#define CLEAR_LINE "\033[2K"

//	Static Functions
static ssize_t	process_input(char *buff, ssize_t rd, ssize_t buff_size);
static ssize_t	empty_filedescriptor(char *buff, ssize_t buff_size, bool mute);

// #define FILE_CREATION 256	// (NAME_MAX || MAX_PATH) + 1
//	only return 0 on EOF, and -1 on read() error
ssize_t	get_user_input(char *buff, ssize_t buff_size, char *msg, bool mute)
{
	ssize_t	rd;

	if (buff == NULL || buff_size <= 0)
		return (-1);
	if (msg != NULL)
		ft_putstr_fd(msg, STDOUT_FILENO);
	rd = read(STDIN_FILENO, buff, (size_t)buff_size);
	if (rd > 0 && rd <= buff_size)
	{
		rd = process_input(buff, rd, buff_size);
		if (rd > 0)
			return (rd);
		if (rd == -1)
			rd = empty_filedescriptor(buff, buff_size, mute);
		if (rd != -1)
			return (ft_putstr_fd(MOVE_CURSOR_UP CLEAR_LINE, STDOUT_FILENO), \
			get_user_input(buff, buff_size, msg, mute));
	}
	buff[0] = '\0';
	if (rd == -1)
		return (-1);
	if (msg != NULL)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

static ssize_t	process_input(char *buff, ssize_t rd, ssize_t buff_size)
{
	ssize_t	index;

	if (buff[0] == '\n')
		return (0);
	index = 0;
	while (index < rd && buff[index] != '\n')
		++index;
	if (buff[index] == '\n')
	{
		buff[index] = '\0';
		return (index);
	}
	if (rd < buff_size)
		buff[rd++] = '\0';
	if (buff[rd - 1] == '\0')
		return (rd);
	return (-1);
}

static ssize_t	empty_filedescriptor(char *buff, ssize_t buff_size, bool mute)
{
	ssize_t	rd;

	rd = buff_size;
	while (rd == buff_size)
	{
		rd = read(STDIN_FILENO, buff, (size_t)buff_size);
		if (rd < buff_size || buff[rd - 1] == '\n')
		{
			break ;
		}
	}
	buff[0] = '\0';
	if (mute == true)
		printf("Input of characters is over %ld\n", buff_size - 1);
	return (rd);
}
