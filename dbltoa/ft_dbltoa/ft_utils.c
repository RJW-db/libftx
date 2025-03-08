/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/03/08 03:07:52 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_dbltoa.h"

#if defined(__linux__)
# define NEGATIVE_NAN_INDEX 0
#else
# define NEGATIVE_NAN_INDEX 1
// #elif defined(__APPLE__) && defined(__MACH__)
#endif

/* intialize_string()
 * The function takes str and fills it zeros (48 -> ASCII code for '0').
 * The first place of the string (str[0]) will be filled with a '+',
 * because the first place in binary is the sign holder, 
 * so we will fill it with a '+'
 */
void intialize_string(char *str)
{
	ft_memset(str, '0', BIG_INT);
	str[BIG_INT] = '\0';
	str[0] = '+';				// TODO check if this can be entirely removed
}

/* special_value()
 * This function handles errors related to floating-point numbers, 
 * specifically when dealing with special cases like "infinity" or "NaN" (Not a Number).
 * Example:
 * 		value = 1.0 and mantissa = 0, return "inf".
 *		value = -1.0 and mantissa = 0, return "-inf".
 *		value = 0.0 and mantissa = 0, return "nan".
 */
void	special_value(t_dbl *strs, double val, uint64_t mant, bool is_neg)
{
	const char	nan_strings[2][5] = {"-nan", "nan"};

	if (mant == 0 && val > 0)
		cpy_str(strs->result, "inf");
	else if (mant == 0 && val < 0)
		cpy_str(strs->result, "-inf");
	else
	{
		if (is_neg == false)
			cpy_str(strs->result, "nan");
		else
			cpy_str(strs->result, nan_strings[NEGATIVE_NAN_INDEX]);
	}
}

/* double_to_bits()
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
char	*double_to_bits(int64_t double_bits, char *bit_representation)
{
	char		byte_buffer[BYTE + 1];
	int16_t		byte_index;
	size_t		bit_index;
	size_t		bit_count;
	uint8_t		byte_value;

	bit_representation[DBL_BIT_COUNT] = '\0';
	byte_index = DBL_BYTES - 1;
	bit_index = 0;
	while (byte_index >= 0)
	{
		byte_value = double_bits >> (byte_index * BYTE) & BYTE_MASK;
		int64_base(byte_value, "01", byte_buffer, BYTE + 1);
		bit_count = BYTE - ft_strlen(byte_buffer);
		ft_memset(bit_representation + bit_index, '0', bit_count);
		cpy_str(bit_representation + bit_index + bit_count, byte_buffer);
		bit_index += BYTE;
		--byte_index;
	}
	return (bit_representation);
}

/* ft_add_sign()
 * This function formats a numeric string by performing the following operations:
 *   1) Removing unnecessary trailing zeros from the decimal part of the string.
 *   2) Ensuring proper decimal formatting by keeping exactly two decimal places if a decimal point is present.
 *   3) Adding a negative sign to the string if `is_neg` is false.
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
 *      - If `is_neg` is `false`, the function prepends a negative sign (`'-'`) to the resulting string.
 *      - If `is_neg` is `true`, no negative sign is added.
 *
 *   4. Step 4: Copy the formatted string:
 *      - The function copies the necessary portion of the original string into the result string, 
 * 		  skipping the first character if `is_neg` is true.
 */
void	ft_add_sign(char *result, bool is_neg)
{
	uint16_t	len;

	len = ft_strlen(result) - 1;
	while (len > 0 && result[len] == '0')
		--len;
	if (result[len] == '.' && result[0] == '0')
		--len;
	if (is_neg == false)
		ft_memmove(result + is_neg, result + 1, len);
	else
		result[0] = '-';
	result[len + is_neg] = '\0';
}

