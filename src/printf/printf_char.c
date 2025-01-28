/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printf_char.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/09 18:09:43 by rde-brui      #+#    #+#                 */
/*   Updated: 2025/01/13 17:43:59 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void	chr_bonus_count(t_p *c, t_fl *f)
{
	va_arg(c->va, int32_t);
	if (f->width == 0)
	{
		++c->mal;
	}
	else
	{
		c->mal += f->width;
	}
}

void	chr_bonus_write(t_p *p, t_fl *f)
{
	if (f->dash == false)
	{
		p->i += move_num_chr(p->str + p->i, ' ', f->width - 1);
	}
	p->str[p->i] = va_arg(p->va, int32_t);
	++p->i;
	if (f->dash == true && f->width > 0)
	{
		p->i += move_num_chr(p->str + p->i, ' ', f->width - 1);
	}
}
