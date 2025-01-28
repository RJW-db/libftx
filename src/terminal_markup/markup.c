/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   markup.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/13 18:13:07 by rde-brui      #+#    #+#                 */
/*   Updated: 2025/01/13 19:09:26 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <terminal_markup.h>

void	markup(t_cchr *str, ...)
{
	va_list	style;
	int		num_styles;
	int		minus_check;

	num_styles = 0;
	va_start(style, str);
	while (va_arg(style, int) != 0)
		num_styles++;
	va_end(style);
	va_start(style, str);
	if (num_styles == 0)
		printf("%s", str);
	else if (num_styles > 0)
	{
		minus_check = va_arg(style, int);
		printf("\033[%d", minus_check);
		while (--num_styles)
			printf(";%d", va_arg(style, int));
		printf("m%s\033[0m", str);
		fflush(stdout);
	}
	va_end(style);
}

void	print_full_width(t_csize_t c)
{
	struct winsize	w;
	const size_t	markup = sizeof(MARKUP) - 1;
	const size_t	markdown = sizeof(MARKDOWN) - 1;
	char			*chr;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	chr = (char *)malloc((w.ws_col + markup + markdown + 1));
	if (chr == NULL)
	{
		perror("print_full_width: ");
		return ;
	}
	memcpy(chr, MARKUP, markup);
	memset(chr + markup, c, w.ws_col);
	memcpy(chr + markup + w.ws_col, MARKDOWN, markdown);
	chr[markup + w.ws_col + markdown] = '\0';
	printf("%s", chr);
	fflush(stdout);
	free(chr);
}
