#include <ft_atof.h>

//	Static Functions
static int		parse_exponent_sign(t_atof *atof);
static int		parse_exponent_value(t_atof *atof, const char *str);
static float	apply_positive_exponent(float num, int exp, bool *overflow);
static float	apply_negative_exponent(float num, int exp, bool *overflow);

bool	process_exponent(t_atof *atof, const char *str, int i)
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
			return (false);
		}
		exp *= exp_sign;
		if (exp > 0)
			atof->num = apply_positive_exponent(atof->num, exp, atof->overflow);
		else if (exp < 0)
			atof->num = apply_negative_exponent(atof->num, exp, atof->overflow);
	}
	return (true);
}

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
