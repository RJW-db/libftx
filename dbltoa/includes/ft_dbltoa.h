/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dbltoa.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/03/04 21:54:06 by rde-brui      ########   odam.nl         */
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
# include <stdbool.h>
# include <stdint.h>

# define BYTE_MASK 0xFF
# define DBL_BYTES 8
# define BYTE 8
# define DBL_BIT_COUNT 64

#define DECIMAL_NBR 10
#define DECIMAL_BASE "0123456789"
#define BINARY_NBR 2
#define BINARY_BASE "01"
#define HEXADECIMAL_BASE "0123456789ABCDEF"

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

typedef union	u_double_bitcast
{
	double d;
	int64_t i;
}	t_bitcast;

// CONVERTSION
char	*ft_dbltoa(double dbl);
char	*convert_to_fraction(double ogNum, char *nume, char *denom, bool *n_flag);
void	convert_to_sci_notation(char *num, char *deno, int *digitexpo, double ogNum);
char	*convert_to_str(char *dbl, char *num, char *deno, int digitexp);
bool 	binary_to_decimal(char *nbr, char *buff, size_t buff_size);

// MATH
char	*ft_add(char *s1, char *s2);
char	*ft_subs(char *s1, char *s2);
char	*ft_multi(char *s1, char *s2);
char	*ft_divi(char *s1, char *s2);

// UTILS
void	init_bigChar(char *str);
void	init_struct(char *s1, char *s2, t_number *num);
char	*error_inf(double dbl, uint64_t mantissa);
char	*ft_add_sign(char *dblStr, bool n_flag);
int		compare_str(char *s1, char *s2);
// char	*double_to_bitstring(unsigned char *type, size_t size);
// char	*double_to_bitstring(double num, uint16_t total_bytes);
char	*double_to_bitstring(t_bitcast cast, char *bit_string);
int64_t	ft_basecheck(char *base_from);
int64_t	ft_atoi_b(char *nbr, char *base_from, int64_t basevalue, int64_t *sig);

void ft_bzero(void *str, size_t size_n);
char *ft_strdup(const char *str);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memmove(void *dst, const void *src, size_t len);
size_t				ft_strlen(const char *s);
size_t				strlen_safe(const char *str);
char				*ft_strchr(const char *s, int c);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
long				atoi64(const char *str);
char				*ft_substr(char const *s, uint32_t start, size_t len);
void				substr_buff(const char *s, uint32_t start, size_t len, char *buff);
char				*strjoin_safe(char const *s1, char const *s2);
char				*ft_itoa(long n);
// char				*itoa_base(int64_t n, const char *base);
size_t				int64_base(int64_t n, const char *base, char *buff, size_t buf_len);
void				ft_putstr_fd(char *s, int fd);

size_t	cpy_str(char *dst, const char *src);
uint8_t	digit_counter(int64_t n, uint8_t base_len);
#endif
