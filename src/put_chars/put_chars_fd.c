/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   put_chars_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/09 20:31:53 by rde-brui      #+#    #+#                 */
/*   Updated: 2025/05/09 15:16:18 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <libftx.h>

void	ft_putchar_fd(char c, int fd)
{
	if (write(fd, &c, 1) == -1)
		perror("ft_putchar_fd: write");
}

void	ft_putendl_fd(const char *s, int fd)
{
	char	destination[BUFF_SIZE];
	size_t	i;

	i = 0;
	while (*s != '\0')
	{
		destination[i] = *s;
		++s;
		if (i == (BUFF_SIZE - 1))
		{
			if (write(fd, destination, BUFF_SIZE) == -1)
			{
				perror("ft_putendl_fd: write");
				return ;
			}
			i = 0;
			continue ;
		}
		++i;
	}
	destination[i] = '\n';
	if (write(fd, destination, i + 1) == -1)
		perror("ft_putendl_fd: write");
}

void	ft_putnbr_fd(int n, int fd)
{
	char	store[11];
	char	*number;
	int		negative;

	number = store + 10;
	if (n == 0)
	{
		if (write(fd, "0\n", 2) == -1)
			perror("ft_putnbr_nl_fd: write");
		return ;
	}
	negative = n;
	if (n < 0)
		negative = -n;
	while (negative != 0)
	{
		*(number--) = (char)('0' + (negative % 10));
		negative /= 10;
	}
	if (n < 0)
		*(number--) = '-';
	if (write(fd, number, (size_t)((store + 10) - number + 1)) == -1)
		perror("ft_putnbr_nl_fd: write");
}

void	ft_putnbr_nl_fd(int n, int fd)
{
	char	store[12];
	char	*number;
	int		negative;

	number = store + 11;
	*(number) = '\n';
	if (n == 0)
	{
		if (write(fd, "0\n", 2) == -1)
			perror("ft_putnbr_nl_fd: write");
		return ;
	}
	negative = n;
	if (n < 0)
		negative = -n;
	while (negative != 0)
	{
		*(number--) = (char)('0' + (negative % 10));
		negative /= 10;
	}
	if (n < 0)
		*(--number) = '-';
	if (write(fd, number, (size_t)((store + 11) - number + 1)) == -1)
		perror("ft_putnbr_nl_fd: write");
}

void	ft_putstr_fd(const char *s, int fd)
{
	if (write(fd, s, ft_strlen(s)) == -1)
		perror("ft_putstr_fd: write");
}
