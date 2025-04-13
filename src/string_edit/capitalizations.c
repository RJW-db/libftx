/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   capitalizations.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/13 15:41:54 by rjw           #+#    #+#                 */
/*   Updated: 2025/04/13 15:48:46 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	to_lower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}

int	to_upper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}

char	*str_decapitalize(char *str)
{
	size_t	i;

	if (str != NULL)
	{
		i = 0;
		while (str[i] != '\0')
		{
			str[i] = (char)to_lower((unsigned char)str[i]);
			++i;
		}
	}
	return (str);
}

char	*str_capitalize(char *str)
{
	size_t	i;

	if (str != NULL)
	{
		i = 0;
		while (str[i] != '\0')
		{
			str[i] = (char)to_upper((unsigned char)str[i]);
			++i;
		}
	}
	return (str);
}
