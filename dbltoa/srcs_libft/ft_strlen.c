
#include "../includes/ft_dbltoa.h"

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	strlen_safe(const char *str)
{
	size_t	n;

	if (str == NULL)
		return (0);
	n = 0;
	while (str[n])
		++n;
	return (n);
}