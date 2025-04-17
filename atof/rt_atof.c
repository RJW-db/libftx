#include <stdio.h>
#include <stdbool.h>
#include <float.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include <libft.h>
#include <limits.h>

double	ft_fabs(double x)
{
	double result;
	uint64_t bits;

	// Reinterpret the double as a 64-bit unsigned integer
	ft_memcpy(&bits, &x, sizeof(bits)); // Safely copy the double bits into an integer
	// Clear the sign bit (most significant bit) for a 64-bit double
	bits &= 0x7FFFFFFFFFFFFFFF;
	// Reinterpret the modified bits back as a double
	ft_memcpy(&result, &bits, sizeof(result)); // Safely copy the bits back into a double
	return result;
}


float	ft_fabsf(float x)
{
	float		result;
	uint32_t	bits;

	// Reinterpret the float as a 32-bit unsigned integer
	ft_memcpy(&bits, &x, sizeof(bits)); // Safely copy the float bits into an integer
	// Clear the sign bit (most significant bit)
	bits &= 0x7FFFFFFF;
	// Reinterpret the modified bits back as a float
	ft_memcpy(&result, &bits, sizeof(result)); // Safely copy the bits back into a float
	return (result);
}

typedef struct	s_stod
{
	const char	*str;
	float	num;
	int		i;
	bool	*overflow;
}	t_atof;


// Skip whitespace and process sign
int process_sign(const char *str, int *sign)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		++i;
	if (str[i] == '-')
	{
		*sign = -1;
		++i;
	}
	else if (str[i] == '+')
		++i;
	return (i);
}

// Process integer part of the number
float process_integer(t_atof *atof, const char *str, int i)
{
	float	num;

	num = 0.0F;
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		if (num > (FLT_MAX - (str[i] - '0')) / 10.0F)
		{
			*atof->overflow = true;
			atof->i = i;	// this should be removed, because it's not gonna be used anymore
			atof->num = FLT_MAX;
			return (FLT_MAX);
		}
		num = (num * 10.0F) + (str[i] - '0');
		++i;
	}
	atof->i = i;
	atof->num = num;
	return (num);
}

// Process fractional part
float process_fraction(t_atof *atof, const char *str, int i, float num)
{
	float	digit_value;
	float	scale;

	scale = 0.1F;
	if (str[i] == '.')
	{
		++i;
		while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
		{
			digit_value = (str[i++] - '0') * scale;
			if (num > FLT_MAX - digit_value)
			{
				*atof->overflow = true;
				atof->i = i;	// this should be removed, because it's not gonna be used anymore
				atof->num = FLT_MAX;
				return (FLT_MAX);
			}
			num += digit_value;
			scale *= 0.1F;
		}
	}
	atof->i = i;
	atof->num = num;
	return (num);
}


// Helper function to parse the exponent sign
static int parse_exponent_sign(t_atof *atof)
{
	int	exp_sign;

	exp_sign = 1;
	if (atof->str[atof->i] == '-')
	{
		exp_sign = -1;
		++atof->i;
	} 
	else if (atof->str[atof->i] == '+')
		++atof->i;
	return (exp_sign);
}

// Helper function to parse the exponent value
static int parse_exponent_value(t_atof *atof, const char *str)
{
	int	exp;

	exp = 0;
	while (str[atof->i] != '\0' && ft_isdigit(str[atof->i]) == true)
	{
		if (exp > (INT_MAX - (str[atof->i] - '0')) / 10)
		{
			*atof->overflow = true;
			return (INT_MAX);
		}
		exp = exp * 10 + (str[atof->i] - '0');
		++atof->i;
	}
	return (exp);
}

// Helper function to handle positive exponents
static float apply_positive_exponent(float num, int exp, bool *overflow)
{
	while (exp > 0)
	{
		if (num > FLT_MAX / 10.0F)
		{
			*overflow = true;
			return (FLT_MAX);
		}
		num *= 10.0F;
		--exp;
	}
	return (num);
}

// Helper function to handle negative exponents
static float apply_negative_exponent(float num, int exp, bool *overflow)
{
	while (exp < 0)
	{
		num *= 0.1F;
		if (num != 0.0F && ft_fabsf(num) < FLT_MIN)
		{
			*overflow = true;
			return (0.0F);
		}
		++exp;
	}
	return (num);
}

// Main process_exponent function
float process_exponent(t_atof *atof, const char *str, int i)
{
	int	exp_sign;
	int	exp;

	if ((str[i] == 'e' || str[i] == 'E') && str[i + 1] != '\0')
	{
		++atof->i;
		exp_sign = parse_exponent_sign(atof);
		exp = parse_exponent_value(atof, str);
		if (*atof->overflow == true)
		{
			if (exp_sign > 0)
				atof->num = FLT_MAX;
			else
				atof->num = 0.0F;
			// return ;
			return (atof->num);
		}
		exp *= exp_sign;
		if (exp > 0)
			atof->num = apply_positive_exponent(atof->num, exp, atof->overflow);
		else if (exp < 0)
			atof->num = apply_negative_exponent(atof->num, exp, atof->overflow);
	}
	return (atof->num);
}

