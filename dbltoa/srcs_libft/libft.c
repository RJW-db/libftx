#include <dbltoa.h>
#include <stdlib.h>

int64_t	atoi64(const char *nptr)
{
	int64_t	i;
	int8_t	flag;

	if (*nptr == '\0')
		return (0);
	i = 0;
	flag = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		++nptr;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			flag *= -1;
	while (*nptr >= '0' && *nptr <= '9')
		i = i * 10 + (*nptr++ - '0');
	return (i * flag);
}

char	*charmove(char *dest, const char *src, size_t n)
{
	char	*tmp;

	tmp = dest;
	if (src > dest)
		while (n--)
			*tmp++ = *src++;
	else if (dest > src)
		while (n--)
			*(dest + n) = *(src + n);
	return (dest);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t		i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = (unsigned char)c;
		++i;
	}
	return (b);
}


char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		++i;
	}
	if ((char)c == '\0')
		return ((char *)s + i);
	return (NULL);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n--)
	{
		if (*s1 != *s2) {
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		}
		if (*s1 == '\0') {
			return (0);
		}
		++s1;
		++s2;
	}
	return (0);
}

size_t	find_char_not(const char *str, const char c1)
{
	char	*tmp_str;

	tmp_str = (char *)str;
	while (*tmp_str != '\0' && *tmp_str == c1)
	{
		++tmp_str;
	}
	if (*tmp_str != c1)
	{
		return (tmp_str - str);
	}
	return (0);
}


bool	strs_ok(const char *s1, const char *s2)
{
	return (s1 != NULL && s2 != NULL);
}

size_t	cpy_str(char *dst, const char *src)
{
	size_t	i;
	char	c;

	i = 0;
	c = src[i];
	while (c != '\0')
	{
		dst[i] = c;
		++i;
		c = src[i];
	}
	dst[i] = '\0';
	return (i);
}

size_t	cpy_str_s(char *dst, const char *src)
{
	if (strs_ok(dst, src) == false)
		return (0);
	return (cpy_str(dst, src));
}

size_t	cpy_srcs_s(char *dst, const char *s1, const char *s2, const char *s3)
{
	size_t	i;

	if (strs_ok(dst, s1) == false)
		return (0);
	i = cpy_str(dst, s1);
	if (s2 == NULL)
	{
		dst[i] = '\0';
		return (i);
	}
	i += cpy_str(&dst[i], s2);
	if (s3 == NULL)
	{
		dst[i] = '\0';
		return (i);
	}
	i += cpy_str(&dst[i], s3);
	dst[i] = '\0';
	return (i);
}

char	*strjoin_safe(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	index;

	ptr = malloc(sizeof(char) * (strlen_safe(s1) + strlen_safe(s2) + 1));
	if (ptr == NULL)
		return (NULL);
	index = cpy_str_s(ptr, s1);
	index = cpy_str_s(ptr + index, s2);
	if (s1 == NULL && s2 == NULL)
		ptr[0] = '\0';
	return (ptr);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		while (src[i])
			++i;
		return (i);
	}
	while (i < size - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		++i;
	}
	if (i < size)
		dst[i] = '\0';
	while (src[i] != '\0')
		++i;
	return (i);
}


char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	len;

	len = ft_strlen(s);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	cpy_str(str, s);
	return (str);
}

size_t	ft_strlen(const char *s)
{
	const char	*tmp = s;

	while (*tmp != '\0')
		++tmp;
	return (tmp - s);
}

size_t	strlen_safe(const char *str)
{
	size_t	n;

	if (str == NULL)
		return (0);
	n = 0;
	while (str[n] != '\0')
		++n;
	return (n);
}

void	extract_substr(const char *s, uint32_t start, size_t ln, char *buf)
{
	size_t i = 0;
	size_t s_len;

	if (s == NULL || buf == NULL)
		return ;
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
