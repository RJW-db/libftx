/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dbltoa.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/03/10 02:53:21 by rjw           ########   odam.nl         */
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

#define DBL_MANT_DECIMAL_DIGITS 16  // Maximum digits needed for mantissa

#define DECIMAL_NBR 10
#define DECIMAL_BASE "0123456789"
#define BINARY_NBR 2
#define BINARY_BASE "01"
#define HEXADECIMAL_BASE "0123456789ABCDEF"

# define MAX_DIGIT	1030
# define BIG_INT	1024 // DBL_MIN is the larges number -> has 1024 digits
# define MAX_DBL_STR_LEN 1077	//	longest subnormal number + terminator

typedef struct	s_nbr
{
	int32_t	i_s1;	// Index of the last character in s1
	int32_t	j_s2;	// Index of the last character in s2
	int32_t	sig_s1;	// Index of the first significant digit in s1
	int32_t	sig_s2;	// Index of the first significant digit in s2
}	t_nbr;

typedef struct s_dbl
{
	char	*s1;
	char	*s2;
	char	*result;
	bool	is_buffered;
}	t_dbl;

// CONVERTSION
char		*dbltoa(double dbl);
uint16_t	dbltoa_buff(double value, char *buff, uint16_t b_size);
bool		fraction_conversion(double value, t_dbl *strings, bool *is_neg);
void		scientific_notation(char *num, char *deno, int16_t *digitexpo, double value);
void		double_to_string(t_dbl *s, int16_t digitexp);
bool		binary_to_decimal(const char *bin_str, char *dec_str, size_t size);

// MATH
void		ft_addition(char *s1, char *s2);
// char		*ft_addition(char* s1, char* s2);
// void		ft_subtraction(char *s1, char *s2);
int			ft_subtraction(char *s1, char *s2);

void		ft_multiply(char *s1, char *s2);
void		ft_division(char *s1, char *s2);

// UTILS
void		intialize_string(char *str);
void		init_struct(char *s1, char *s2, t_nbr *num);
void		special_value(t_dbl *strs, double val, uint64_t mant, bool is_neg);
void		ft_add_sign(char *dblStr, bool is_neg);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

char		*double_to_bits(int64_t dbl_to_int_cast, char *bit_string);
int64_t		atoi_base(const char *num_str, char *base, bool *is_neg);
void 		ft_bzero(void *str, size_t size_n);
char 		*ft_strdup(const char *str);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_memmove(void *dst, const void *src, size_t len);
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
#endif
