/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   itoa.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:31:43 by rjw           #+#    #+#                 */
/*   Updated: 2025/02/27 18:04:26 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>
#define DECIMAL_BASE "0123456789"

//	Static Functions
static char	*int_to_str(char *dst, uint8_t len, int64_t n, const char *base);
/*
	Used functions:
	- ft_strdup
	- malloc
	- ft_strdup
*/
char	*ft_itoa(int n)
{
	uint8_t	count;
	bool	sign;
	char	*dst;

	sign = (n < 0);
	count = digit_counter(n, 10);
	dst = malloc((count + TERM) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	if (sign == true)
		dst[0] = '-';
	return (int_to_str(dst + sign, count - sign, n, DECIMAL_BASE));
}

/*
	Used functions:
	- ft_strdup
	- malloc
	- ft_strdup
*/
char	*nbr_to_str(int64_t n)
{
	uint8_t	count;
	bool	sign;
	char	*dst;

	sign = (n < 0);
	count = digit_counter(n, 10);
	dst = malloc((count + TERM) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	if (sign == true)
		dst[0] = '-';
	return (int_to_str(dst + sign, count - sign, n, DECIMAL_BASE));
}

/*
	Used functions:
	- cpy_str
*/
uint8_t	nbr_to_buff(char *dst, int64_t n)
{
	uint8_t	count;
	bool	sign;

	sign = (n < 0);
	count = digit_counter(n, 10);
	if (sign == true)
		dst[0] = '-';
	int_to_str(dst + sign, count - sign, n, DECIMAL_BASE);
	return (count);
}

static char	*int_to_str(char *dst, uint8_t len, int64_t n, const char *base)
{
	const size_t	base_len = ft_strlen(base);
	const bool		sign = (n < 0);

	dst[len] = '\0';
	if (n == INT64_MIN)
	{
		if (ft_strncmp(DECIMAL_BASE, base, ft_strlen(DECIMAL_BASE) + 1) == 0)
		{
			dst[--len] = '8';
			n /= base_len; 
		}
		else
		{
			dst[--len] = base[-(n % base_len)];  // Store last digit
			n /= base_len;
			n = -n;  // Make it positive to continue safely
		}
	}
	
	if (n < 0)
		n = -n;
	while (len > 0)
	{
		dst[--len] = (n % base_len) + '0';
		n /= base_len;
	}
	return (dst - sign);
}

char	*itoa_base(int64_t n, const char *base)
{
	size_t	base_len;
	uint8_t	count;
	bool	sign;
	char	*dst;

	base_len = strlen_safe(base);
	if (base_len < 2)
		return (NULL);
	if (n == 0)
		return (ft_strdup((char [2]){base[0], '\0'}));
	sign = (n < 0);
	count = digit_counter(n, base_len);
	printf("%d\n", count + TERM);
	dst = malloc((count + TERM) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	if (sign == true)
		dst[0] = '-';
	return (int_to_str(dst + sign, count - sign, n, base));
}


// static char	*int_to_str_base(char *dst, bool sign, uint8_t count, unsigned long num, const char *base)
// {
// 	size_t	base_len = ft_strlen(base);

// 	dst[count + sign] = '\0';
// 	while (count > 0)
// 	{
// 		--count;
// 		dst[count + sign] = base[num % base_len];
// 		num /= base_len;
// 	}
// 	if (sign)
// 		dst[0] = '-';
// 	return (dst);
// }
