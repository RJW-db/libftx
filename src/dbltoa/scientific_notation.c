/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scientific_notation.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/12 01:38:15 by rjw           #+#    #+#                 */
/*   Updated: 2025/03/15 01:28:57 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <dbltoa.h>

//	Static Function
static int16_t	calculate_exponent(double nbr);

void	scientific_notation(char *num, char *deno, int16_t *digitexpo, double value)
{
	char	digit[MAX_DBL_STR_LEN + 1];

	*digitexpo = calculate_exponent(value);
	if (*digitexpo > 0)
	{
		intialize_buff(digit);
		digit[MAX_DBL_STR_LEN - *digitexpo - 1] = '1';
		ft_multiply(deno, digit);
	}
	else if (*digitexpo < 0)
	{
		intialize_buff(digit);
		digit[MAX_DBL_STR_LEN + *digitexpo - 1] = '1';
		ft_multiply(num, digit);
	}
}

static int16_t	calculate_exponent(double nbr)
{
	int16_t	exponent;

	if (nbr < 0)
		nbr = -nbr;
	exponent = 0;
	if (nbr >= DECIMAL_NBR)
	{
		while (nbr >= DECIMAL_NBR)
		{
			nbr /= DECIMAL_NBR;
			++exponent;
		}
	}
	if (nbr != 0)
	{
		while (nbr < 1)
		{
			nbr *= DECIMAL_NBR;
			--exponent;
		}
	}
	return (exponent);
}
