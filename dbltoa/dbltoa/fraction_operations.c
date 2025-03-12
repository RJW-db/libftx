/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fraction_operations.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/12 02:52:56 by rjw           #+#    #+#                 */
/*   Updated: 2025/03/12 03:07:08 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dbltoa.h"

/*
 * What Do numerator and denominator Represent?
 * numerator: Stores the numerator of the fraction representing the floating-point number.
 * denominator: Stores the denominator, which helps express the floating-point value as a fraction.
 * In floating-point representation, a number like 3.14159 can be expressed as:
 * 
 * 								314159
 * 								------
 * 								100000
 * 
 * This fraction-based approach allows for precise decimal representation, 
 * avoiding precision issues that arise with direct binary floating-point conversion.
 * 	1. Avoids Floating-Point Precision Issues
 * 		- Representing the number as a fraction first ensures more accurate decimal conversion.
 * 	2. Handles Large Numbers
 * 		- Standard double values are limited in precision.
 * 		- Using big integers (MAX_DBL_STR_LEN) allows for higher precision conversions, making this method ideal for scientific or financial applications.
 * 
 * 
 * The function converts the mantissa into a big integer and scales it by 2^exponent
 * Steps:
 * 		1):
 * 			Convert the mantissa to a String
 * 		2): (expo > 0)
 * 			Places the mantissa value at the end of numerator* (shifting it right)
 * 			Calculates mantissa * 2^exponent
 * 		3): else
 * 			(Exponent is Zero or Negative) -> Simply copies the mantissa string into the numerator*.
 * 		4):
 */
char	*populate_numerator(char *num_str, uint64_t mant, int16_t expo)
{
	char	mant_bits[DBL_MANT_BITS + 1];
	char	exp_str[MAX_DBL_STR_LEN + 1];
	size_t	mant_len;

	mant_len = int64_base(mant, DECIMAL_BASE, mant_bits, sizeof(mant_bits));
	if (mant_len >= MAX_DBL_STR_LEN)
		return (NULL);
	if (expo > 0)
	{	
		cpy_str(num_str + MAX_DBL_STR_LEN - mant_len, mant_bits);
		intialize_buff(exp_str);
		exp_str[MAX_DBL_STR_LEN - 1] = '2';
		if (pow2(exp_str, expo) == NULL)
			return (NULL);
		ft_multiply(num_str, exp_str);
	}
	else
		cpy_str(num_str + MAX_DBL_STR_LEN - mant_len, mant_bits);
	return (num_str);
}

/*
 * This function initializes the denominator
 * 
 * If the exponent is Positive
 * 		The denominator is just 1, meaning the fraction is already in its final form
 * If the value != 0
 * 		Exponent is Negative -> denominator = 2^−exponent
 * 		Calculates 2^−exponent
 * else Floating-point number is Zero
 *		Sets denominator to 1, avoiding unnecessary calculations.
 * 
 * Example:
 * populate_denominator(deno, exponent, 6.25)
 * 		-exponent > 0, so deno = 1
 * Final Fraction
 * 		4004
 * 		---- = 6.25
 * 		  1
 * 
 * populate_numerator handles the mantissa and scales it based on the exponent.
 * populate_denominator sets the denominator, either as 1 (for positive exponents) or as 2^−exponent (for negative exponents).
 * Together, they allow a floating-point number to be represented as a fraction.
 */
char	*populate_denominator(char *denom_str, int16_t expo, double value)
{
	intialize_buff(denom_str);
	if (expo <= 0 && value != 0) 
	{
		denom_str[MAX_DBL_STR_LEN - 1] = '2';
		if (pow2(denom_str, -expo) == NULL)
			return (NULL);
		return (denom_str);
	}
	denom_str[MAX_DBL_STR_LEN - 1] = '1';
	return (denom_str);
}

/*
 * This function is designed to calculate powers of 2 using a big integer representation stored in a string (exp_str). 
 * It does so by repeatedly adding the current value to itself, essentially doubling it, to simulate exponentiation.
 */
char	*pow2(char *exp_str, int64_t exponent)
{
	char	pow2[MAX_DBL_STR_LEN + 1];

	if (exponent != 0)
	{
		while (exponent > 1)
		{
			cpy_str(pow2, exp_str);
			ft_addition(exp_str, pow2);
			--exponent;
		}
	}
	else
	{
		intialize_buff(exp_str);
		exp_str[MAX_DBL_STR_LEN - 1] = '1';
	}
	return (exp_str);
}
