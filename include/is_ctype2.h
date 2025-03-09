/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_ctype2.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/11 02:58:41 by rjw           #+#    #+#                 */
/*   Updated: 2025/03/09 02:19:04 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_CTYPE2_H
# define IS_CTYPE2_H

static inline int	ft_isspace(int c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}

static inline int	ft_isupper(int c)
{
	return (c >= 'A' && c <= 'Z');
}

static inline int	ft_islower(int c)
{
	return (c >= 'a' && c <= 'z');
}

static inline int	ft_isprint(int c)
{
	return (c >= ' ' && c <= '~');
}
#endif