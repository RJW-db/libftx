/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dbltoa.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/12 01:38:30 by rjw           #+#    #+#                 */
/*   Updated: 2025/03/12 03:10:32 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DBLTOA_H
# define DBLTOA_H

# include <math.h>	//	INFINITY, NAN
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

//	longest numbers -__DBL_DENORM_MIN__ is 1077 characters long
# define MAX_DBL_STR_LEN 1078

# define BYTE_MASK 0xFF
# define DBL_BYTES 8
# define BYTE 8
# define DBL_BIT_COUNT 64


# define DECIMAL_NBR 10
# define DECIMAL_BASE "0123456789"
# define BINARY_NBR 2
# define BINARY_BASE "01"
# define HEXADECIMAL_BASE "0123456789ABCDEF"

// IEEE 754 representation of -NAN
# define NEGATIVE_NAN_BITS 0xFFF8000000000000
# define DBL_EXP_BITS 11
# define DBL_EXP_DECIMAL_DIGITS 5
# define DBL_MANT_BITS 52
# define DBL_MANT_DECIMAL_DIGITS 16  // Maximum digits needed for mantissa
// 1023 (IEEE 754 exponent bias) + 52 (mantissa bit count)
# define DBL_EXP_NORMAL_BIAS 1075
// 1023 (IEEE 754 exponent bias) + 52 - 1 (subnormal adjustment)
# define DBL_EXP_SUBNORMAL_BIAS 1074
// 2047 (max exponent value in IEEE 754) - 1075 (DBL_EXP_NORMAL_BIAS)
# define DBL_EXP_MAX 972

typedef struct s_dbl
{
	char	*s1;
	char	*s2;
	char	*result;
	uint16_t	prec;
}	t_dbl;

typedef struct	s_nbr
{
	int32_t	i_s1;	// Index of the last character in s1
	int32_t	j_s2;	// Index of the last character in s2
	int32_t	sig_s1;	// Index of the first significant digit in s1
	int32_t	sig_s2;	// Index of the first significant digit in s2
}	t_nbr;

// CONVERTSION
char		*dbltoa(double dbl);
uint16_t	dbltoa_buff(double value, char *buff, uint16_t b_size);
bool		fraction_conversion(double value, t_dbl *strings, bool *is_neg);
void		scientific_notation(char *num, char *deno, int16_t *digitexpo, double value);
uint16_t	double_to_string(t_dbl *s, int16_t digit_exponent, bool is_neg);
bool		binary_to_decimal(const char *bin_str, char *dec_str, size_t size);
char		*populate_numerator(char *num_str, uint64_t mant, int16_t expo);
char		*populate_denominator(char *denom_str, int16_t expo, double value);
char		*pow2(char *exp_str, int64_t exponent);
// MATH
char		*ft_addition(char* s1, char* s2);
int16_t		ft_subtraction(char *s1, char *s2);
void		ft_multiply(char *s1, char *s2);
void		ft_division(char *s1, char *s2);

// UTILS
void		intialize_buff(char *buff);
void		init_struct(char *s1, char *s2, t_nbr *num);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

int64_t		atoi_base(const char *nbr_str, char *base, bool *is_neg);
void 		ft_bzero(void *str, size_t size_n);
char 		*ft_strdup(const char *str);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_memmove(void *dest, const void *src, size_t len);
size_t		ft_strlen(const char *s);
size_t		strlen_safe(const char *str);
char		*ft_strchr(const char *s, int c);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
int64_t		atoi64(const char *nptr);
void		extract_substr(const char *s, uint32_t start, size_t ln, char *buf);
char		*strjoin_safe(char const *s1, char const *s2);
size_t		int64_base(int64_t n, const char *base, char *buff, size_t b_len);
void		ft_putstr_fd(char *s, int fd);
size_t		find_char_not(const char *str, const char c1);
size_t		cpy_str(char *dst, const char *src);
uint8_t		digit_counter(int64_t n, uint8_t base_len);
uint64_t	abs_int64(int64_t n);

uint16_t	integer_part_length(double nbr);

uint16_t	process_precision(char *result, uint16_t prec);
#endif
