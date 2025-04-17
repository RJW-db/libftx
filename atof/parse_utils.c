#include <stdio.h>
#include <stdbool.h>
#include <float.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include <libft.h>
#include <limits.h>

typedef struct	s_stod
{
	double	num;
	bool	*overflow;
	double	max_val;
	double	min_val;
	bool	is_double;
}	t_stod;


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
int	process_sign(const char *str, int *sign)
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
double process_integer(const char *str, int *idx, t_stod *stod)
{
	int 	i;

	i = *idx;
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		if (stod->num > (stod->max_val - (str[i] - '0')) / 10.0)
		{
			*stod->overflow = true;
			*idx = i;
			return (stod->max_val);
		}
		stod->num = (stod->num * 10.0) + (str[i] - '0');
		++i;
	}
	*idx = i;
	return (stod->num);
}

// Process fractional part
double process_fraction(const char *str, int *idx, t_stod *stod)
{
	double	digit_value;
	double	scale;
	int		i;

	i = *idx;
	scale = 0.1;
	if (str[i] == '.')
	{
		++i;
		while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
		{
			digit_value = (str[i++] - '0') * scale;
			if (stod->num > stod->max_val - digit_value)
			{
				*stod->overflow = true;
				*idx = i;
				return (stod->max_val);
			}
			stod->num += digit_value;
			scale *= 0.1;
		}
	}
	*idx = i;
	return (stod->num);
}

