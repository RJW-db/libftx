/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printf_int.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/14 14:40:19 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/13 16:54:10 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

//	Static Functions
static void	count_p2(t_p *c, t_fl *f, int32_t prefix);
static void	int_bonus_p2(t_p *p, t_fl *f, int32_t pref);

/**
 * @brief d & i,
 * negative number negates the flag +,,
 * space will be ignored when there is +,
 * 0 is ignored when - is there,
 * s and c have their own structure
*/
void	int_bonus_count(t_p *c, t_fl *f)
{
	int32_t		prefix;

	f->nbr = va_arg(c->va, int32_t);
	prefix = ((f->nbr < 0) || f->plus || (f->width <= 0 && f->space));
	f->ap_len = signed_count(f->nbr) + (prefix == 1 && (f->nbr >= 0));
	if (f->ap_len - prefix >= f->prec)
		f->width -= f->ap_len;
	else
		f->width -= f->prec + prefix;
	if (f->nbr < 0)
	{
		f->sign = '-';
		f->nbr *= -1;
	}
	else if (f->plus == true && f->sign == 'X')
		f->sign = '+';
	else if (f->space == true && f->sign == 'X')
	{
		f->sign = ' ';
		f->width -= 1;
	}
	if (f->dash == true)
		f->zero = false;
	count_p2(c, f, prefix);
}

/**
 * @brief d & i,
 * negative number negates the flag +,,
 * space will be ignored when there is +,
 * 0 is ignored when - is there,
 * s and c have their own structure
*/
void	int_bonus_write(t_p *p, t_fl *f)
{
	int32_t		prefix;

	f->nbr = va_arg(p->va, int32_t);
	prefix = ((f->nbr < 0) || f->plus || (f->width <= 0 && f->space));
	f->ap_len = signed_count(f->nbr) + (prefix == 1 && (f->nbr >= 0));
	if (f->ap_len - prefix >= f->prec)
		f->width -= f->ap_len;
	else
		f->width -= f->prec + prefix;
	if (f->nbr < 0)
	{
		f->sign = '-';
		f->nbr *= -1;
	}
	else if (f->plus == true && f->sign == 'X')
		f->sign = '+';
	else if (f->space == true && f->sign == 'X')
	{
		f->sign = ' ';
		f->width -= 1;
	}
	if (f->dash == true)
		f->zero = false;
	int_bonus_p2(p, f, prefix);
}

static void	count_p2(t_p *c, t_fl *f, int32_t prefix)
{
	if (f->width >= 0 && f->dash == false && f->dot == true)
		c->mal += f->width + (f->nbr == 0 && f->space == false && f->prec == 0);
	else if (f->width >= 0 && f->dash == false && f->zero == false)
		c->mal += f->width;
	if (f->sign != 'X')
		c->mal += 1;
	if (f->dot == true && f->prec - f->ap_len + prefix > 0)
		c->mal += f->prec - f->ap_len + prefix;
	else if (f->zero == true && f->width > 0 && f->dot == false)
		c->mal += f->width;
	if (f->nbr != 0 || (f->width && f->prec) || (f->nbr == 0
			&& f->dot == false))
	{
		c->mal += unsigned_count(f, f->nbr);
	}
	else if (f->nbr == 0 && f->space == true && f->width > 0)
		c->mal += 1;
	if (f->width >= 0 && f->dash == true)
	{
		c->mal += f->width + (f->dot == true && f->nbr == 0 && f->space == false
				&& f->prec == 0);
	}
}

static void	int_bonus_p2(t_p *p, t_fl *f, int32_t prefix)
{
	if (f->width >= 0 && f->dash == false && f->dot == true)
	{
		p->i += move_num_chr(p->str + p->i, ' ', f->width
				+ (f->nbr == 0 && f->space == false && f->prec == 0));
	}
	else if (f->width >= 0 && f->dash == false && f->zero == false)
		p->i += move_num_chr(p->str + p->i, ' ', f->width);
	if (f->sign != 'X')
		p->i += move_num_chr(p->str + p->i, f->sign, 1);
	if (f->dot == true)
		p->i += move_num_chr(p->str + p->i, '0', f->prec - f->ap_len + prefix);
	else if (f->zero == true)
		p->i += move_num_chr(p->str + p->i, '0', f->width);
	if (f->nbr != 0 || (f->width && f->prec) || (f->nbr == 0
			&& f->dot == false))
		p->i += ft_ultoa_base(f, f->nbr, p->str + p->i);
	else if (f->nbr == 0 && f->space == true && f->width > 0)
		p->i += move_str(p->str + p->i, " ");
	if (f->width >= 0 && f->dash == true)
	{
		p->i += move_num_chr(p->str + p->i, ' ', f->width + (f->dot == true
					&& f->nbr == 0 && f->space == false && f->prec == 0));
	}
}
