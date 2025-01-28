/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sign.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:33:02 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/08 17:44:16 by rde-brui      ########   odam.nl         */
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
