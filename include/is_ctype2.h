/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_ctype2.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/11 02:58:41 by rjw           #+#    #+#                 */
/*   Updated: 2025/03/04 20:14:16 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_CTYPE2_H
# define IS_CTYPE2_H

static inline int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
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