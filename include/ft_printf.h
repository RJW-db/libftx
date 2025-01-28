/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/11 17:39:55 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/13 17:47:39 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>	// va_list
# include <common_defs.h>
# define SPECIFIER "csdiupxX%"

typedef struct p_print
{
	t_cchr	*fmt;
	int8_t	spec;
	va_list	va;
	int32_t	mal;
	char	*str;
	int32_t	i;
	int32_t	k;
	bool	count_or_str;
}	t_p;

typedef struct s_flags
{
	char	sp;
	bool	space;
	bool	plus;
	bool	dash;
	bool	zero;
	bool	hash;
	int8_t	hsh;
	int32_t	width;
	bool	dot;
	int32_t	prec;
	int32_t	f_len;
	int32_t	ap_len;
	bool	minus;
	char	sign;
	int64_t	nbr;
	char	*base;
	int8_t	b_num;
	char	prefix[3];
	bool	stop;
	va_list	count;
}	t_fl;

int		ft_printf(t_cchr *fmt, ...);
int		ft_dprintf(int fd, t_cchr *format, ...);
int		ft_vprintf(t_cchr *format, va_list args);

int32_t	parse_format_string(t_p *c);
int32_t	parse_format(t_p *c, t_fl *f, int32_t i);
void	flag_check(t_p *c, t_fl *f);

int32_t	spec_count_one(t_p *c, t_fl *f);
int32_t	spec_count_two(t_p *c, t_fl *f);
void	spec_str_one(t_p *p, t_fl *f);
void	spec_str_two(t_p *p, t_fl *f);

int32_t	unsigned_count(t_fl *f, uint64_t n);
int32_t	signed_count(int32_t n);
int32_t	signed_decimal_base(char *str, int32_t n);
int32_t	move_str(char *dst, t_cchr *src);
int32_t	move_num_src(char *dst, t_cchr *src, int32_t num);
int32_t	move_num_chr(char *str, t_cchr c, int32_t n);
int32_t	ft_ultoa_base(t_fl *f, uint64_t n, char *str);

void	chr_bonus_count(t_p *c, t_fl *f);
void	chr_bonus_write(t_p *p, t_fl *f);
void	str_bonus_count(t_p *c, t_fl *f);
void	str_bonus_write(t_p *p, t_fl *f);
void	int_bonus_count(t_p *c, t_fl *f);
void	int_bonus_write(t_p *p, t_fl *f);
void	nbr_bonus_count(t_p *c, t_fl *f);
void	nbr_bonus_write(t_p *p, t_fl *f);
#endif