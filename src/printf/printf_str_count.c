/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printf_str_count.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/10 18:29:06 by rde-brui      #+#    #+#                 */
/*   Updated: 2025/01/13 16:54:53 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

//	Static Functions
static void	str_bonus_trun_count(t_p *c, t_fl *f);
static void	flag_specific(t_p *c, t_fl *f);

/**
 * @brief	Allowed flags ".-6"   6 - minimum width
 * 			"%.-15s" not allowed order
*/
void	str_bonus_count(t_p *c, t_fl *f)
{
	t_p	tmp_copy;

	tmp_copy = *c;
	f->ap_len = spec_count_one(&tmp_copy, f);
	va_end(tmp_copy.va);
	if (f->dot == false && f->ap_len >= f->width)
	{
		c->mal += spec_count_one(c, f);
	}
	else if (f->dot == false && f->ap_len < f->width)
	{
		c->mal += spec_count_one(c, f) + f->width - f->ap_len;
	}
	else if (f->dot == true)
	{
		str_bonus_trun_count(c, f);
	}
}

static void	str_bonus_trun_count(t_p *c, t_fl *f)
{
	char	*nil_check;

	nil_check = va_arg(c->va, char *);
	if (nil_check == NULL)
	{
		if (f->dash == true && f->prec >= 6)
		{
			c->mal += 6;
		}
		else if (f->prec >= 6 && f->width <= 0)
		{
			c->mal += 6;
		}
		else if (f->prec >= 6 && f->width > 0)
		{
			c->mal += f->width - f->prec + 6;
		}
		else
		{
			c->mal += f->width;
		}
	}
	else
		flag_specific(c, f);
}

static void	flag_specific(t_p *c, t_fl *f)
{
	int32_t	spaces;

	if (f->prec < f->ap_len)
	{
		spaces = f->width - f->prec;
		f->width = f->prec;
	}
	else
	{
		spaces = f->width - f->ap_len;
		f->width = f->ap_len;
	}
	if (f->dash == true)
	{
		c->mal += f->width;
	}
	if (spaces > 0)
	{
		c->mal += spaces;
	}
	if (f->dash == false)
	{
		c->mal += f->width;
	}
}
