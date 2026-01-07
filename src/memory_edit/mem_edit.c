/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mem_edit.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:32:47 by rjw           #+#    #+#                 */
/*   Updated: 2025/05/09 15:52:40 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libftx.h>

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*tmp_dest;
	const unsigned char	*tmp_src;

	if (!dest && !src)
		return (NULL);
	tmp_dest = (unsigned char *)dest;
	tmp_src = (const unsigned char *)src;
	while (n--)
		*tmp_dest++ = *tmp_src++;
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*src_char = src;
	char		*tmp;

	tmp = dest;
	if (src_char > tmp)
		while (n--)
			*(tmp++) = *(src_char++);
	if ((char *)dest > src_char)
		while (n--)
			*((char *)dest + n) = *(src_char + n);
	return (dest);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*charb;

	charb = b;
	while (len--)
		*charb++ = (unsigned char)c;
	return (b);
}

/**
 * @brief Swaps the values of two memory locations byte by byte.
 * @param[in,out] a Pointer to the first value to swap (modified in place).
 * @param[in,out] b Pointer to the second value to swap (modified in place).
 * @param[in] size Size of the data type in bytes, e.g., sizeof(int).
 * @return false if any pointer is NULL or size is 0, true otherwise.
 */
bool	swap_values(void *a, void *b, size_t size)
{
	unsigned char	*p1;
	unsigned char	*p2;
	unsigned char	tmp;

	if (!a || !b || size == 0)
		return (false);
	p1 = (unsigned char *)a;
	p2 = (unsigned char *)b;
	while (size != 0)
	{
		tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		++p1;
		++p2;
		--size;
	}
	return (true);
}
