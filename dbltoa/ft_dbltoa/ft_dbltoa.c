/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dbltoa.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/03/11 20:13:27 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_dbltoa.h"

//	Static functions
static int16_t	dbltoa_convert(double value, t_dbl *strings);

/* ft_dbltoa()
 * This function converts a double or float to an char*.
 * you can either do:
 * Option 1:
 * double db = 2.8;
 * char* str = ft_dbltoa(db);
 * 
 * Option 2:
 * float fl = 2.8f;
 * char* str = ft_dbltoa(fl);
 * 
 * Both are possible, because the float is being cast into a double.
 * How is that possible?
 * Because the double is way bigger than a float an therefore can hold a max float.
 * 
 * For more information (https://github.com/llefranc/42_ft_printf)
 */
static int16_t	dbltoa_convert(double value, t_dbl *strings)
{
	int16_t		digitexpo;			// stores the exponent
	char		numerator[MAX_DBL_STR_LEN + 1]; 	// storing the numerator
	char		denominator[MAX_DBL_STR_LEN + 1]; 	// storing the denominator
	bool 		is_neg;
	uint16_t	result_len;

	is_neg = true;
	intialize_string(numerator);
	intialize_string(denominator);
	strings->s1 = numerator;
	strings->s2 = denominator;
	// strings->inf_or_nan = 0;
	if (fraction_conversion(value, strings, &is_neg) == false)
	{
		// strings->inf_or_nan = ft_strlen(strings->result);
		// return (strings->inf_or_nan);
		return (ft_strlen(strings->result));
	}
	scientific_notation(numerator, denominator, &digitexpo, value);
	double_to_string(strings, digitexpo);
	result_len = process_number_string(strings->result, is_neg);
	if (strings->prec == UINT16_MAX)
		return (result_len);
	return (process_precision(strings->result, strings->prec));
}

char	*dbltoa(double value)
{
	char	result[MAX_DBL_STR_LEN + 1];
	t_dbl	strings;

	strings.result = result;
	// strings.prec = UINT16_MAX;
	strings.prec = 6;
	dbltoa_convert(value, &strings);
	return (ft_strdup(result));
}

char	*dbltoa_precision(double value, uint16_t prec)
{
	char	result[MAX_DBL_STR_LEN + 1];
	t_dbl	strings;

	strings.result = result;
	strings.prec = prec;
	dbltoa_convert(value, &strings);
	return (ft_strdup(result));
}

uint16_t	integer_part_length(double nbr)
{
	uint16_t len;

	// printf("first\n");
	len = 0;
	if (nbr < 0) {
		++len;
		nbr = -nbr;
	}
	// printf("%hu")
	// printf("second\n");
    while (nbr >= 1) {
        len++;
        nbr /= 10;
    }
	
	len += (len == 0);
	// printf("third\n");
	return (len);
}

uint16_t	dbltoa_buff(double value, char *buff, uint16_t b_size)
{
	char		result[MAX_DBL_STR_LEN + 1];
	t_dbl		strings;
	uint16_t	result_len;

	if (b_size == 1)
		buff[0] = '\0';
	if (b_size <= 1)
		return (b_size);
	strings.result = result;
	strings.prec = UINT16_MAX;
	result_len = dbltoa_convert(value, &strings);

	if (b_size <= result_len)
	{
		ft_strlcpy(buff, result, b_size);
		--b_size;
		if (buff[b_size - 1] == '.')
		{
			buff[b_size - 1] = '\0';
			--b_size;
		}
		return (b_size);
	}
	ft_strlcpy(buff, result, result_len);
	return (result_len);
}
// uint16_t	dbltoa_buff(double value, char *buff, uint16_t b_size)
// {
// 	char		result[MAX_DBL_STR_LEN + 1];
// 	t_dbl		strings;
// 	uint16_t	result_len;

// 	if (b_size == 1)
// 		buff[0] = '\0';
// 	if (b_size <= 1)
// 		return (b_size);
// 	strings.result = result;
// 	strings.prec = UINT16_MAX;
// 	result_len = dbltoa_convert(value, &strings);

// 	// uint16_t	dot_index = 0;
// 	// uint16_t	res_index = 0;
// 	// while (res_index < result_len)
// 	// {
// 	// 	if (result[res_index] == '.')
// 	// 		dot_index = res_index;
// 	// }
// 	// integer_part_length() shouldn't handle INFINITY and NAN
// 	if (b_size <= result_len)
// 	{
// 		ft_strlcpy(buff, result, b_size);
// 		--b_size;
// 		// printf("%hu  %hu\n", b_size, strings.inf_or_nan);
// 		// if (strings.inf_or_nan > 0 && b_size < strings.inf_or_nan)
// 		// {
// 		// 	ft_memset(buff, '\0', b_size);
// 		// 	return (0);
// 		// }
// 		// // printf("1  %hu   %s\n", b_size, buff);
// 		if (buff[b_size - 1] == '.')
// 		{
// 			buff[b_size - 1] = '\0';
// 			--b_size;
// 		}
// 		// printf("2  %hu   %s\n", b_size, buff);
// 		return (b_size);
// 	}
// 	ft_strlcpy(buff, result, result_len);
// 	// printf("\n%hu\n", result_len);
// 	return (result_len);
// }

// uint16_t	dbltoa_buff(double value, char *buff, uint16_t b_size)
// {
// 	int16_t			digitexpo;			// stores the exponent
// 	char			numerator[MAX_DBL_STR_LEN + 1]; 	// storing the numerator
// 	char			denominator[MAX_DBL_STR_LEN + 1]; 	// storing the denominator
// 	bool 			is_neg;
// 	t_dbl			strings;

// 	is_neg = true;
// 	// initialization numerator and denominator (filling them with zeros)
// 	intialize_string(numerator);
// 	intialize_string(denominator);
	
// 	strings = (t_dbl){numerator, denominator, buff, false};
// 	if (fraction_conversion(value, &strings, &is_neg) == false)
// 	{
// 		if (strings.is_buffered == false)
// 			// return (ft_strdup(result));
// 		return (ft_strlen(strings.result));
// 	}
	
// 	// One digit infront of the '.'
// 	scientific_notation(numerator, denominator, &digitexpo, value);

// 	// Converts the processed numerator and denominator into a string
// 	double_to_string(&strings, digitexpo);
// 	// result = double_to_string(&strings, digitexpo);
// 	// printf(">%s\n", result);

// 	// Add Sign and remove extra zeros
// 	process_number_string(strings.result, is_neg);
// 	// if (strings.is_buffered == false)
// 		// return (ft_strdup(result));

// 	(void)b_size;	// use for precision
// 	return (ft_strlen(strings.result));
// }