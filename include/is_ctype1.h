/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_ctype1.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/11 02:58:41 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/11 03:10:24 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_CTYPE1_H
# define IS_CTYPE1_H

static inline int	ft_isalnum(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)
		|| (c >= 48 && c <= 57))
		return (8);
	return (0);
}

static inline int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1024);
	return (0);
}

static inline int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

static inline int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
#endif