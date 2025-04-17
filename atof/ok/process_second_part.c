#include <ft_atof.h>

//	Static Functions
static bool		check_near_max(t_atof *atof);
static int		extract_exp_value(const char *str);
static int		parse_exponent(const char *str, int i);
static float	extract_mantissa(const char *str);

// Near-maximum threshold (99.9999% of FLT_MAX)
#define FLT_NEAR_MAX_THRESHOLD 0.999999F
// Maximum mantissa value for float (slightly below the exact value for precision)
#define FLT_MAX_MANTISSA 3.4028234F

float	process_second_part(t_atof *atof, int sign)
{
	if (process_exponent(atof, atof->str, atof->i) == false)
	{
		if (atof->num == 0.0F)
			return (0.0F);
		if (sign > 0)
			return (FLT_MAX);
		return (-FLT_MAX);
	}
	if (check_near_max(atof) == true)
	{
		*atof->overflow = true;
		return (FLT_MAX);
	}
	return (atof->num);
}

static bool	check_near_max(t_atof *atof)
{
	int	exp_val;

	if (atof->num <= FLT_MAX * FLT_NEAR_MAX_THRESHOLD)
		return false;
	exp_val = extract_exp_value(atof->str);
	if (exp_val > 38)
		return (true);
	if (exp_val < 38)
		return (false);
	return (extract_mantissa(atof->str) > FLT_MAX_MANTISSA);
}

static int	extract_exp_value(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 'e' || str[i] == 'E')
			return (parse_exponent(str, ++i));
		++i;
	}
	return (0);
}

static int	parse_exponent(const char *str, int i)
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

static float	extract_mantissa(const char *str)
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
		mantissa = mantissa * 10.0F + (str[idx++] - '0');
	if (str[idx] == '.')
	{
		++idx;
		while (str[idx] != '\0' && str[idx] >= '0' && str[idx] <= '9')
		{
			mantissa += (str[idx] - '0') * frac_scale;
			frac_scale *= 0.1F;
			++idx;
		}
	}
	return (mantissa);
}
