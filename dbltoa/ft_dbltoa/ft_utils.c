/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/03/03 21:00:09 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_dbltoa.h"

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

/* fill_str()
 * The function pads a binary string with leading zeros to ensure it represents exactly 8 bits (1 byte).
 *
 * The function counts characters in str, because if already 8 Bits, it will return string.
 * Else it will continue with allocating memory for the missing leading zeros and
 * fill those missing 0 with zeros (ft_memset(zero, 48, 8 - i);).
 * At the end we just join the strings again.
 */
static char	*fill_str(char *str)
{
	int		i;
	char	*zero;
	char	*tmp;

	i = 0;
	while (str[i] != '\0')
		++i;
	if (i == 8)
		return (str);
	zero = malloc(8 - i + 1);
	if (zero == NULL)
		return (free(str), NULL);
	zero[8 - i] = '\0';
	ft_memset(zero, 48, 8 - i);
	tmp = zero;
	zero = strjoin_safe(zero, str);
	free(tmp);
	free(str);
	if (zero == NULL)
		return (NULL);
	return (zero);
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

/* str_bits()
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

union DoubleInt64 {
    double d;
    int64_t i;
};

char	*str_bits(unsigned char *type, size_t size)
{
	char			*strBits; 	// Hold the final binary string
	char			*tmp;		// Temporary string to hold each byte's binary form
	char			*tmp2;		// Used for concatenation

	strBits = NULL;
	while (size > 0)
	{
		// printf(">%lld<\n\n", (int64_t)(*type));
		tmp = itoa_base((int64_t)(*type), "01");
		if (tmp == NULL)
			return (NULL);
		tmp = fill_str(tmp);
		if (tmp == NULL)	//	if NULL everything will be freed inside fill_str
			return (NULL);
		tmp2 = strBits;
		strBits = strjoin_safe(tmp, tmp2);
		free(tmp);
		free(tmp2);
		if (strBits == NULL)
			return (NULL);
		++type;
		--size;
	}
	// exit(0);
	return (strBits);
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
