/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_precision_tester.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/12 01:15:54 by rjw           #+#    #+#                 */
/*   Updated: 2025/03/12 16:14:26 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <dbltoa.h>
#include <float.h>
#include <stdarg.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdio.h>

//	Static Functions
static void	process_precision_tester(void);
static void	single_precision(size_t index, char *input, char *exp, uint16_t prec);

int	main(void)
{
	process_precision_tester();
	return (0);
}

static void	process_precision_tester(void)
{
	single_precision(1, "0.4", "0", 0);
	single_precision(1, "-0.4", "0", 0);
	single_precision(1, "0.5", "1", 0);
	single_precision(1, "-0.5", "-1", 0);

	single_precision(1, "9.4", "9", 0);
	single_precision(1, "-9.4", "-9", 0);
	single_precision(1, "9.5", "10", 0);
	single_precision(1, "-9.5", "-10", 0);

	single_precision(1, "9.4", "9.4", 1);
	single_precision(1, "-9.4", "-9.4", 1);
	single_precision(1, "9.5", "9.5", 1);
	single_precision(1, "-9.5", "-9.5", 1);

	single_precision(1, "3.454", "3.45", 2);
	single_precision(1, "-3.454", "-3.45", 2);
	single_precision(1, "3.455", "3.46", 2);
	single_precision(1, "-3.455", "-3.46", 2);

	single_precision(1, "123.0999984", "123.099998", 6);
	single_precision(1, "-123.0999984", "-123.099998", 6);
	single_precision(1, "123.0999985", "123.099999", 6);
	single_precision(1, "-123.0999985", "-123.099999", 6);

	single_precision(1, "999.9999994", "999.999999", 6);
	single_precision(1, "-999.9999994", "-999.999999", 6);
	single_precision(1, "999.9999995", "1000", 6);
	single_precision(1, "-999.9999995", "-1000", 6);

	single_precision(1, "123.4999984", "123", 0);
	single_precision(1, "-123.4999984", "-123", 0);
	single_precision(1, "123.5999985", "124", 0);
	single_precision(1, "-123.5999985", "-124", 0);
}

static void	single_precision(size_t index, char *input, char *exp, uint16_t prec)
{
	char		result[MAX_DBL_STR_LEN + 1];

	cpy_str(result, input);
	uint16_t	exp_len = ft_strlen(exp);
	uint16_t	res_len = process_precision(result, prec);

	// printf("\n%hu   %s\n", exp_len, exp);
	// printf("%hu   %s\n", res_len, result);
	testing_dbltoa_b(index, (strncmp(result, exp, exp_len + 1) == 0), res_len == exp_len);
}
