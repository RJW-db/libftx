/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   math_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/01 01:29:17 by rjw           #+#    #+#                 */
/*   Updated: 2025/03/17 20:21:02 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int8_t	sign(int n)
{
	if (n >= 0)
		return (n > 0);
	return (-1);
}

/**
 * check on double.
*/
int8_t	sign_d(double n)
{
	if (n >= 0)
		return (n > 0);
	return (-1);
}

uint64_t	abs_int64(int64_t n)
{
	if (n >= 0)
		return ((uint64_t)n);
	return ((uint64_t)((-(n + 1)) + 1));
}