#include <strings.h>
// Check if string is a special floating point value like "inf" or "nan"
static bool is_special_float(const char *str, float *result)
{
	if (strcasecmp(str, "inf") == 0 || strcasecmp(str, "infinity") == 0)
	{
		*result = INFINITY;
		return (true);
	}
	if (strcasecmp(str, "-inf") == 0 || strcasecmp(str, "-infinity") == 0)
	{
		*result = -INFINITY;
		return (true);
	}
	if (strcasecmp(str, "nan") == 0 || strcasecmp(str, "-nan") == 0)
	{
		*result = NAN;
		return (true);
	}
	return (false);
}

/**
 * @brief Parses the exponent part of a string, including sign and numeric value.
 * @param str The input string.
 * @param i Pointer to the current index in the string (updated during parsing).
 * @return The parsed exponent value, or INT_MAX/INT_MIN in case of overflow.
 */
static int parse_exponent(const char *str, int i)
{
	int exp_sign;
	int exp_val;

	exp_sign = 1;
	exp_val = 0;
	if (str[i] == '-')
	{
		exp_sign = -1;
		++i;
	}
	else if (str[i] == '+')
		++i;
	while (str[i] != '\0' && ft_isdigit(str[i]) == true)
	{
		if (exp_val > (INT_MAX - (str[i] - '0')) / 10)
		{
			if (exp_sign > 0)
				return (INT_MAX);
			return (INT_MIN);
		}
		exp_val = exp_val * 10 + (str[i] - '0');
		++i;
	}
	return (exp_val * exp_sign);
}

// Extract exponent value from string
static int extract_exp_value(const char *str, bool *found_exp)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 'e' || str[i] == 'E')
		{
			*found_exp = true;
			return (parse_exponent(str, ++i));
		}
		++i;
	}
	return (0);
}

// Extract mantissa for high-precision checking
static float extract_mantissa(const char *str)
{
	float	mantissa;
	float	frac_scale;
	int		idx;

	mantissa = 0.0F;
	frac_scale = 0.1F;
	idx = 0;
	while (str[idx] == ' ' || str[idx] == '\t')
		++idx;
	if (str[idx] == '-' || str[idx] == '+')
		++idx;
	while (str[idx] != '\0' && str[idx] >= '0' && str[idx] <= '9')
		mantissa = mantissa * 10.0f + (str[idx++] - '0');
	if (str[idx] == '.')
	{
		++idx;
		while (str[idx] != '\0' && str[idx] >= '0' && str[idx] <= '9')
		{
			mantissa += (str[idx] - '0') * frac_scale;
			frac_scale *= 0.1f;
			++idx;
		}
	}
	return (mantissa);
}

// Check if number is near FLT_MAX and potentially overflows
static bool check_near_max(t_atof *atof)
{
	bool	found_exp;
	float	mantissa;
	int		exp_val;

	found_exp = false;
	mantissa = 0.0F;
	exp_val = 0;
	if (atof->num <= FLT_MAX * 0.999999F)
		return (false);
	exp_val = extract_exp_value(atof->str, &found_exp);
	mantissa = extract_mantissa(atof->str);
	if (exp_val > 38 || (exp_val == 38 && mantissa > 3.4028234F))
		return (true);
	return (false);
}

// Handle overflow based on sign
static float handle_overflow(int sign, float num)
{
	if (num == 0.0F)
		return (0.0F);
	if (sign > 0)
		return (FLT_MAX);
	return (-FLT_MAX);
}

// Process the first part of numeric parsing
static float process_first_part(t_atof *atof, int sign)
{
	atof->num = process_integer(atof, atof->str, atof->i);
	if (*atof->overflow == true)
	{
		if (sign > 0)
			return (FLT_MAX);
		return (-FLT_MAX);
	}
	atof->num = process_fraction(atof, atof->str, atof->i, atof->num);
	if (*atof->overflow == true)
	{
		if (sign > 0)
			return (FLT_MAX);
		return (-FLT_MAX);
	}
	return (atof->num);
}

// Process the second part of numeric parsing
static float process_second_part(t_atof *atof, int sign)
{
	atof->num = process_exponent(atof, atof->str, atof->i);
	if (*atof->overflow == true)
		return (handle_overflow(sign, atof->num));
	if (atof->num > FLT_MAX)
	{
		*atof->overflow = true;
		return (FLT_MAX);
	}
	if (check_near_max(atof)/*  == true */)
	{
		*atof->overflow = true;
		return (FLT_MAX);
	}
	if (atof->num == FLT_MAX && !(*atof->overflow))
		*atof->overflow = false;
	return (atof->num);
}

// Handle applying sign and checking underflow
static float apply_sign_and_check(t_atof *atof, int sign)
{
	float	result;

	result = atof->num * sign;
	if (result != 0.0F && ft_fabsf(result) < FLT_MIN)
	{
		*atof->overflow = true;
		return (0.0F);
	}
	return (result);
}

// Main function that implements rt_atof with better boundary checks
float rt_atof(const char *str, bool *overflow)
{
	t_atof	atof;
	float	special_val;
	int		sign;

	atof = (t_atof){str, 0.0F, 0, overflow};
	special_val = 0.0F;
	atof.str += skip_spaces(str);
	if (is_special_float(atof.str, &special_val))
		return (special_val);
	sign = 1;
	atof.i = process_sign(atof.str, &sign);
	atof.num = process_first_part(&atof, sign);
	if (*overflow == true)
		return (atof.num);
	atof.num = process_second_part(&atof, sign);
	if (*overflow == true)
		return (atof.num);
	return (apply_sign_and_check(&atof, sign));
}
