/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_null_check.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:29:51 by rjw           #+#    #+#                 */
/*   Updated: 2025/05/09 15:16:18 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libftx.h>

bool	strs_ok(const char *s1, const char *s2)
{
	return (s1 != NULL && s2 != NULL);
}

bool	dpstr_ok(char **s1)
{
	return (s1 != NULL && *s1 != NULL);
}

bool	dpstrs_ok(char **s1, char **s2)
{
	return (dpstr_ok(s1) == true && dpstr_ok(s2) == true);
}
