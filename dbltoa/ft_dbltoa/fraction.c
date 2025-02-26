/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fraction.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/02/26 19:13:17 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_dbltoa.h"

/*
 * IEEE-754 Double Precision Format:
 * SEEEEEEE EEEEMMMM MMMMMMMM MMMMMMMM MMMMMMMM MMMMMMMM MMMMMMMM MMMMMMMM
 * ↑↑           ↑
 * ||           └── Mantissa (52 bits) → `mantissa`
 * |└── Exponent (11 bits) → `exponent`
 * └── Sign bit (1 bit)
 * 
 * Sign Bit (1 bit): 0 for positive, 1 for negative.
 * Exponent (11 bits): Stores the power of 2 (biased by 1023).
 * Mantissa (52 bits): Stores the fractional part.
 *
 *		------------------------------------------------
 *
 * What the function does?
 *	- Extracts the 11-bit exponent from the binary string.
 *	- Extracts the 52-bit mantissa from the binary string.
 *	- Converts exponent and mantissa to decimal.
 *	- Adjusts for normalized/denormalized numbers.
 *
 *		------------------------------------------------
 *
 * Adjusts the exponent bias?
 * 	IEEE-754 exponent bias is 1023.
 * 	Denormalized numbers (exponent 0) use -1074 instead of -1075.
 * 	Normalized numbers subtract 1075 to get the actual exponent.
 *
 * 	Example:
 * 	| Binary 	    | Exponent | Decimal (Biased) | Adjusted (Actual Exponent) |
 * 	| "10000000000" |	1024   | 	  1075		  |	   1024 - 1075   =   -51   |
 *	| "01111111111"	|	1023   |	  1075		  |	   1023 - 1075   =   -52   |
 * 	| "00000000000"	|	0	   | 	  1075		  |	   0 	- 1074   =   -1074 |
 *
 *
 * Why 1074 and 1075?
 * 	{
 * 		// Adjusts the exponent bias
 * 		if (*exponent == 0)
 *			*exponent -= 1074;
 *		else
 *			*exponent -= 1075;
 * 	 }
 * 	- The exponent is stored with a bias of 1023.
 * 	- The smallest exponent for a normalized number is -1022.
 * 	- If the exponent is not zero, we adjust it using:
 *				actual exponent = stored exponent − 1023 − 1 = stored exponent − 1075
 *	- When the exponent is all zeros (00000000000), the number is denormalized.
 *	- The actual exponent for denormals is always -1022 (minimum exponent) - 52 (mantissa shift):
 *				− 1022 − 52 = − 1074
 * 	- This is why for denormalized numbers, we use:
 *				exponent -= 1074;
 * 	- For normalized numbers, we use:
 *				exponent -= 1075;
 *				Because the implicit leading 1 bit in the mantissa shifts the exponent by an extra 1.
 * 
 *		------------------------------------------------
 *
 * Adjusts the mantissa bias?
 * 	if (ft_atoi(expoTmp) && (ft_atoi(expoStr) - 1075) != 972)
 *     			*mantissa += (1UL << 52); 	// Adds 2^52 to restore the implicit 1
 * 	If exponent is NOT 972, add 2^52 to the mantissa. (Bit-shift 52 to left)
 * 	This accounts for the implicit leading 1 in normalized numbers.
 *	In other words:
 *		If the exponent is not zero & not 972, the number is normalized, 
 *		and implicit leading 1 is added (mantissa becomes 1.xxxxx instead of 0.xxxxx).
 *
 *		Example:
 *		| Mantissa Bits	| Decimal Mantissa | Adjusted Mantissa (with 2^52)	   |
 *		| "100100..."	| 31897010349248   | 31897010349248 + 4503599627370496 |
 *
 * Why is 972 used?
 * 	The 972 is related to special cases of floating-point numbers 
 * 	like Infinity (Inf) and NaN (Not-a-Number).
 * 
 * 	Special IEEE-754 Exponent Values
 * 	- The largest possible exponent in 11-bit storage is 2047 (11111111111 in binary).
 * 	- The largest normal exponent is 1023.
 * 	- A value of 1024 could mean infinity (Inf).
 * 	- Exponent value 972 is an indicator of Inf or NaN.
 * 
 * 	Why Check if (exponent - 1075) != 972?
 * 	- If the biased exponent is 2047, the number is Inf or NaN.
 * 	- To detect this, we check:
 * 		if (exponent - 1075 != 972)
 * 		- When exponent - 1075 == 972 → It is Inf or NaN.
 * 		- Otherwise, it is a regular number.
 * 
 * Steps:
 * 		1):
 * 			expoTmp : Extracts 11 bits of the exponent (starts at 1 to skip the sign bit)
 * 			mantTmp : Extracts mantissa bits (starts at 12, because exponent goes till 11 bits)
 * 		2):
 * 			Converts binary exponent to expoStr/mantStr (exponent "10000000000" → decimal "1024")
 * 		3):
 * 			Converts string to int (string "1024" to integer 1024)
 * 		4):
 * 			Adjusts the exponent bias
 * 			Normlize number (if not zerro)
 * 
 */
