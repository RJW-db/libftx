/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printf.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/15 13:29:00 by rde-brui      #+#    #+#                 */
/*   Updated: 2025/01/13 18:44:32 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>	// perror
#include <ft_printf.h>

//	Static Functions
static int32_t	ft_printf_all(int fd, t_cchr *format, va_list args);

int	ft_printf(t_cchr *format, ...)
{
	va_list	args;
	int		result;

	va_start(args, format);
	result = ft_printf_all(STDOUT_FILENO, format, args);
	va_end(args);
	return (result);
}

int	ft_dprintf(int fd, t_cchr *format, ...)
{
	va_list	args;
	int		result;

	va_start(args, format);
	result = ft_printf_all(fd, format, args);
	va_end(args);
	return (result);
}

int	ft_vprintf(t_cchr *format, va_list args)
{
	return (ft_printf_all(STDOUT_FILENO, format, args));
}

static int32_t	ft_printf_all(int fd, t_cchr *format, va_list args)
{
	t_p		print;
	int32_t	total;

	if (format == NULL)
		return (-1);
	print.fmt = format;
	print.count_or_str = true;
	va_copy(print.va, args);
	total = parse_format_string(&print);
	va_end(print.va);
	print.str = (char *)malloc((total + 1) * sizeof(char));
	if (print.str == NULL)
		return (0);
	print.str[total] = '\0';
	print.count_or_str = false;
	va_copy(print.va, args);
	parse_format_string(&print);
	va_end(print.va);
	if (write(fd, print.str, total) == -1)
		perror("ft_printf_all: write: ");
	free(print.str);
	return (total);
}
