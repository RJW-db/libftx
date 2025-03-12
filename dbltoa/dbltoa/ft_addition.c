/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_addition.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/12 02:12:12 by rjw           #+#    #+#                 */
/*   Updated: 2025/03/12 03:31:44 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dbltoa.h"

char	*ft_addition(char *s1, char *s2)
{
	int32_t	len;
	int32_t	carry;
	int32_t	i;
	int32_t	sum;
	
	s1 += (*s1 == '+');
	s2 += (*s2 == '+');
	carry = 0;
	len = ft_strlen(s1);
	i = len - 1;
	while (i >= 0)
	{
		sum = (s1[i] - '0') + (s2[i] - '0') + carry;
		carry = sum / 10;
		s1[i] = (sum % 10) + '0';
		--i;
	}
	if (carry > 0)
	{
		ft_memmove(s1 + 1, s1, len);
		s1[0] = carry + '0';
	}
	return (s1);
}