static void get_exponent_mantissa(int *exponent, unsigned long *mantissa, char *strbits)
{
	char	*expoTmp;
	char	*expoStr;
	char	*mantTmp;
	char	*mantStr;

	if (!(expoTmp = ft_substr(strbits, 1, 11)) || !(mantTmp = ft_substr(strbits, 12, 52)))
		return ;
	
	if (!(expoStr = convert_binary_to_decimal(expoTmp, "01", "0123456789")))
	{
        free(expoTmp);
        free(mantTmp);
        return;
    }
	if (!(mantStr = convert_binary_to_decimal(mantTmp, "01", "0123456789")))
	{
        free(expoTmp);
        free(mantTmp);
        free(expoStr);
        return;
    }
	
	*exponent = ft_atoi(expoStr);
	*mantissa = ft_atoi(mantStr);
	
	// Adjusts the exponent bias
	if (*exponent == 0) 
		*exponent -= 1074;
	else
		*exponent -= 1075;

	// Normlize number (if not zerro)
	if (ft_atoi(expoTmp) && (ft_atoi(expoStr) - 1075) != 972)
		*mantissa += (1UL << 52);

	free(expoStr);
	free(mantStr);
	free(expoTmp);
	free(mantTmp);
}

/*
 * This function is designed to calculate powers of 2 using a big integer representation stored in a string (bigint). 
 * It does so by repeatedly adding the current value to itself, essentially doubling it, to simulate exponentiation.
 */
static char	*pow_table2(char *bigint, unsigned long exponent)
{
	char	pow2[BIG_INT + 1];

	if (!exponent)
	{
		init_bigChar(bigint);
		bigint[BIG_INT - 1] = '1';
	}
	else
	{
		while (exponent-- > 1)
		{
			ft_strlcpy(pow2, bigint, BIG_INT + 1);
			if (!ft_add(bigint, pow2))
				return (NULL);
		}
	}
	return (bigint);
}

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
 * 		- Using big integers (BIG_INT) allows for higher precision conversions, making this method ideal for scientific or financial applications.
 * 
 * 
 * The function converts the mantissa into a big integer and scales it by 2^exponent
 * Steps:
 * 		1):
 * 			Convert the mantissa to a String
 * 		2): (expoValue > 0)
 * 			Places the mantissa value at the end of numerator* (shifting it right)
 * 			Calculates mantissa * 2^exponent
 * 		3): else
 * 			(Exponent is Zero or Negative) -> Simply copies the mantissa string into the numerator*.
 * 		4):
 */
static char	*fill_numerator(char *numerator, unsigned long mantValue, long expoValue)
{
	char	*mantissa;
	char	exponent[BIG_INT + 1];

	if (!(mantissa = ft_itoa(mantValue)))
		return (NULL);
	
	if (ft_strlen(mantissa) >= BIG_INT)
		return (NULL);
	if (expoValue > 0)
	{	
		ft_strlcpy(numerator + BIG_INT - ft_strlen(mantissa), mantissa, ft_strlen(mantissa) + 1);
		init_bigChar(exponent);

		exponent[BIG_INT - 1] = '2';
		if (!pow_table2(exponent, expoValue))
			return (NULL);
		ft_multi(numerator, exponent);
	}
	else
		ft_strlcpy(numerator + BIG_INT - ft_strlen(mantissa), mantissa, ft_strlen(mantissa) + 1);

	free(mantissa);
	return (numerator);
}

