/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dbltoa.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/12 01:25:31 by rjw           #+#    #+#                 */
/*   Updated: 2025/03/12 01:25:38 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DBLTOA_H
# define FT_DBLTOA_H

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

# define DBL_MANT_DECIMAL_DIGITS 16  // Maximum digits needed for mantissa

# define DECIMAL_NBR 10
# define DECIMAL_BASE "0123456789"
# define BINARY_NBR 2
# define BINARY_BASE "01"
# define HEXADECIMAL_BASE "0123456789ABCDEF"

typedef struct s_dbl
{
	char	*s1;
	char	*s2;
	char	*result;
	// uint8_t	inf_or_nan;
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
void		double_to_string(t_dbl *s, int16_t digit_exponent);
bool		binary_to_decimal(const char *bin_str, char *dec_str, size_t size);

// MATH
// void		ft_addition(char *s1, char *s2);
char		*ft_addition(char* s1, char* s2);
// void		ft_subtraction(char *s1, char *s2);
int			ft_subtraction(char *s1, char *s2);

void		ft_multiply(char *s1, char *s2);
void		ft_division(char *s1, char *s2);

// UTILS
void		intialize_string(char *str);
void		init_struct(char *s1, char *s2, t_nbr *num);
void		special_value(t_dbl *strs, double val, uint64_t mant, bool is_neg);
uint16_t	process_number_string(char *dblStr, bool is_neg);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

char		*double_to_bits(int64_t dbl_to_int_cast, char *bit_string);
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

size_t		cpy_str(char *dst, const char *src);
uint8_t		digit_counter(int64_t n, uint8_t base_len);
uint64_t	abs_int64(int64_t n);

uint16_t	integer_part_length(double nbr);

uint16_t	process_precision(char *result, uint16_t prec);
#endif
