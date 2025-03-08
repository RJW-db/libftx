/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dbltoa.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/03/08 02:33:34 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_dbltoa.h"

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
char	*dbltoa(double ogNum)
{
	int16_t			digitexpo;			// stores the exponent
	char			numerator[BIG_INT + 1]; 	// storing the numerator
	char			denominator[BIG_INT + 1]; 	// storing the denominator
	// char			numerator[MAX_DBL_STR_LEN]; 	// storing the numerator
	// char			denominator[MAX_DBL_STR_LEN]; 	// storing the denominator
	char			result[MAX_DIGIT + 1];
	bool 			n_flag;
	t_dbl			strings;

	n_flag = true;
	// initialization numerator and denominator (filling them with zeros)
	intialize_string(numerator);
	intialize_string(denominator);
	
	strings = (t_dbl){numerator, denominator, result, false};
	if (fraction_conversion(ogNum, &strings, &n_flag) == false)
	{
		if (strings.is_buffered == false)
			return (ft_strdup(result));
		// return (ft_strlen(strings.result));
	}
	
	// One digit infront of the '.'
	scientific_notation(numerator, denominator, &digitexpo, ogNum);

	// Converts the processed numerator and denominator into a string
	convert_to_str(&strings, digitexpo);
	// result = convert_to_str(&strings, digitexpo);
	// printf(">%s\n", result);

	// Add Sign and remove extra zeros
	ft_add_sign(result, n_flag);
	
	// if (strings.is_buffered == false)
		return (ft_strdup(result));
	// return (ft_strlen(strings.result));
}


uint16_t	dbltoa_buff(double ogNum, char *buff, uint16_t b_size)
{
	int16_t			digitexpo;			// stores the exponent
	char			numerator[BIG_INT + 1]; 	// storing the numerator
	char			denominator[BIG_INT + 1]; 	// storing the denominator
	// char			numerator[MAX_DBL_STR_LEN]; 	// storing the numerator
	// char			denominator[MAX_DBL_STR_LEN]; 	// storing the denominator
	// char			result[MAX_DIGIT + 1];
	bool 			n_flag;
	t_dbl			strings;

	n_flag = true;
	// initialization numerator and denominator (filling them with zeros)
	intialize_string(numerator);
	intialize_string(denominator);
	
	strings = (t_dbl){numerator, denominator, buff, false};
	if (fraction_conversion(ogNum, &strings, &n_flag) == false)
	{
		if (strings.is_buffered == false)
			// return (ft_strdup(result));
		return (ft_strlen(strings.result));
	}
	
	// One digit infront of the '.'
	scientific_notation(numerator, denominator, &digitexpo, ogNum);

	// Converts the processed numerator and denominator into a string
	convert_to_str(&strings, digitexpo);
	// result = convert_to_str(&strings, digitexpo);
	// printf(">%s\n", result);

	// Add Sign and remove extra zeros
	ft_add_sign(strings.result, n_flag);
	// if (strings.is_buffered == false)
		// return (ft_strdup(result));

	(void)b_size;	// use for precision
	return (ft_strlen(strings.result));
}