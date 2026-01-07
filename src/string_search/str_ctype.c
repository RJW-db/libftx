/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_ctype.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/13 15:57:49 by rjw           #+#    #+#                 */
/*   Updated: 2025/04/13 16:24:09 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "is_ctype1.h"

bool	str_check_all(const char *str, int (*func)(int))
{
	while (*str)
	{
		if (func((unsigned char)*str) == 0)
			return (false);
		++str;
	}
	return (true);
}
