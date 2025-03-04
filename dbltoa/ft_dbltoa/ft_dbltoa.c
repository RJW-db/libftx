/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dbltoa.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 17:26:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2025/03/04 19:46:51 by rde-brui      ########   odam.nl         */
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
char	*ft_dbltoa(double ogNum)
{
	int			digitexpo;			// stores the exponent
	char			numerator[BIG_INT + 1]; 	// storing the numerator
	char			denominator[BIG_INT + 1]; 	// storing the denominator
	// char			numerator[MAX_DBL_STR_LEN]; 	// storing the numerator
	// char			denominator[MAX_DBL_STR_LEN]; 	// storing the denominator
	char			*str;			// final string representation of the double
	bool 			n_flag;

	n_flag = true;
	// initialization numerator and denominator (filling them with zeros)
	init_bigChar(numerator);
	init_bigChar(denominator);

	// Convert dbl into a fraction
	str = convert_to_fraction(ogNum, numerator, denominator, &n_flag);
	if (str != NULL)
		return (str);
	
	// One digit infront of the '.'
	convert_to_sci_notation(numerator, denominator, &digitexpo, ogNum);

	// Converts the processed numerator and denominator into a string
	str = convert_to_str(str, numerator, denominator, digitexpo);

	// Add Sign and remove extra zeros
	str = ft_add_sign(str, n_flag);
	// str = ft_add_sign(str, (bit_string[0] == '0'));
	
	return (str);
}

