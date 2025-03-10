/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dbltoa.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/03/10 21:08:12 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_dbltoa.h"

//	Static functions
static void	dbltoa_convert(double value, t_dbl *strings);

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
static void	dbltoa_convert(double value, t_dbl *strings)
{
	int16_t			digitexpo;			// stores the exponent
	char			numerator[MAX_DBL_STR_LEN + 1]; 	// storing the numerator
	char			denominator[MAX_DBL_STR_LEN + 1]; 	// storing the denominator
	bool 			is_neg;

	is_neg = true;
	intialize_string(numerator);
	intialize_string(denominator);
	strings->s1 = numerator;
	strings->s2 = denominator;
	if (fraction_conversion(value, strings, &is_neg) == false)
	{
		return ;
	}
	scientific_notation(numerator, denominator, &digitexpo, value);
	double_to_string(strings, digitexpo);
	ft_add_sign(strings->result, is_neg);
}

char	*dbltoa(double value)
{
	char	result[MAX_DBL_STR_LEN + 1];
	t_dbl	strings;

	strings.result = result;
	strings.is_buffered = false;
	dbltoa_convert(value, &strings);
	return (ft_strdup(result));
}



uint16_t	dbltoa_buff(double value, char *buff, uint16_t b_size)
{
	int16_t			digitexpo;			// stores the exponent
	char			numerator[MAX_DBL_STR_LEN + 1]; 	// storing the numerator
	char			denominator[MAX_DBL_STR_LEN + 1]; 	// storing the denominator
	bool 			is_neg;
	t_dbl			strings;

	is_neg = true;
	// initialization numerator and denominator (filling them with zeros)
	intialize_string(numerator);
	intialize_string(denominator);
	
	strings = (t_dbl){numerator, denominator, buff, false};
	if (fraction_conversion(value, &strings, &is_neg) == false)
	{
		if (strings.is_buffered == false)
			// return (ft_strdup(result));
		return (ft_strlen(strings.result));
	}
	
	// One digit infront of the '.'
	scientific_notation(numerator, denominator, &digitexpo, value);

	// Converts the processed numerator and denominator into a string
	double_to_string(&strings, digitexpo);
	// result = double_to_string(&strings, digitexpo);
	// printf(">%s\n", result);

	// Add Sign and remove extra zeros
	ft_add_sign(strings.result, is_neg);
	// if (strings.is_buffered == false)
		// return (ft_strdup(result));

	(void)b_size;	// use for precision
	return (ft_strlen(strings.result));
}