/*
 * This function initializes the denominator
 * 
 * If the exponent is Positive
 * 		The denominator is just 1, meaning the fraction is already in its final form
 * If the ogNum != 0
 * 		Exponent is Negative -> denominator = 2^−exponent
 * 		Calculates 2^−exponent
 * else Floating-point number is Zero
 *		Sets denominator to 1, avoiding unnecessary calculations.
 * 
 * Example:
 * fill_denominator(deno, exponent, 6.25)
 * 		-exponent > 0, so deno = 1
 * Final Fraction
 * 		4004
 * 		---- = 6.25
 * 		  1
 * 
 * fill_numerator handles the mantissa and scales it based on the exponent.
 * fill_denominator sets the denominator, either as 1 (for positive exponents) or as 2^−exponent (for negative exponents).
 * Together, they allow a floating-point number to be represented as a fraction.
 */
static char			*fill_denominator(char *denominator, long exponent, double ogNum)
{
	if (exponent > 0)
	{
		init_bigChar(denominator);
		denominator[BIG_INT - 1] = '1';
	}
	else if (ogNum != 0) 
	{
		init_bigChar(denominator);
		denominator[BIG_INT - 1] = '2';
		if (!pow_table2(denominator, -exponent))
			return (NULL);
	}
	else 
	{
		init_bigChar(denominator);
		denominator[BIG_INT - 1] = '1';
	}
	return (denominator);
}

/*
 * IEEE-754 Double Precision Format:
 * SEEEEEEE EEEEMMMM MMMMMMMM MMMMMMMM MMMMMMMM MMMMMMMM MMMMMMMM MMMMMMMM
 * ↑↑           ↑
 * ||           └── Mantissa (52 bits) → `mantissa`
 * |└── Exponent (11 bits) → `exponent`
 * └── Sign bit (1 bit)
 * 
 * Sign Bit (1 bit): 0 for positive, 1 for negative.
 * Exponent (11 bits): Stores the power of 2 (biased by 1023).
 * Mantissa (52 bits): Stores the fractional part.
 * 
 * 		------------------------------------------------
 * 
 * If exponent == 972, this means dbl is either:
 * Infinity (+∞ or -∞)
 * NaN (Not a Number -> 0.0 / 0.0)
 * Calls error_inf() to return a string like "inf" or "nan".
 * TEST CASES:
 * 	- double test = 1.0 / 0.0; // Division by zero creates +∞
 * 	- double test = -1.0 / 0.0; // Negative division by zero creates -∞
 * 	- double test = 0.0 / 0.0; // 0 divided by 0 produces NaN
 * 
 * Why 972?
 * In IEEE-754:
 * 	- The exponent is stored as biased (actual_exp + 1023).
 * 	- Infinity and NaN have an exponent of all 1s (2047 in decimal).
 * 		S1111111 1111MMMM MMMMMMMM MMMMMMMM MMMMMMMM MMMMMMMM MMMMMMMM MMMMMMMM
 * 	- get_exponent_mantissa() subtracts the bias (1023), so we get 972 (2047 - 1075).
 */
char	*convert_to_fraction(double ogNum, char *nume, char *denom, bool *n_flag)
{
	int				exponent;	// exponent
	unsigned long	mantissa; 	// mantissa
	char			*strbits; 	// store the bitstring representation of ogNum

	// Converts the raw memory of ogNum into a string of bits (holds the 64-bit IEEE-754 representation)
	strbits = str_bits(&ogNum, sizeof(ogNum));
	if (strbits == NULL)
		return (NULL);
	if (strbits[0] == '0')
		*n_flag = false;

	// Extract the Exponent and Mantissa
	get_exponent_mantissa(&exponent, &mantissa, strbits);
	if (exponent == 972)
	{
		// If exponent is +-Infinity and NaN return error
		free(strbits);
		return (error_inf(ogNum, mantissa));
	}

	// Converts into a char numerator/denominator
	fill_numerator(nume, mantissa, exponent);
	fill_denominator(denom, exponent, ogNum);

	free(strbits);
	return (NULL);
}
