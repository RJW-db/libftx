
#include "../includes/ft_dbltoa.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*tmp;

	tmp = dest;
	if (src > dest)
		while (n--)
			*(char *)tmp++ = *(char *)src++;
	if (dest > src)
		while (n--)
			*((char *)dest + n) = *((char *)src + n);
	return (dest);
}
