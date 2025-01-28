/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printf_process_format.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/13 16:09:26 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/13 17:09:20 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int32_t	parse_format_string(t_p *c)
{
	t_fl	flags;

	c->i = 0;
	c->mal = 0;
	c->k = 0;
	while (c->fmt && c->fmt[c->k] != '\0')
	{
		c->spec = parse_format(c, &flags, c->k);
		if (c->spec == -1)
		{
			if (c->count_or_str == true)
				++c->mal;
			else
				c->i += move_num_chr(&c->str[c->i], c->fmt[c->k], 1);
			++c->k;
			continue ;
		}
		else
		{
			flag_check(c, &flags);
		}
		++c->k;
	}
	return (c->mal);
}

void	spec_str_one(t_p *p, t_fl *f)
{
	char			*null_check;

	if (f->sp == 'c')
	{
		p->i += move_num_chr(p->str + p->i, va_arg(p->va, int32_t), 1);
	}
	else if (f->sp == 's')
	{
		null_check = va_arg(p->va, char *);
		if (null_check == NULL || null_check == 0)
		{
			p->i += move_str(p->str + p->i, "(null)");
		}
		else
		{
			p->i += move_str(p->str + p->i, null_check);
		}
	}
	else if (f->sp == 'd' || f->sp == 'i')
	{
		p->i += signed_decimal_base(p->str + p->i, va_arg(p->va, int32_t));
	}
}

void	spec_str_two(t_p *p, t_fl *f)
{
	if (f->sp == 'p')
	{
		f->nbr = va_arg(p->va, uint64_t);
		if (f->nbr == 0)
		{
			p->i += move_str(p->str + p->i, "(nil)");
		}
		else
		{
			p->i += move_str(p->str + p->i, "0x");
			p->i += ft_ultoa_base(f, f->nbr, p->str + p->i);
		}
	}
	else if (f->sp == 'x' || f->sp == 'X' || f->sp == 'u')
	{
		p->i += ft_ultoa_base(f, va_arg(p->va, uint32_t), p->str + p->i);
	}
	else if (f->sp == '%')
	{
		p->i += move_str(p->str + p->i, "%");
	}
}
