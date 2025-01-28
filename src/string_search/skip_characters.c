/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   skip_characters.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:30:24 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/08 17:44:16 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	skip_alpha(t_cchr *str)
{
	size_t	i;

	i = 0;
	while (ft_isalpha(str[i]) == 1024)
		++i;
	return (i);
}

size_t	skip_digits(t_cchr *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && ft_isdigit(str[i]))
		++i;
	return (i);
}

size_t	skip_signed_digits(t_cchr *str)
{
	size_t	i;

	i = 0;
	if (str[i] != '\0' && (str[i] == '-' || str[i] == '+'))
		++i;
	if (str[i] == '\0' || ft_isdigit(str[i]) == 0)
		return (0);
	while (str[i] != '\0' && ft_isdigit(str[i]))
		++i;
	return (i);
}

size_t	skip_spaces(t_cchr *str)
{
	size_t	i;

	i = 0;
	while (ft_isspace(str[i]) == 1)
		++i;
	return (i);
}
