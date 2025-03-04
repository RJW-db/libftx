/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/03/04 17:44:03 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_dbltoa.h"
#define BYTE_MASK 0xFF
#define BYTE 8
size_t biggest = 0;

/* init_bigChar()
 * The function takes str and fills it zeros (48 -> ASCII code for '0').
 * The first place of the string (str[0]) will be filled with a '+',
 * because the first place in binary is the sign holder, 
 * so we will fill it with a '+'
 */
void init_bigChar(char *str)
{
	ft_memset(str, 48, BIG_INT);
	str[BIG_INT] = '\0';
	str[0] = '+';				// TODO check if this can be entirely removed
}

/* error_inf()
 * This function handles errors related to floating-point numbers, 
 * specifically when dealing with special cases like "infinity" or "NaN" (Not a Number).
 * Example:
 * 		ogNum = 1.0 and mantissa = 0, return "inf".
 *		ogNum = -1.0 and mantissa = 0, return "-inf".
 *		ogNum = 0.0 and mantissa = 0, return "nan".
 */
char	*error_inf(double ogNum, unsigned long mantissa)
{
	char			*dblStr;

	if (!mantissa && ogNum > 0)
		dblStr = ft_strdup("inf");
	else if (!mantissa && ogNum < 0)
		dblStr = ft_strdup("-inf");
	else
		dblStr = ft_strdup("nan");

	return (dblStr);
}

bool	dpstr_ok(char **s1)
{
	return (!(s1 == NULL || *s1 == NULL));
}

void	*free_str(char **str)
{
	if (dpstr_ok(str) == true)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}

/* double_to_bitstring()
 * Converts the void* (in this case double) into a string of bits.
 * So, 3.14 will turn into 01000000 00001001 00001100 11001100 11001100 11001100 11001100 11001100
 * 
 * It iterate over each byte of type and
 * Converts the current byte (*ptr) into an 8-bit binary string.
 * 		Example: (*ptr = 5, tmp = "00000101").
 * 		itoa_base() the base is "01" which will convert the string into binary.
 * 
 * If itoa_base doesn't return exactly 8 bits, fill_str() pads it with leading zeros. 
 * 		Example: (tmp = "101", it becomes "00000101")
 * 
 * And then it will joins the new tmp to the existing strBits
 */


/* fill_str()
 * The function pads a binary string with leading zeros to ensure it represents exactly 8 bits (1 byte).
 *
 * The function counts characters in str, because if already 8 Bits, it will return string.
 * Else it will continue with allocating memory for the missing leading zeros and
 * fill those missing 0 with zeros (ft_memset(zero, 48, 8 - i);).
 * At the end we just join the strings again.
 */
// static char	*fill_str(char *str)
// {
// 	int		i;
// 	char	*zero;
// 	char	*tmp;

// 	i = 0;
// 	while (str[i] != '\0')
// 		++i;
// 	if (i == 8)
// 		return (str);
// 	zero = malloc(8 - i + 1);
// 	if (zero == NULL)
// 		return (free(str), NULL);
// 	zero[8 - i] = '\0';
// 	ft_memset(zero, 48, 8 - i);
// 	tmp = zero;
// 	zero = strjoin_safe(zero, str);
// 	free(tmp);
// 	free(str);
// 	if (zero == NULL)
// 		return (NULL);
// 	return (zero);
// }

typedef union	u_double_bitcast
{
	double d;
	int64_t i;
}	t_double_bitcast;

// char *double_to_bitstring(double num, uint16_t total_bytes)
// {
// 	t_double_bitcast bitcast = { .d = num };
// 	char *bit_string = NULL;
// 	char *tmp;
// 	char *prev_bit_string;
// 	uint16_t byte_idx;

// 	for (byte_idx = 0; byte_idx < total_bytes; ++byte_idx)
// 	{
// 		// Matches your original implementation's byte extraction
// 		tmp = itoa_base(((bitcast.i >> (byte_idx * BYTE)) & BYTE_MASK), "01");
// 		// *tmp = 1;
// 		printf(">%s\n", tmp);
// 		if (tmp == NULL)
// 			return (NULL);

// 		tmp = fill_str(tmp);
// 		if (tmp == NULL)
// 			return (NULL);
// 		printf(">%s\n", tmp);
// 		prev_bit_string = bit_string;
// 		bit_string = strjoin_safe(tmp, prev_bit_string);
// 		printf(">%s\n", bit_string);

// 		free(tmp);
// 		free(prev_bit_string);
// 		if (bit_string == NULL)
// 			return (NULL);
// 	}
// 	// printf("%zu\n", ft_strlen(bit_string));
// 	printf(">%d\n", total_bytes * 8 + 1);
// 	printf("%s\n", bit_string);
// 	return (bit_string);
// }

