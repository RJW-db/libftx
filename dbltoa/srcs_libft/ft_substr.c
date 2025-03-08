
#include "../includes/ft_dbltoa.h"

void	extract_substr(const char *s, uint32_t start, size_t ln, char *buf)
{
	size_t i = 0;
	size_t s_len;

	if (s == NULL || buf == NULL)
		return;
	s_len = ft_strlen(s);
	if (s_len <= start)
		ln = 0;
	else if ((s_len - start) < ln)
		ln = s_len - start;
	while (i < ln && s[start + i])
	{
		buf[i] = s[start + i];
		++i;
	}
	buf[i] = '\0';
}
