/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printf_flags.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/12 00:29:08 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/13 17:43:52 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>

//	Static Functions
static void		flags_reset(t_fl *f);
static int32_t	find_spec(t_fl *f, t_cchr fmt, int8_t i);
static int32_t	get_flags(t_p *c, t_fl *f, int32_t k);
static int32_t	get_width_prec(t_p *c, t_fl *f, int32_t k, int32_t *width_prec);

int32_t	parse_format(t_p *c, t_fl *f, int32_t k)
{
	int32_t	begin;
	int8_t	specifier;
	int8_t	i;

	begin = k;
	flags_reset(f);
	if (c->fmt[k] != '%')
		return (-1);
	k++;
	c->k++;
	i = 0;
	specifier = find_spec(f, c->fmt[k], i);
	if (specifier >= 0)
		return (specifier);
	k = get_flags(c, f, k);
	k = get_width_prec(c, f, k, &f->width);
	k = get_width_prec(c, f, k, &f->prec);
	specifier = find_spec(f, c->fmt[k], i);
	if (specifier == -1)
		flags_reset(f);
	c->k += k - begin - 1;
	return (specifier);
}

static void	flags_reset(t_fl *f)
{
	ft_bzero(f, sizeof(t_fl));
	f->sign = 'X';
	move_num_chr(f->prefix, '\0', 3);
}

static int32_t	find_spec(t_fl *f, t_cchr fmt, int8_t i)
{
	while (SPECIFIER[i] != '\0')
	{
		if (fmt == SPECIFIER[i])
		{
			f->sp = fmt;
			f->b_num = 16;
			f->base = "0123456789abcdef";
			move_str(f->prefix, "0x");
			if (fmt == 'X')
			{
				f->base = "0123456789ABCDEF";
				move_str(f->prefix, "0X");
			}
			else if (c_in_str(fmt, "udi") == true)
			{
				f->base = "0123456789";
				f->b_num = 10;
			}
			return (i);
		}
		i++;
	}
	return (-1);
}

static int32_t	get_flags(t_p *c, t_fl *f, int32_t k)
{
	while (c_in_str(c->fmt[k], " +-0#") == true)
	{
		if (c->fmt[k] == ' ')
			f->space = true;
		else if (c->fmt[k] == '+')
			f->plus = true;
		else if (c->fmt[k] == '-')
			f->dash = true;
		else if (c->fmt[k] == '0')
			f->zero = true;
		else if (c->fmt[k] == '#')
			f->hash = true;
		f->f_len++;
		k++;
	}
	return (k);
}

static int32_t	get_width_prec(t_p *c, t_fl *f, int32_t k, int32_t *width_prec)
{
	if (f->stop == true)
	{
		if (c->fmt[k] != '.')
			return (k);
		f->dot = true;
		++k;
	}
	else
		f->stop = true;
	while (c->fmt[k] >= '0' && c->fmt[k] <= '9')
	{
		*width_prec = *width_prec * 10 + (c->fmt[k] - 48);
		++k;
	}
	return (k);
}
