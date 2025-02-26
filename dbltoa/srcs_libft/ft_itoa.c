#include "../includes/ft_dbltoa.h"

char	*mallocstr(unsigned long temp, unsigned long *len)
{
	char *str;

	while (temp > 9)
	{
		temp /= 10;
		*len += 1;
	}
	if (!(str = malloc(sizeof(*str) * (*len + 1))))
		return (NULL);
	str[*len] = 0;
	*len -= 1;
	return (str);
}

char	*ft_itoa(long n)
{
	char			*str;
	unsigned long	temp;
	unsigned long	len;

	len = 1;
	temp = n;
	if (n < 0)
	{
		len++;
		temp = -n;
	}
	if (!(str = mallocstr(temp, &len)))
		return (NULL);
	if (n < 0)
		str[0] = '-';
	while (temp > 9)
	{
		str[len--] = (temp % 10) + 48;
		temp /= 10;
	}
	str[len] = temp + 48;
	return (str);
}
