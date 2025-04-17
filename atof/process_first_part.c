#include <ft_atof.h>

//	Static Functions
static bool	parse_integer_part(t_atof *atof, const char *str, int16_t i);
static bool	parse_fraction_part(t_atof *atof, const char *str, int16_t i);

float	parse_integer_and_fraction(t_atof *atof, int8_t sign)
{
	if (parse_integer_part(atof, atof->str, atof->i) == false)
	{
		if (sign > 0)
			return (FLT_MAX);
		return (-FLT_MAX);
	}
	if (parse_fraction_part(atof, atof->str, atof->i) == false)
	{
		if (sign > 0)
			return (FLT_MAX);
		return (-FLT_MAX);
	}
	return (atof->num);
}


static bool	parse_integer_part(t_atof *atof, const char *str, int16_t i)
{
	float	num;

	num = 0.0F;
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		if (num > (FLT_MAX - (str[i] - '0')) / 10.0F)
		{
			*atof->overflow = true;
			atof->num = FLT_MAX;
			return (false);
		}
		num = (num * 10.0F) + (str[i] - '0');
		++i;
	}
	atof->i = i;
	atof->num = num;
	return (true);
}

static bool	parse_fraction_part(t_atof *atof, const char *str, int16_t i)
{
	float	digit_value;
	float	scale;

	scale = 0.1F;
	if (str[i] == '.')
	{
		++i;
		while (str[i] != '\0' && ft_isdigit(str[i]) == true)
		{
			digit_value = (str[i] - '0') * scale;
			if (atof->num > FLT_MAX - digit_value)
			{
				*atof->overflow = true;
				atof->num = FLT_MAX;
				return (false);
			}
			atof->num += digit_value;
			scale *= 0.1F;
			++i;
		}
	}
	atof->i = i;
	return (true);
}
