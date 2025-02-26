
#include "../includes/ft_dbltoa.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t i;

	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst <= src)
	{
		while (i < len)
		{
			((unsigned char *)dst)[i] = ((unsigned char	*)src)[i];
			i++;
		}
	}
	else
	{
		while (i < len)
		{
			((unsigned char *)dst)[len - i - 1] =
				((unsigned char *)src)[len - i - 1];
			i++;
		}
	}
	return (dst);
}
