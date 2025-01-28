/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_ctype2.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/11 02:58:41 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/11 17:38:33 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_CTYPE2_H
# define IS_CTYPE2_H

static inline int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || \
	c == '\v' || c == '\f' || c == '\r');
}

static inline int	ft_isupper(int c)
{
	return (c >= 65 && c <= 90);
}

static inline int	ft_islower(int c)
{
	return (c >= 97 && c <= 122);
}

static inline int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}
#endif