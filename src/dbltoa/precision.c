/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   precision.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/11 20:02:40 by rjw           #+#    #+#                 */
/*   Updated: 2025/03/14 21:41:58 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <dbltoa.h>

//	Static functions
static void		handle_carry(char *s1, int16_t *len, int16_t i, int16_t *carry);
static uint16_t	add_precision(char *s1, const char *s2);
static uint16_t	set_precision(char *result, uint16_t prec, uint16_t dot_index);

uint16_t	zero_padding(char *result, bool is_dot, uint16_t prec)
{
	char		*tmp;
	uint16_t	i;
// printf(">%s<\n", result);
// printf("   %hu\n", prec);
// exit(0);
	tmp = result;
	if (is_dot == true)
	{
		// puts("nope");
		tmp[0] = '.';
		++tmp;
	}
	i = 0;
	// puts("yur");
	// printf("%hu\n", prec);
	// exit(0);
	while (i < prec)
	{
		tmp[i] = '0';
		++i;
		// printf("%hu\n", i);
	}
	// puts("yur");

	// printf(">%c<\n", tmp[1]);
	// printf(">%s<\n", tmp);
	// printf(">%hu<\n", i);
	tmp[i] = '\0';
	// printf("result %s\n", result - 3);
	// printf("%hu\n", i +is_dot);
	// puts(result - 3);
	// exit(0);
	return (i + is_dot);
}
bool	is_only_zero_decimals(char *result)
{
	uint16_t zeros;

	zeros = 0;
	while (result[zeros] == '0')
	{
		++zeros;
	}
	if (result[zeros] != '\0')
		return (false);
	return (true);
}

uint16_t	inbetween(char *result, uint16_t res_len, uint16_t prec, bool is_neg)
{
	if (is_neg == true && result[0] == '0' && (result[1] != '.' || is_only_zero_decimals(result + 2) == true))
	{
		cpy_str(result - is_neg, result);
		is_neg = false;
		--result;
	}
	if (prec == 0)
		return (res_len + is_neg);
	uint16_t new_dot_index = 0;
	while (result[new_dot_index] != '\0' && result[new_dot_index] != '.')
		++new_dot_index;
	if (result[new_dot_index] == '\0') {
		zero_padding(result + new_dot_index, true, prec);
		return (res_len + is_neg + true + prec);
	}
	uint16_t	decimal_count = 0;
	while (result[new_dot_index + 1 /* +1 skip . */ + decimal_count] != '\0') {
		++decimal_count;
	}
	uint16_t pad_zero = 0;
	if (prec > decimal_count) {
		pad_zero = prec - decimal_count;
		zero_padding(result + new_dot_index + 1 + decimal_count, false, pad_zero);
		return (res_len + is_neg + pad_zero);
	}
	return (res_len + is_neg);
}

uint16_t	process_precision(char *result, uint16_t prec)
{
	uint16_t	res_index;
	uint16_t	res_len;
	bool		is_neg;
	uint16_t	padding;

	if (result[0] == '-' && result[1] == '0' && result[2] == '\0')
		cpy_str(result, "0");
	is_neg = (*result == '-');
	if (is_neg == true)
		result += is_neg;
	res_index = 0;
	while (result[res_index] != '\0')
	{
		if (result[res_index] == '.')
		{
			res_len = set_precision(result, prec, res_index);
			return (inbetween(result, res_len, prec, is_neg));
		}
		++res_index;
	}
	padding = 0;
	if (prec > 0)
		padding = zero_padding(result + res_index, true, prec);
	return (res_index + is_neg + padding);
}

static uint16_t	set_precision(char *result, uint16_t prec, uint16_t dot_index)
{
	char		rounding_increment[MAX_DBL_STR_LEN + 1];
	uint16_t	prec_index;
	char		rounding_nbr;

	prec_index = 0;
	while (result[dot_index + prec_index] != '\0' && prec_index <= prec)
		++prec_index;
	rounding_nbr = result[dot_index + prec_index];
	result[dot_index + prec_index] = '\0';
	if (rounding_nbr >= '5')
	{
		ft_memset(rounding_increment, '0', prec_index);
		rounding_increment[1] = '.';
		rounding_increment[prec_index] = '1';
		rounding_increment[prec_index + 1] = '\0';
		return (add_precision(result, rounding_increment));
	}
	if (result[dot_index + prec_index - 1] == '.')
	{
		--prec_index;
		result[dot_index + prec_index] = '\0';
	}
	return (dot_index + prec_index);
}

static uint16_t	add_precision(char *s1, const char *s2)
{
	int16_t	s1_len;
	int16_t	carry;
	int16_t	i;
	int16_t	j;

	s1_len = ft_strlen(s1) - 1;
	j = ft_strlen(s2) - 1;
	carry = 0;
	i = s1_len;
	while (i >= 0 || j >= 0 || carry != 0)
	{
		if (i >= 0 && s1[i] != '.')
			carry += s1[i] - '0';
		if (j >= 0 && s2[j] != '.')
			carry += s2[j] - '0';
		handle_carry(s1, &s1_len, i, &carry);
		--i;
		--j;
	}
	i = s1_len;
	while (i > 0 && s1[i] == '0')
		--i;
	i -= (s1[i] == '.');
	s1[i + 1] = '\0';
	return (i + 1);
}

static void	handle_carry(char *s1, int16_t *len, int16_t i, int16_t *carry)
{
	if (i < 0 || s1[i] != '.')
	{
		if (i >= 0)
			s1[i] = (*carry % 10) + '0';
		else
		{
			charmove(s1 + 1, s1, ++(*len));
			s1[0] = (*carry % 10) + '0';
		}
		*carry /= 10;
	}
	else
		s1[i] = '.';
}
