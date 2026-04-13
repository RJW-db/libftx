/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_ctype1_str.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/13 16:18:17 by rjw           #+#    #+#                 */
/*   Updated: 2025/04/13 17:41:50 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_CTYPE1_STR_H
# define IS_CTYPE1_STR_H
# include <stdbool.h>
# include <is_ctype1.h>

bool	str_check_all(const char *str, int (*func)(int));

static inline bool	str_isdigit(const char *str)
{
	return (str_check_all(str, ft_isdigit));
}

static inline bool	str_isalpha(const char *str)
{
	return (str_check_all(str, ft_isalpha));
}

static inline bool	str_isalnum(const char *str)
{
	return (str_check_all(str, ft_isalnum));
}

#endif
