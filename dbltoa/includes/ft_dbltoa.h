/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dbltoa.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/02/26 19:01:38 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_DBLTOA_H
# define FT_DBLTOA_H


# include <stdio.h>
# include <stdarg.h>
# include <locale.h>
# include <stdlib.h>
# include <float.h>
# include <unistd.h>
# include <string.h>
# include <strings.h>
# include <ctype.h>
#include <stdbool.h>

# define MAX_DIGIT	1030
# define BIG_INT	1024 // DBL_MIN is the larges number -> has 1024 digits
# define MAX_DBL_STR_LEN 1077	//	longest subnormal number + terminator

typedef struct s_number
{
	int i_s1;   	// Index of the last character in s1
	int j_s2;   	// Index of the last character in s2
	int digit_s1;  	// Index of the first significant digit in s1
	int digit_s2;  	// Index of the first significant digit in s2
} t_number;

// CONVERTSION
char	*ft_dbltoa(double dbl);
char	*convert_to_fraction(double ogNum, char *nume, char *denom, bool *n_flag);
void	convert_to_sci_notation(char *num, char *deno, int *digitexpo, double ogNum);
char	*convert_to_str(char *dbl, char *num, char *deno, int digitexp);
char	*convert_binary_to_decimal(char *nbr, char *base_from, char *base_to);


// MATH
char	*ft_add(char *s1, char *s2);
char	*ft_subs(char *s1, char *s2);
char	*ft_multi(char *s1, char *s2);
char	*ft_divi(char *s1, char *s2);

// UTILS
void	init_bigChar(char *str);
void	init_struct(char *s1, char *s2, t_number *num);
char	*error_inf(double dbl, unsigned long mantissa);
char	*ft_add_sign(char *dblStr, bool n_flag);
int	compare_str(char *s1, char *s2);
char	*str_bits(void *type, size_t size);
long	ft_basecheck(char *base_from);
long	ft_atoi_b(char *nbr, char *base_from, long basevalue, long *sig);
long	ft_init_malloc(char *nbrconv, long len);


void ft_bzero(void *str, size_t size_n);
char *ft_strdup(const char *str);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memmove(void *dst, const void *src, size_t len);
size_t				ft_strlen(const char *s);
double				ft_pow(double nb, double power);
char				*ft_strchr(const char *s, int c);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
long				ft_atoi(const char *str);
char				*ft_substr(const char *s, unsigned int start, size_t len);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_itoa(long n);
char				*ft_itoa_base(long n, const char *base);
void				ft_putstr_fd(char *s, int fd);


#endif
