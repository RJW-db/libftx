/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printf_count.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/04 18:07:23 by rde-brui      #+#    #+#                 */
/*   Updated: 2025/01/13 16:53:27 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>

int32_t	spec_count_one(t_p *c, t_fl *f)
{
	char	*null_check;

	if (f->sp == 'c')
	{
		va_arg(c->va, int32_t);
		return (1);
	}
	else if (f->sp == 's')
	{
		null_check = va_arg(c->va, char *);
		if (null_check == NULL || null_check == 0)
		{
			return (6);
		}
		else
		{
			return (ft_strlen(null_check));
		}
	}
	return (signed_count(va_arg(c->va, int32_t)));
}

int32_t	spec_count_two(t_p *c, t_fl *f)
{
	int32_t		i;

	i = 0;
	if (f->sp == 'p')
	{
		i = unsigned_count(f, va_arg(c->va, uint64_t));
		if (i == 0)
		{
			i = 5;
		}
		else
		{
			i = i + 2;
		}
	}
	else if (f->sp == 'u' || f->sp == 'x' || f->sp == 'X')
	{
		return (unsigned_count(f, va_arg(c->va, uint32_t)));
	}
	else if (f->sp == '%')
	{
		return (1);
	}
	return (i);
}

int32_t	signed_count(int32_t n)
{
	int32_t	word_size;

	word_size = 0;
	if (n == 0)
	{
		return (1);
	}
	if (n < 0)
	{
		word_size += 1;
		n *= -1;
	}
	while (n != 0)
	{
		n /= 10;
		word_size += 1;
	}
	return (word_size);
}

int32_t	unsigned_count(t_fl *f, uint64_t n)
{
	int32_t	word_size;

	if (n == 0)
	{
		if (f->sp == 'p')
		{
			return (0);
		}
		else
		{
			return (1);
		}
	}
	word_size = 0;
	while (n != 0)
	{
		n /= f->b_num;
		word_size = word_size + 1;
	}
	return (word_size);
}

int32_t	ft_ultoa_base(t_fl *f, uint64_t n, char *str)
{
	char		store[21];
	uint8_t		i;

	move_num_chr(store, '\0', 21);
	if (n == 0)
	{
		str[0] = '0';
		return (1);
	}
	i = 19;
	while (n != 0)
	{
		store[i] = f->base[n % f->b_num];
		n /= f->b_num;
		i--;
	}
	return (move_str(str, &store[i + 1]));
}
