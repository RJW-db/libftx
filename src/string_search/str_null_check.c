/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_null_check.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:29:51 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/08 17:44:16 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
	true  if exists
	false if NULL
*/
bool	strs_ok(t_cchr *s1, t_cchr *s2)
{
	return (!(s1 == NULL || s2 == NULL));
}

/*
	true  if exists
	false if NULL
	dp = double pointer
*/
bool	dpstr_ok(char **s1)
{
	return (!(s1 == NULL || *s1 == NULL));
}

/*
	1 if exists
	0 if NULL
	dp = double pointer
*/
bool	dpstrs_ok(char **s1, char **s2)
{
	return (dpstr_ok(s1) == true && dpstr_ok(s2) == true);
}
