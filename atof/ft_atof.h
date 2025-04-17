#ifndef FT_ATOF_H
# define FT_ATOF_H

# include <stdio.h>
# include <stdbool.h>
# include <float.h>
# include <math.h>
# include <string.h>
# include <stdint.h>
# include <libft.h>
# include <limits.h>

typedef struct s_stod
{
	const char	*str;
	float		num;
	int16_t		i;
	bool		*overflow;
} t_atof;

float	ft_atof(const char *str, bool *overflow);

float	parse_integer_and_fraction(t_atof *atof, int8_t sign);
float	parse_exponent_and_adjust(t_atof *atof, int8_t sign);
bool	parse_and_apply_exponent(t_atof *atof, const char *str, int16_t i);


double	ft_fabs(double x);
float	ft_fabsf(float x);
#endif
