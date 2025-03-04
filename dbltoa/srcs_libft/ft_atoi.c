
#include "../includes/ft_dbltoa.h"

// int32_t	ft_atoi(const char *nptr)
// {
// 	int32_t	i;
// 	int8_t	flag;

// 	i = 0;
// 	flag = 1;
// 	if (*nptr == '\0')
// 		return (0);
// 	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n' || \
// 	*nptr == '\v' || *nptr == '\f' || *nptr == '\r')
// 		++nptr;
// 	if (*nptr == '-' || *nptr == '+')
// 		if (*nptr++ == '-')
// 			flag *= -1;
// 	while (*nptr >= '0' && *nptr <= '9')
// 		i = i * 10 + (*nptr++ - '0');
// 	return (i * flag);
// }

long		ft_atoi(const char *str)
{
	long	nb;
	long	signe;
	long	i;

	nb = 0;
	signe = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		signe *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return ((long)(nb * signe));
}

void ft_bzero(void *str, size_t size_n)
{
    unsigned char *p = (unsigned char *)str;
    for (size_t i = 0; i < size_n; i++)
        p[i] = 0;
}