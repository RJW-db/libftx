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
    int			i;
    bool		*overflow;
} t_atof;

float	ft_atof(const char *str, bool *overflow);

float	process_first_part(t_atof *atof, int sign);
float	process_second_part(t_atof *atof, int sign);
bool	process_exponent(t_atof *atof, const char *str, int i);


double	ft_fabs(double x);
float	ft_fabsf(float x);
#endif