// Helper function to parse the exponent sign
static int8_t parse_exponent_sign(const char *str, int *i)
{
	int8_t	exp_sign;

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
static double apply_positive_exponent(int exp, t_stod *stod)
{
	while (exp > 0)
	{
		// printf("Before multiplication: num = %e, exp = %d\n", stod->num, exp);
		if (stod->num > stod->max_val / 10.0)
		{
			// printf("Overflow detected: num = %e\n", stod->num);
			*stod->overflow = true;
			return (stod->max_val);
		}
		stod->num *= 10.0;
		--exp;
	}
	return (stod->num);
}

// Helper function to handle negative exponents
static double apply_negative_exponent(int exp, t_stod *stod)
{
	while (exp < 0)
	{
		stod->num *= 0.1F;
		if (stod->num != 0.0)
		{
			if (stod->is_double == true)
				*stod->overflow = (ft_fabs(stod->num) < stod->min_val);
			else
				*stod->overflow = (ft_fabsf((float)stod->num) < stod->min_val);
			if (*stod->overflow == true)
				return (0.0);
		}
		++exp;
	}
	return (stod->num);
}

// Main process_exponent function
double process_exponent(const char *str, int *idx, t_stod *stod)
{
	int8_t	exp_sign;
	int		exp;

	if ((str[*idx] == 'e' || str[*idx] == 'E') && str[*idx + 1] != '\0')
	{
		++(*idx);
		exp_sign = parse_exponent_sign(str, idx);
		exp = parse_exponent_value(str, idx, stod->overflow);
		if (*stod->overflow == true)
		{
			if (exp_sign > 0)
				return (stod->max_val);
			return (0.0);
		}
		exp *= exp_sign;
		if (exp > 0) {
			// puts("1");
			stod->num = apply_positive_exponent(exp, stod);
		}
		else if (exp < 0){
			// puts("2");
			stod->num = apply_negative_exponent(exp, stod);
		}
	}
	return (stod->num);
}

// Check if string is a special floating point value like "inf" or "nan"
static bool is_special_float(const char *str, double *result)
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
static double extract_mantissa(const char *str)
{
	double	mantissa;
	double	frac_scale;
	int		idx;

	mantissa = 0.0;
	frac_scale = 0.1;
	idx = 0;
	while (str[idx] == ' ' || str[idx] == '\t')
		++idx;
	if (str[idx] == '-' || str[idx] == '+')
		++idx;
	while (str[idx] != '\0' && str[idx] >= '0' && str[idx] <= '9')
		mantissa = mantissa * 10.0 + (str[idx++] - '0');
	if (str[idx] == '.')
	{
		++idx;
		while (str[idx] != '\0' && str[idx] >= '0' && str[idx] <= '9')
		{
			mantissa += (str[idx] - '0') * frac_scale;
			frac_scale *= 0.1;
			++idx;
		}
	}
	return (mantissa);
}

// Check if number is near FLT_MAX and potentially overflows
static bool check_near_max(const char *str, t_stod *stod)
{
	bool	found_exp;
	double	mantissa;
	int		exp_val;

	found_exp = false;
	mantissa = 0.0;
	exp_val = 0;
	// if (stod->num <= stod->max_val * 0.999999999999999)	// for float you would only need 0.999999
	if (stod->num <= stod->max_val * 0.999999F)	// for float you would only need 0.999999f
		return (false);
	exp_val = extract_exp_value(str, &found_exp);
	mantissa = extract_mantissa(str);
	// if (exp_val > 38 || (exp_val == 38 && mantissa > stod->max_val))	// for float you would only need 3.4028234F
	// if (exp_val > 38 || (exp_val == 38 && mantissa > 1.7976931348623157e+308))	// for float you would only need 3.4028234F
	if (exp_val > 38 || (exp_val == 38 && mantissa > 3.4028234F))	// for float you would only need 3.4028234F
		return (true);
	return (false);
}

// Handle overflow based on sign
static double handle_overflow(int sign, t_stod *stod)
{
	if (stod->num == 0.0)
		return (0.0);
	if (sign > 0)
		return (stod->max_val);
	return (-stod->max_val);
}

// Process the first part of numeric parsing
static double process_first_part(const char *str, int *i, int sign, t_stod *stod)
{
	stod->num = process_integer(str, i, stod);
	if (*stod->overflow == true)
	{
		if (sign > 0)
			return (stod->max_val);
		return (-stod->max_val);
	}
	stod->num = process_fraction(str, i, stod);
	if (*stod->overflow == true)
	{
		if (sign > 0)
			return (stod->max_val);
		return (-stod->max_val);
	}
	return (stod->num);
}

// Process the second part of numeric parsing
static double process_second_part(const char *str, int *i, int sign, t_stod *stod)
{
	stod->num = process_exponent(str, i, stod);
	if (*stod->overflow == true)
		return (handle_overflow(sign, stod));
	if (stod->num > stod->max_val * 0.999999)
	{
		*stod->overflow = true;
		return (stod->max_val);
	}
	if (check_near_max(str, stod))
	{
		*stod->overflow = true;
		return (stod->max_val);
	}
	if (stod->num == stod->max_val && !(*stod->overflow))
		*stod->overflow = true;
	return (stod->num);
}

// Handle applying sign and checking underflow
static double apply_sign_and_check(int sign, t_stod *stod)
{
	double	result;

	result = stod->num * sign;
	if (result != 0.0)
	{
		if (stod->is_double == true)
			*stod->overflow = ft_fabs(result) < stod->min_val;
		else
			*stod->overflow = ft_fabsf((float)result) < stod->min_val;
		if (*stod->overflow == true)
			return (0.0);
	}
	// printf("result %.1074f\n", result);

	return (result);
}

// Main function that implements rt_atof with better boundary checks
float rt_atof(const char *str, bool *overflow)
{
	t_stod	stod;
	double	special_value;
	int		i;
	int		sign;

	// if (normally do this----unless with makefile define don't do this)
	// 	*overflow = false;
	stod = (t_stod){0.0, overflow, FLT_MAX, FLT_MIN, false};
	special_value = 0.0;
	stod.num = 0.0;
	sign = 1;
	i = process_sign(str, &sign);
	if (is_special_float(str, &special_value))
		return (special_value);
	stod.num = process_first_part(str, &i, sign, &stod);
	if (*overflow == true)
		return (stod.num);
	stod.num = process_second_part(str, &i, sign, &stod);
	if (*overflow == true)
		return (stod.num);
	return (apply_sign_and_check(sign, &stod));
}