uint64_t	int64_to_abs(int64_t n)
{
	if (n >= 0)
		return ((uint64_t)n);
	return (uint64_t)((-(n + 1)) + 1);
}

size_t	int64_base(int64_t n, const char *base, char *buff, size_t buf_len)
{
	const bool	is_negative = (n < 0);
	size_t		base_len;
	uint64_t	abs_value;
	size_t		index;
	uint8_t		num_digits;

	abs_value = int64_to_abs(n);
	base_len = strlen_safe(base);
	if (base_len < 2 || buf_len < 2)
		return ((buf_len != 0 && ft_strlcpy(buff, "\0", 1)), 0);
	num_digits = digit_counter(n, base_len);
	while (num_digits-- >= buf_len)
		abs_value /= base_len;
	index = buf_len - 1;
	buff[index] = '\0';
	while ((abs_value > 0 && index > 0) || index == buf_len - 1)
	{
		buff[--index] = base[abs_value % base_len];
		abs_value /= base_len;
	}
	if (is_negative && index > 0)
		buff[--index] = '-';
	if (index > 0)
		ft_strlcpy(buff, buff + index, buf_len - index);
	return (buf_len - index - 1);
}

size_t	cpy_str_only(char *dst, const char *src)
{
	size_t	i;
	char	c;

	i = 0;
	c = src[i];
	while (c != '\0')
	{
		dst[i] = c;
		++i;
		c = src[i];
	}
	return (i);
}
char *double_to_bitstring(double num, uint16_t total_bytes)
{
	t_double_bitcast bitcast = { .d = num };
	uint16_t byte_idx;
	size_t index = (total_bytes * 8 + 1) - 9;
	size_t len = 0;
	char buff[BYTE + 1];
	char *bit_string = malloc(total_bytes * 8 + 1);
	bit_string[total_bytes * 8] = '\0';
	ft_memset(bit_string, '5', total_bytes * 8);
	for (byte_idx = 0; byte_idx < total_bytes; ++byte_idx)
	{
		size_t check = int64_base(((bitcast.i >> (byte_idx * BYTE)) & BYTE_MASK), "01", buff, BYTE + 1);
		if(check > biggest)
			biggest = check;
		len = ft_strlen(buff);

		ft_memset(bit_string + index, 48, 8 - len);
		cpy_str_only(bit_string + index + (8 - len), buff);
		if (index > 0)	// remove this if out if i don't need it anymore for printing
			index -= 8;
	}
	// printf("%zu\n", ft_strlen(bit_string));
	// printf(">%d<\n", total_bytes * 8 + 1);
	// printf(">%d<\n", (total_bytes * 8 + 1) - 9);
	// printf("%s\n", bit_string + index);
	// printf("%zu\n", index);
	// printf("%s\n", bit_string);

	return (bit_string);
}

/* ft_add_sign()
 * This function formats a numeric string by performing the following operations:
 *   1) Removing unnecessary trailing zeros from the decimal part of the string.
 *   2) Ensuring proper decimal formatting by keeping exactly two decimal places if a decimal point is present.
 *   3) Adding a negative sign to the string if `n_flag` is false.
 *
 * Steps:
 *   1. Step 1: Trim trailing zeros:
 *      - The function iterates from the end of the string, removing any trailing zeros after the decimal point.
 *      - If a decimal point remains after trimming, the function ensures that exactly two decimal places are kept -> 123.00
 *
 *   2. Step 2: Memory allocation:
 *      - Allocate memory for the resulting string, accounting the extra 2zeros and negative sign.
 *
 *   3. Step 3: Handle negative sign:
 *      - If `n_flag` is `false`, the function prepends a negative sign (`'-'`) to the resulting string.
 *      - If `n_flag` is `true`, no negative sign is added.
 *
 *   4. Step 4: Copy the formatted string:
 *      - The function copies the necessary portion of the original string into the result string, 
 * 		  skipping the first character if `n_flag` is true.
 */
char *ft_add_sign(char *dblStr, bool n_flag)
{
	int len;
	char *result;

	len = ft_strlen(dblStr) - 1;
	// Step 1:
	while (len > 0 && dblStr[len] == '0')
		--len;
	if (dblStr[len] == '.' && dblStr[0] == '0')
		--len;
	// Step 2:
	result = (char*)malloc(len + n_flag + 1);
	if (!result)
		return (NULL);
	
	// Step 3:
	if (n_flag == true)
		result[0] = '-';

	// Step 4:
	strncpy(result + n_flag, dblStr + 1, len);	// TODO: use libft ft_strncpy
	result[len + n_flag] = '\0';

	free(dblStr);
	return (result);
}
