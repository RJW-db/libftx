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
float process_integer(const char *str, int *idx, bool *overflow)
{
	float	num;
	int 	i;

	i = *idx;
	num = 0.0F;
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		if (num > (FLT_MAX - (str[i] - '0')) / 10.0F)
		{
			*overflow = true;
			*idx = i;
			return (FLT_MAX);
		}
		num = (num * 10.0F) + (str[i] - '0');
		++i;
	}
	*idx = i;
	return (num);
}

// Process fractional part
float process_fraction(const char *str, int *idx, float num, bool *overflow)
{
	float	digit_value;
	float	scale;
	int		i;

	i = *idx;
	scale = 0.1F;
	if (str[i] == '.')
	{
		++i;
		while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
		{
			digit_value = (str[i++] - '0') * scale;
			if (num > FLT_MAX - digit_value)
			{
				*overflow = true;
				*idx = i;
				return (FLT_MAX);
			}
			num += digit_value;
			scale *= 0.1F;
		}
	}
	*idx = i;
	return (num);
}


// Helper function to parse the exponent sign
static int parse_exponent_sign(const char *str, int *i)
{
	int	exp_sign;

	exp_sign = 1;
	if (str[*i] == '-')
	{
		exp_sign = -1;
		(*i)++;
	} 
	else if (str[*i] == '+')
		(*i)++;
	return (exp_sign);
}

// Helper function to parse the exponent value
static int parse_exponent_value(const char *str, int *i, bool *overflow)
{
	int	exp;

	exp = 0;
	while (str[*i] != '\0' && (str[*i] >= '0' && str[*i] <= '9'))
	{
		if (exp > (INT_MAX - (str[*i] - '0')) / 10)
		{
			*overflow = true;
			return (INT_MAX);
		}
		exp = exp * 10 + (str[(*i)++] - '0');
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
float process_exponent(const char *str, int *idx, float num, bool *overflow)
{
	int	exp_sign;
	int	exp;

	printf("%s\n", str + *idx);
	printf("result %.1074f\n", num);

	if ((str[*idx] == 'e' || str[*idx] == 'E') && str[*idx + 1] != '\0')
	{
		++(*idx);
		exp_sign = parse_exponent_sign(str, idx);
		exp = parse_exponent_value(str, idx, overflow);
		if (*overflow == true)
		{
			if (exp_sign > 0)
				return (FLT_MAX);
			return (0.0F);
		}
		exp *= exp_sign;
		if (exp > 0) {
			puts("1");
			num = apply_positive_exponent(num, exp, overflow);
		}
		else if (exp < 0) {
			puts("2");
			num = apply_negative_exponent(num, exp, overflow);
		}
	}
	// printf("result %.1074f\n", num);
	return (num);
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
static bool check_near_max(const char *str, float num)
{
	bool	found_exp;
	float	mantissa;
	int		exp_val;

	found_exp = false;
	mantissa = 0.0F;
	exp_val = 0;
	if (num <= FLT_MAX * 0.999999F)
		return (false);
	exp_val = extract_exp_value(str, &found_exp);
	mantissa = extract_mantissa(str);
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
static float process_first_part(const char *str, int *i, int sign, bool *overflow)
{
	float	num;

	num = process_integer(str, i, overflow);
	if (*overflow == true)
	{
		if (sign > 0)
			return (FLT_MAX);
		return (-FLT_MAX);
	}
	num = process_fraction(str, i, num, overflow);
	if (*overflow == true)
	{
		if (sign > 0)
			return (FLT_MAX);
		return (-FLT_MAX);
	}
	return (num);
}

// Process the second part of numeric parsing
static float process_second_part(const char *str, int *i, float num, int sign, bool *overflow)
{
	num = process_exponent(str, i, num, overflow);
	if (*overflow == true)
		return (handle_overflow(sign, num));
	if (num > FLT_MAX)
	{
		*overflow = true;
		return (FLT_MAX);
	}
	if (check_near_max(str, num))
	{
		*overflow = true;
		return (FLT_MAX);
	}
	if (num == FLT_MAX && !(*overflow))
		*overflow = false;
	return (num);
}

// Handle applying sign and checking underflow
static float apply_sign_and_check(float num, int sign, bool *overflow)
{
	float	result;

	result = num * sign;
	// printf("result %.1074f\n", result);
	if (result != 0.0F && ft_fabsf(result) < FLT_MIN)
	{
		*overflow = true;
		return (0.0F);
	}
	return (result);
}

// Main function that implements rt_atof with better boundary checks
float rt_atof(const char *str, bool *overflow)
{
	float	special_val;
	float	num;
	int		i;
	int		sign;

	special_val = 0.0F;
	num = 0.0F;
	sign = 1;
	i = skip_spaces(str);
	i = process_sign(str + i, &sign);
	if (is_special_float(str + i, &special_val))
		return (special_val);
	num = process_first_part(str, &i, sign, overflow);
	if (*overflow == true)
		return (num);
	num = process_second_part(str, &i, num, sign, overflow);
	if (*overflow == true)
		return (num);
	return (apply_sign_and_check(num, sign, overflow));
}
