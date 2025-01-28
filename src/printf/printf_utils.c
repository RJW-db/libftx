/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printf_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/15 14:42:32 by rde-brui      #+#    #+#                 */
/*   Updated: 2025/01/13 17:45:43 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

//	negative is 64 bit for overflow
int32_t	signed_decimal_base(char *str, int32_t n)
{
	const char	store[12] = {0};
	const char	*base = "0123456789";
	char		*number;
	int64_t		negative;

	if (n == 0)
	{
		str[0] = '0';
		return (1);
	}
	negative = n;
	if (negative < 0)
		negative *= -1;
	number = &((char *)store)[11];
	while (negative != 0)
	{
		*(--number) = base[negative % 10];
		negative /= 10;
	}
	if (n < 0)
		*(--number) = '-';
	return (move_str(str, number));
}

int32_t	move_str(char *dst, t_cchr *src)
{
	int8_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		++i;
	}
	return (i);
}

int32_t	move_num_src(char *dst, t_cchr *src, int32_t num)
{
	int8_t	i;

	i = 0;
	while (src[i] != '\0' && num > 0)
	{
		dst[i] = src[i];
		++i;
		--num;
	}
	return (i);
}

int32_t	move_num_chr(char *str, t_cchr c, int32_t n)
{
	int8_t	i;

	i = 0;
	while (i < n)
	{
		str[i] = c;
		++i;
	}
	return (i);
}
