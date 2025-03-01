/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   digit_counter.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:33:31 by rjw           #+#    #+#                 */
/*   Updated: 2025/03/01 02:23:00 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
	int64_t has max 19 + (-) = 20 digits,	-9,223,372,036,854,775,808
	uint64_t has max 20 digits,  18,446,744,073,709,551,615
*/
uint8_t	digit_counter(int64_t n, uint8_t base_len)
{
	uint8_t	count;

	count = (n <= 0);
	while (n != 0)
	{
		n /= base_len;
		++count;
	}
	return (count);
}

uint8_t	digit_ucounter(uint64_t n, uint8_t base_len)
{
	uint8_t	count;

	count = (n <= 0);
	while (n != 0)
	{
		n /= base_len;
		++count;
	}
	return (count);
}
