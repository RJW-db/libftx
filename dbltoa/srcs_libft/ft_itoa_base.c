/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_base.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/02/19 16:20:27 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_dbltoa.h"

// This function reverses the characters in a given string str.
static void	str_reverse(char *str)
{
	int		i;
	int		j;
	char	temp;

	i = 0;
	j = ft_strlen(str) - 1;
	while (i < j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}

/* ft_itoa_base()
 * This function converts a given number (nbr) into a string 
 * representing that number in a specified base.
 * 
 * If the number is negative, it stores its absolute value in num 
 * and will add a - sign at the end if necessary.
 * 
 * It checks if the base is valid (i.e., has at least two characters). 
 * Because a number system with a base less than 2 isn't valid.
 * 
 * The remainder of num when divided by the base gives the correct 
 * character (digit) for the current place value.
 * These characters are placed into the buffer array.
 * 
 * The characters were added to the buffer in reverse order, 
 * so str_reverse() reverse the buffer.
 */
char	*ft_itoa_base(long nbr, const char *base)
{
	char			buffer[65];
	int				i;
	unsigned long	num;

	i = 0;
	if (nbr < 0)
		num = -nbr;
	else
		num = nbr;
	if (ft_strlen(base) < 2)
		return (NULL);
	if (nbr == 0)
		return (ft_strdup("0"));
	while (num)
	{
		buffer[i++] = base[num % ft_strlen(base)];
		num /= ft_strlen(base);
	}
	if (nbr < 0)
		buffer[i++] = '-';
	buffer[i] = '\0';
	str_reverse(buffer);
	return (ft_strdup(buffer));
}
