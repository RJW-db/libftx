/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_to_sci_notation.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/03/07 17:31:23 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_dbltoa.h"

/* get_exponent_base10()
 * This function is to determine the order of magnitude (or exponent in scientific notation)
 * of the given number.
 * The function calculates the exponent of the number in base 10—essentially 
 * finding the power of ten needed to normalize the number into scientific notation.
 * where a number is written in the form:	
 *				𝑎×10^𝑏
 * Where:
 *		- 𝑎 is a single digit before the decimal point.
 *		- 𝑏 is the exponent (the value returned by this function).
 *
 *
 * if (nb < 0) :
 * 	- Convert nb to positive (if it's negative)
 * if (nb >= 10) :
 * 	- Divide nb by 10 repeatedly until it is less than 10.
 * if (nb < 1 && nb != 0) :
 * 	-  Multiply nb by 10 repeatedly until it reaches at least 1
 *
 *
 * Example:
 * nb = 29.45
 * 1) Check if nb is negative:
 *		29.45 is positive, so no change.
 * 2) Check if nb >= 10:
 * 		29.45 >= 10, 
 *		so we enter the while loop:
 *			First iteration: 
 *			nb = 29.45 / 10 = 2.945, intNum = 1
 *			nb < 10 now, so we exit the loop.
 *	3) Return intNum:
 *		The function returns 1.
 */
static int16_t	get_exponent_base10(double nb)
{
	int16_t	exponent;

	if (nb < 0)
		nb = -nb;
	exponent = 0;
	if (nb >= 10)
	{
		while (nb >= 10)
		{
			nb /= 10;
			++exponent;
		}
	}
	if (nb != 0)
	{
		while (nb < 1)
		{
			nb *= 10;
			--exponent;
		}
	}
	return (exponent);
}

/*
 * Converts a fraction (numerator/denominator) into scientific notation,  
 * ensuring that only one nonzero digit appears before the decimal point.
 * 
 * - If (*digitexpo > 0) : Number too large, needs scaling down
 * 	 Multiply the denominator by 10^digitexpo -> This shifts the decimal point left
 * 	 Example: 122.5 (convert to 1.225 × 10²)
 * 	
 * - If (*digitexpo < 0) : Number too small, needs scaling up
 * 	 Multiply the numerator by 10^|digitexpo| -> This shifts the decimal point right
 * 	 Example: 0.024 (convert to 2.4 × 10⁻²)
 */
void	convert_to_sci_notation(char *num, char *deno, int16_t *digitexpo, double ogNum)
{
	char	digit[BIG_INT + 1];

	// base-10 exponent needed to express ogNum in scientific notation
	*digitexpo = get_exponent_base10(ogNum);

	init_bigChar(digit);
	if (*digitexpo > 0)
	{
		digit[BIG_INT - *digitexpo - 1] = '1';
		ft_multiply(deno, digit);
	}
	else if (*digitexpo < 0)
	{
		digit[BIG_INT + *digitexpo - 1] = '1';
		ft_multiply(num, digit);
	}
}