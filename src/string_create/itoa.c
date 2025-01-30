/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   itoa.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:31:43 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/30 18:52:19 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

//	Static Functions
static char	*nbr_to_str(char *dst, bool sign, uint8_t i, int64_t n);

/*
	Used functions:
	- malloc
	- ft_strdup
*/
char	*ft_itoa(int n)
{
	bool	sign;
	int		i;
	int		remaining;
	char	*ptr;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	sign = false;
	if (n < 0)
	{
		sign = true;
		n *= -1;
	}
	i = 1;
	remaining = n;
	while (remaining >= 10)
	{
		remaining /= 10;
		++i;
	}
	ptr = malloc((i + 1 + sign) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	return (nbr_to_str(ptr, sign, i, n));
}

uint8_t	itoa_buff(char *dst, int64_t n)
{
	int64_t	remaining;
	uint8_t	i;
	bool	sign;

	if (n == -9223372036854775807LL-1)
	{
		return (cpy_str(dst, "-9223372036854775808"));
	}
	sign = 0;
	if (n < 0)
	{
		sign = 1;
		n *= -1;
	}
	i = 1;
	remaining = n;
	while (remaining >= 10)
	{
		remaining /= 10;
		++i;
	}
	nbr_to_str(dst, sign, i , n);
	return (i + sign);
}

static char	*nbr_to_str(char *dst, bool sign, uint8_t i, int64_t n)
{
	dst[i + sign] = '\0';
	while (i > 0)
	{
		--i;
		dst[i + sign] = n % 10 + '0';
		n /= 10;
	}
	if (sign == true)
		dst[0] = '-';
	return (dst);
}
