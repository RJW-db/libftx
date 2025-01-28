/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   digit_counter.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:33:31 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/11 21:25:54 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
	int64_t has max 19 + (-) = 20 digits,	-9,223,372,036,854,775,808
	uint64_t has max 20 digits,  18,446,744,073,709,551,615
*/
uint8_t	digit_counter(int64_t n)
{
	uint8_t	count;

	if (n == 0)
		return (1);
	count = 0;
	if (n < 0)
		++count;
	while (n != 0)
	{
		n /= 10;
		++count;
	}
	return (count);
}
