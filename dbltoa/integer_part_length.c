/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   integer_part_length.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/12 01:20:34 by rjw           #+#    #+#                 */
/*   Updated: 2025/03/12 01:29:30 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dbltoa.h"

//	Static Functions
static void	integer_part_length_tester(void);

int	main(void)
{
	integer_part_length_tester();
	return (0);
}

static void	integer_part_length_tester(void)
{
	printf("%hu\n", integer_part_length(0)); // 1
	printf("%hu\n", integer_part_length(1)); // 1
	printf("%hu\n", integer_part_length(01)); // 1
	printf("%hu\n", integer_part_length(__DBL_MIN__)); // 1
	printf("%hu\n", integer_part_length(__DBL_DENORM_MIN__)); // 1
	printf("%hu\n", integer_part_length(-1)); // 2
	printf("%hu\n", integer_part_length(123)); // 3
	printf("%hu\n", integer_part_length(-123)); // 4
	printf("%hu\n", integer_part_length(9999.6666)); // 4
	printf("%hu\n", integer_part_length(DBL_MIN_10_EXP)); // 4
	

	printf("%hu\n", integer_part_length(-123126877777777781062520432865268252910947010799856319324944859136.0)); // 67, .0 is discarded
	printf("%hu\n", integer_part_length(__DBL_MAX__)); // 309
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