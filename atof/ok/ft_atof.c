#include <ft_atof.h>

//	Static Functions
static bool		is_special_float(const char *str, float *result);
static int		process_sign(const char *str, int *sign);
static float	apply_sign_and_check(t_atof *atof, int sign);

float	ft_atof(const char *str, bool *overflow)
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

static bool	is_special_float(const char *str, float *result)
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

// Skip whitespace and process sign
static int	process_sign(const char *str, int *sign)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		*sign = -1;
		++i;
	}
	else if (str[i] == '+')
		++i;
	return (i);
}

static float	apply_sign_and_check(t_atof *atof, int sign)
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
