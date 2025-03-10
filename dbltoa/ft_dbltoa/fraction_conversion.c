/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fraction_conversion.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/03/10 02:54:53 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_dbltoa.h"

// IEEE 754 representation of -NAN
#define NEGATIVE_NAN_BITS 0xFFF8000000000000
#define DBL_EXP_BITS 11
#define DBL_EXP_DECIMAL_DIGITS 5
#define DBL_MANT_BITS 52
// 1023 (IEEE 754 exponent bias) + 52 (mantissa bit count)
#define DBL_EXP_NORMAL_BIAS 1075
// 1023 (IEEE 754 exponent bias) + 52 - 1 (subnormal adjustment)
#define DBL_EXP_SUBNORMAL_BIAS 1074
// 2047 (max exponent value in IEEE 754) - 1075 (DBL_EXP_NORMAL_BIAS)
#define DBL_EXP_MAX 972

typedef union	u_double_bitcast
{
	double	d;
	int64_t	i;
}	t_bitcast;

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
 * 	if (atoi64(exp_bits) && (atoi64(exp_str) - 1075) != 972)
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
 * 			exp_bits : Extracts 11 bits of the exponent (starts at 1 to skip the sign bit)
 * 			mant_bits : Extracts mantissa bits (starts at 12, because exponent goes till 11 bits)
 * 		2):
 * 			Converts binary exponent to exp_str/mant_str (exponent "10000000000" → decimal "1024")
 * 		3):
 * 			Converts string to int (string "1024" to integer 1024)
 * 		4):
 * 			Adjusts the exponent bias
 * 			Normlize number (if not zerro)
 * 
 */
static void extract_expo_mant(int16_t *exponent, uint64_t *mant, char *strbits)
{
	char	exp_bits[DBL_EXP_BITS + 1];
	char	exp_str[DBL_EXP_DECIMAL_DIGITS + 1];
	char	mant_bits[DBL_MANT_BITS + 1];
	char	mant_str[DBL_MANT_DECIMAL_DIGITS + 1];

	extract_substr(strbits, 1, DBL_EXP_BITS, exp_bits);
	extract_substr(strbits, DBL_EXP_BITS + 1, DBL_MANT_BITS, mant_bits);
	binary_to_decimal(exp_bits, exp_str, sizeof(exp_str));
	binary_to_decimal(mant_bits, mant_str, sizeof(mant_str));
	*exponent = atoi64(exp_str);
	*mant = atoi64(mant_str);
	if (*exponent != 0) 
		*exponent -= DBL_EXP_NORMAL_BIAS;
	else
		*exponent -= DBL_EXP_SUBNORMAL_BIAS;
	if (atoi64(exp_bits) > 0 &&
		(atoi64(exp_str) - DBL_EXP_NORMAL_BIAS) != DBL_EXP_MAX)
	{
		*mant += (1UL << DBL_MANT_BITS);
	}
}

void	ft_addition(char *s1, char *s2)
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
}

/*
 * This function is designed to calculate powers of 2 using a big integer representation stored in a string (bigint). 
 * It does so by repeatedly adding the current value to itself, essentially doubling it, to simulate exponentiation.
 */
// static char	*pow2(char *bigint, uint64_t exponent)
static char	*pow2(char *bigint, int64_t exponent)
{
	char	pow2[BIG_INT + 1];

	if (exponent != 0)
	{
		while (exponent > 1)
		{
			cpy_str(pow2, bigint);
			ft_addition(bigint, pow2);
			--exponent;
		}
	}
	else
	{
		// TODO
		// puts("\nEDGECASE, only 339 of tester: subnormal_to_max_tests");
		intialize_string(bigint);
		bigint[BIG_INT - 1] = '1';
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
 * 		2): (expo > 0)
 * 			Places the mantissa value at the end of numerator* (shifting it right)
 * 			Calculates mantissa * 2^exponent
 * 		3): else
 * 			(Exponent is Zero or Negative) -> Simply copies the mantissa string into the numerator*.
 * 		4):
 */
static char	*populate_numerator(char *num_str, uint64_t mant, int16_t expo)
{
	char	mant_bits[DBL_MANT_BITS + 1];
	char	exp_str[BIG_INT + 1];
	size_t	mant_len;

	mant_len = int64_base(mant, DECIMAL_BASE, mant_bits, sizeof(mant_bits));
	if (mant_len >= BIG_INT)
		return (NULL);
	if (expo > 0)
	{	
		cpy_str(num_str + BIG_INT - mant_len, mant_bits);
		intialize_string(exp_str);
		exp_str[BIG_INT - 1] = '2';
		if (pow2(exp_str, expo) == NULL)
			return (NULL);
		ft_multiply(num_str, exp_str);
	}
	else
		cpy_str(num_str + BIG_INT - mant_len, mant_bits);
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
static char	*populate_denominator(char *denom_str, int16_t expo, double value)
{
	intialize_string(denom_str);
	if (expo <= 0 && value != 0) 
	{
		denom_str[BIG_INT - 1] = '2';
		if (pow2(denom_str, -expo) == NULL)
			return (NULL);
		return (denom_str);
	}
	denom_str[BIG_INT - 1] = '1';
	return (denom_str);
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
 * Calls special_value() to return a string like "inf" or "nan".
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
bool	fraction_conversion(double value, t_dbl *strings, bool *is_neg)
{
	char		bit_representation[DBL_BIT_COUNT + 1];
	int16_t		exp_value;
	uint64_t	mantissa_value;
	t_bitcast	cast;

	cast.d = value;
	double_to_bits(cast.i, bit_representation);

	if (bit_representation[0] == '0' && cast.i != (int64_t)NEGATIVE_NAN_BITS)
		*is_neg = false;

	extract_expo_mant(&exp_value, &mantissa_value, bit_representation);
	if (exp_value == DBL_EXP_MAX)
	{
		special_value(strings, value, mantissa_value, *is_neg);
		return (false);
	}
	populate_numerator(strings->s1, mantissa_value, exp_value);
	populate_denominator(strings->s2, exp_value, value);
	return (true);
}
