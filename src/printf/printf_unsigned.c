/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printf_unsigned.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/10 23:32:25 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/13 17:43:37 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

//	Static Functions
static void	before_or_after(t_p *p, t_fl *f, bool stop, int8_t nil);

/**
 * @brief	6 - minimum width
 * 			p "-6"
 * 			u ".-06"
 * 			x ".-0#6"
 * 			X ".-0#6"
*/
void	nbr_bonus_count(t_p *c, t_fl *f)
{
	if (f->sp != 'p')
		f->nbr = va_arg(c->va, uint32_t);
	else
		f->nbr = va_arg(c->va, uint64_t);
	if (f->sp == 'p' && f->nbr == 0)
		f->ap_len += 5;
	else
		f->ap_len = unsigned_count(f, f->nbr);
	if (f->sp == 'p' && f->nbr != 0)
		f->ap_len += 2;
	if (f->sp != 'p' && f->hash == true && f->width == 0 && f->nbr == 0)
		f->ap_len += 2 - (2 * (f->width == 0));
	else if (f->sp != 'p' && f->hash == true)
		f->ap_len += 2 - (f->width == 2) - (2 * (f->width == 1));
	if (f->ap_len >= f->prec && f->ap_len >= f->width)
		c->mal += f->ap_len;
	else if (f->prec >= f->ap_len && f->prec >= f->width)
		c->mal += f->prec;
	else
		c->mal += f->width;
}

/**
 * @brief	6 - minimum width
 * 			p "-6"
 * 			u ".-06"
 * 			x ".-0#6"
 * 			X ".-0#6"
 * @
*/
void	nbr_bonus_write(t_p *p, t_fl *f)
{
	bool	stop;
	int8_t	nil_check;

	stop = false;
	nil_check = 0;
	if (f->sp != 'p')
		f->nbr = va_arg(p->va, uint32_t);
	else
		f->nbr = va_arg(p->va, uint64_t);
	if (f->sp == 'p' && f->nbr == 0)
	{
		f->nbr = 5;
		nil_check = 2;
	}
	f->ap_len = unsigned_count(f, f->nbr);
	if (f->ap_len >= f->prec)
		f->width -= f->ap_len;
	else
		f->width -= f->prec;
	if (((f->ap_len != 0) && (f->hash == true && f->nbr != 0)) || f->sp == 'p')
		f->hsh = 2;
	if (f->width >= 0 && f->dash == false
		&& (f->dot == true || f->zero == false))
		p->i += move_num_chr(p->str + p->i, ' ', f->width - f->hsh - nil_check);
	before_or_after(p, f, stop, nil_check);
}

static void	before_or_after(t_p *p, t_fl *f, bool stop, int8_t nil)
{
	if (nil == 0 && (f->sp == 'p' || f->hash == true) && f->nbr != 0
		&& (f->zero == true || f->prec >= f->ap_len + f->hsh))
	{
		p->i += move_str(p->str + p->i, f->prefix);
		stop = true;
	}
	if (f->width >= 0 && f->dash == false && f->zero == true && f->dot == false)
		p->i += move_num_chr(p->str + p->i, '0', f->width - f->hsh);
	if (f->dot == true)
		p->i += move_num_chr(p->str + p->i, '0', f->prec - f->ap_len);
	if (f->dot == true && f->prec == 0)
		p->i += move_str(p->str + p->i, " ");
	else
	{
		if (nil == 0 && (f->sp == 'p' || f->hash == true) && f->nbr != 0
			&& stop == false)
			p->i += move_str(p->str + p->i, f->prefix);
		if (nil == false)
			p->i += ft_ultoa_base(f, f->nbr, p->str + p->i);
		else
			p->i += move_str(p->str + p->i, "(nil)");
	}
	if (f->width >= 0 && f->dash == true)
		p->i += move_num_chr(p->str + p->i, ' ', f->width - f->hsh - nil);
}
