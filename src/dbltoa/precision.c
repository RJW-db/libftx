/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   precision.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/11 20:02:40 by rjw           #+#    #+#                 */
/*   Updated: 2025/03/13 21:25:36 by rde-brui      ########   odam.nl         */
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
	// exit(0);
	return (i + is_dot);
}

uint16_t	process_precision(char *result, uint16_t prec)
{
	uint16_t	res_index;
	uint16_t	dot_index;
	bool		is_neg;

	is_neg = false;
	if (*result == '-')
	{
		if (result[1] == '0' && result[2] == '\0') {
		// puts("hier");
			cpy_str(result, "0");
		}
		else {
			is_neg = true;
			result += is_neg;
		}
	}
	res_index = 0;
	while (result[res_index] != '\0')
	{
		if (result[res_index] == '.')
		{
			// puts(result - is_neg);
			dot_index = res_index;
			res_index = set_precision(result, prec, res_index);
			if (res_index == 1 && is_neg == true && result[0] == '0')
			{
				// puts("\nhier");
				// puts(result);
				cpy_str(result - is_neg, result);
				is_neg = false;
			}
			// puts("yur");
			// puts(result - 1);
			// exit(0);
			// while (kijken vanaf dot_index of kleiner is dan precision, so ja vullen met padding)
			uint16_t pad_index = 0;
			if (prec != 0) {
				dot_index += 1;
				while (result[dot_index + pad_index] != '\0' && pad_index < prec - 1)
					++pad_index;
			}

			printf("pad_index %hu\n", pad_index);
			// printf("check %hu\n", prec - pad_index);
			printf("\n>>>%s<\n", result - 1);
			
			
			// printf(">%hu<\n", pad_index);
			// printf(">%hu<\n", dot_index);
			// printf(">%hu<\n", prec);
			// printf(">%hu<\n", is_neg);
			// if (pad_index < prec/*  && result[1] == '\0' */)
			if (pad_index < prec && (pad_index != 0 && prec != 1))
				zero_padding(result + (dot_index + 0) + pad_index, false, prec - pad_index);
			// else
			// 	puts("nope");
			printf(">>%s<\n", result - 1);
			// printf(">>%s<\n", result + res_index);
			// printf("return %hu\n", (dot_index + 1) + pad_index + is_neg);
			// printf("\t %hu\n", (dot_index + 1) + prec + is_neg);

			return ((dot_index) + prec + is_neg);
			// return (res_index + is_neg);
			// break ;
		}
		++res_index;
	}
	// puts("yur");
	// puts(result);
	// puts(result + res_index - 1);
	// printf("%hu\n", prec);
	
	uint16_t pad = 0;
	
	// puts(result);
	if (prec > 0) {
		pad = zero_padding(result + res_index, true, prec);
	}
	// puts(result);
	return (res_index + is_neg + pad);
	// return (cpy_str(result + res_index, ".00") + res_index + is_neg);
	// return (res_index + is_neg);
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
