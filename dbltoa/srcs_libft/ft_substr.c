
#include "../includes/ft_dbltoa.h"

char	*ft_substr(char const *s, uint32_t start, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len <= start)
		len = 0;
	else if ((s_len - start) < len)
		len = s_len - start;
	ptr = malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		ptr[i] = s[start + i];
		++i;
	}
	ptr[i] = '\0';
	return (ptr);
}

void	substr_buff(const char *s, uint32_t start, size_t len, char *buff)
{
	size_t i = 0;
	size_t s_len;

	if (s == NULL || buff == NULL)
		return;
	s_len = ft_strlen(s);
	if (s_len <= start)
		len = 0;
	else if ((s_len - start) < len)
		len = s_len - start;
	while (i < len && s[start + i])
	{
		buff[i] = s[start + i];
		++i;
	}
	buff[i] = '\0';
}
