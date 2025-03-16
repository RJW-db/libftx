/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dbltoa.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/12 01:27:15 by rjw           #+#    #+#                 */
/*   Updated: 2025/03/12 01:27:17 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <dbltoa.h>

//	Static functions
static uint16_t	dbltoa_convert(double value, t_dbl *strings, bool trim);

char	*dbltoa(double value)
{
	char	result[MAX_DBL_BUFF];
	t_dbl	strings;

	strings.result = result;
	strings.prec = UNLIMITED_PRECISION;
	// dbltoa_convert(value, &strings);
	return (ft_strdup(result));
}

char	*dbltoa_precision(double value, uint16_t prec)
{
	char	result[MAX_DBL_BUFF];
	t_dbl	strings;

	strings.result = result;
	strings.prec = prec;
	// dbltoa_convert(value, &strings);
	return (ft_strdup(result));
}

uint16_t	dbltoa_buff(double value, char *buff, uint16_t b_size)
{
	char		result[MAX_DBL_BUFF];
	t_dbl		strings;
	uint16_t	result_len;
// printf(">%f\n", value);
	if (buff == NULL)
		return (0);
	if (b_size == 1)
		buff[0] = '\0';
	if (b_size <= 1)
		return (b_size);
	strings.result = result;
	// strings.prec = UNLIMITED_PRECISION;
	strings.prec = 4;
	// result_len = dbltoa_convert(value, &strings);
	// printf("\n\n%s\n", result);
	// printf("%hu\n", result_len);
	if (b_size <= result_len)
	{

		ft_strlcpy(buff, result, b_size--);
		if (buff[b_size - 1] == '.')
		{
			buff[b_size - 1] = '\0';
			--b_size;
		}
		return (b_size);
	}
	// puts("result");
	ft_strlcpy(buff, result, result_len + 1);
	// puts(buff);
	return (result_len);
}

uint16_t	dbltoa_buff_prec(t_dbltoa_params dbl)
{
	char		result[MAX_DBL_BUFF];
	t_dbl		strings;
	uint16_t	result_len;
	if (dbl.buff != NULL && dbl.buff_size >= 1)
		dbl.buff[0] = '\0';
	if (dbl.buff == NULL || dbl.buff_size <= 1)
		return (0);
	strings.result = result;
	strings.prec = dbl.precision;
	result_len = dbltoa_convert(dbl.value, &strings, dbl.trim_trailing_zeros);
	if (dbl.buff_size < result_len)
	{
		ft_strlcpy(dbl.buff, result, dbl.buff_size);
		return (--dbl.buff_size);
	}
	// printf("%zu\n%hu\n", ft_strlcpy(dbl.buff, result, result_len + 1), result_len);
	return (ft_strlcpy(dbl.buff, result, result_len + 1));
}

// uint16_t	remove_trailing_zeros(char *result, uint16_t res_len)
// {
// 	while (result[res_len] == '0')
// 		--res_len;
// 	result[res_len + 1] = '\0';
// 	if (result[res_len] == '.')
// 		--res_len;
// 	result[res_len + 1] = '\0';
// 	return (0);
// }

static uint16_t	dbltoa_convert(double value, t_dbl *strings, bool trim)
{
	char		numerator[MAX_DBL_STR_LEN + 1];
	char		denominator[MAX_DBL_STR_LEN + 1];
	uint16_t	result_len;
	int16_t		digitexpo;
	bool		is_neg;

	is_neg = true;
	intialize_buff(numerator);
	intialize_buff(denominator);
	strings->s1 = numerator;
	strings->s2 = denominator;
	if (fraction_conversion(value, strings, &is_neg) == false)
		return (ft_strlen(strings->result));
	scientific_notation(numerator, denominator, &digitexpo, value);
	result_len = double_to_string(strings, digitexpo, is_neg);
	// if (result_len > 0 && trim == true) // double_to_string if doesn't find a dot return 0
	// 	(result_len);
	result_len = process_precision(strings->result, strings->prec);
	if (trim == true)
		return (trim_trailing_zeros(strings->result, result_len));	//	if double_to_string works like above, remove looking for dot in trim_trailing_zeros
	return (result_len);
}
