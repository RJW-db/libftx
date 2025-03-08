/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/03/08 01:02:47 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_dbltoa.h"

#if defined(__linux__)
# define NEGATIVE_NAN 0
#else
# define NEGATIVE_NAN 1
// #elif defined(__APPLE__) && defined(__MACH__)
#endif

/* init_bigChar()
 * The function takes str and fills it zeros (48 -> ASCII code for '0').
 * The first place of the string (str[0]) will be filled with a '+',
 * because the first place in binary is the sign holder, 
 * so we will fill it with a '+'
 */
void init_bigChar(char *str)
{
	ft_memset(str, '0', BIG_INT);
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
void	error_inf(t_dbl *strs, double ogNum, uint64_t mantissa, bool n_flag)
{
	const char	neg_nan[2][5] = {"-nan", "nan"};

	if (mantissa == 0 && ogNum > 0)
		cpy_str(strs->result, "inf");
	else if (mantissa == 0 && ogNum < 0)
		cpy_str(strs->result, "-inf");
	else
	{
		if (n_flag == false)
			cpy_str(strs->result, "nan");
		else
			cpy_str(strs->result, neg_nan[NEGATIVE_NAN]);
	}
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
char	*double_to_bitstring(int64_t dbl_to_int_cast, char *bit_string)
{
	char		buff[BYTE + 1];
	int16_t		byte_idx;
	size_t		index;
	size_t		nbr;
	uint8_t		byte_val;

	bit_string[DBL_BIT_COUNT] = '\0';
	index = 0;
	byte_idx = DBL_BYTES - 1;
	while (byte_idx >= 0)
	{
		byte_val = dbl_to_int_cast >> (byte_idx * BYTE) & BYTE_MASK;
		int64_base(byte_val, "01", buff, BYTE + 1);
		nbr = BYTE - ft_strlen(buff);
		ft_memset(bit_string + index, '0', nbr);
		cpy_str(bit_string + index + nbr, buff);
		index += BYTE;
		--byte_idx;
	}
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
void	ft_add_sign(char *result, bool n_flag)
{
	uint16_t	len;

	len = ft_strlen(result) - 1;
	while (len > 0 && result[len] == '0')
		--len;
	if (result[len] == '.' && result[0] == '0')
		--len;
	if (n_flag == false)
		ft_memmove(result + n_flag, result + 1, len);
	else
		result[0] = '-';
	result[len + n_flag] = '\0';
}

