/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   itoa.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:31:43 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/08 17:44:16 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

//	Static Functions
static char	*integer_to_str(int sign, int i, int n);
static void	integer_to_buff(char *dst, int sign, int i, int n);

/*
	Used functions:
	- malloc
	- ft_strdup
*/
char	*ft_itoa(int n)
{
	int		sign;
	int		i;
	int		nn;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	sign = 0;
	if (n < 0)
	{
		sign = 1;
		n *= -1;
	}
	i = 1;
	nn = n;
	while (nn >= 10 || (n == 0 && i == 0))
	{
		nn /= 10;
		++i;
	}
	return (integer_to_str(sign, i, n));
}

void	itoa_buff(char *dst, int n)
{
	int		sign;
	int		i;
	int		nn;

	if (n == -2147483648)
	{
		cpy_str(dst, "-2147483648");
		return ;
	}
	sign = 0;
	if (n < 0)
	{
		sign = 1;
		n *= -1;
	}
	i = 1;
	nn = n;
	while (nn >= 10 || (n == 0 && i == 0))
	{
		nn /= 10;
		++i;
	}
	return (integer_to_buff(dst, sign, i, n));
}

static char	*integer_to_str(int sign, int i, int n)
{
	char	*ptr;

	ptr = malloc((i + 1 + sign) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ptr[i + sign] = '\0';
	while (i-- > 0)
	{
		ptr[i + sign] = n % 10 + '0';
		n /= 10;
	}
	if (sign)
		ptr[0] = '-';
	return (ptr);
}

static void	integer_to_buff(char *dst, int sign, int i, int n)
{
	dst[i + sign] = '\0';
	while (i-- > 0)
	{
		dst[i + sign] = n % 10 + '0';
		n /= 10;
	}
	if (sign)
		dst[0] = '-';
}
