#include "includes/ft_dbltoa.h"
#include <float.h>
#include <math.h>

# define RESET			"\033[0m"
# define BOLD			"\033[1m"
# define ITALIC			"\033[3m"
# define RED			"\033[31m"
# define GREEN			"\033[32m"
# define YELLOW			"\033[0;33m"
# define BLUE			"\033[0;34m" 
# define MAGENTA		"\033[35m"

void		testing_dbltoa_b(size_t index, bool str_check, bool nbr_check);
uint16_t	format_double_b(char *expected, size_t size, double input);
bool		single_test_b(size_t index, double input, size_t buff_len);
void		float_tests_b(void);
void		double_tests_b(void);
void		edgecase_tests_b(void);
void		random_tests_b(void);
void		linear_range_tests_b(void);
void		power_of_ten_tests_b(void);
void		subnormal_to_max_tests_b(void);
void		negative_power_of_ten_tests_b(void);


int	main(void)
{
	float_tests_b();
	double_tests_b();
	edgecase_tests_b();
	random_tests_b();
	linear_range_tests_b();
	power_of_ten_tests_b();
	subnormal_to_max_tests_b();
	negative_power_of_ten_tests_b();
	return (0);
}

void	testing_dbltoa_b(size_t index, bool str_check, bool nbr_check)
{
	const char *table[4] = {
		RED "%zu.KO " RESET,
		YELLOW "%zu.KO " RESET,
		BLUE "%zu.KO " RESET,
		GREEN "%zu.OK " RESET
	};
    int table_index = (str_check << 1) | nbr_check;

    printf((table[table_index]), index);
}

uint16_t	format_double_b(char *expected, size_t size, double input)
{
	snprintf(expected, size, "%.1075f", input);
	uint16_t exp_nbr = strlen(expected) - 1;

	while (expected[exp_nbr] == '0') {
		expected[exp_nbr] = '\0';
		--exp_nbr;
	}
	if (expected[exp_nbr] == '.') {
		expected[exp_nbr] = '\0';
		--exp_nbr;
	}
	return (exp_nbr + 1);
}

bool	single_test_b(size_t index, double input, size_t buff_len)
{
	char expected[MAX_DBL_STR_LEN];
	char result[MAX_DBL_STR_LEN];

	uint16_t exp_nbr = format_double_b(expected, buff_len, input);
	uint16_t res_nbr = dbltoa_buff(input, result, buff_len);

	// printf("%hu   %s\n", exp_nbr, expected);
	// printf("%hu   %s\n", res_nbr, result);

	testing_dbltoa_b(index, (strncmp(result, expected, exp_nbr + 1) == 0), res_nbr == exp_nbr);
	return (0);
}

void	float_tests_b(void)
{
	printf("float_tests_b\n");
	single_test_b(1, -0.0F, MAX_DBL_STR_LEN);
	single_test_b(2, 0.0F, MAX_DBL_STR_LEN);
	single_test_b(3, +0.0F, MAX_DBL_STR_LEN);

	single_test_b(4, -1.0F, MAX_DBL_STR_LEN);
	single_test_b(5, 1.0F, MAX_DBL_STR_LEN);
	single_test_b(6, +1.0F, MAX_DBL_STR_LEN);

	single_test_b(7, -1.5F, MAX_DBL_STR_LEN);
	single_test_b(8, 1.5F, MAX_DBL_STR_LEN);
	single_test_b(9, +1.5F, MAX_DBL_STR_LEN);

	single_test_b(10, -1.0000000000000001F, MAX_DBL_STR_LEN);
	single_test_b(11, 1.0000000000000001F, MAX_DBL_STR_LEN);
	single_test_b(12, +1.0000000000000001F, MAX_DBL_STR_LEN);

	single_test_b(13, -0.9999999999999999F, MAX_DBL_STR_LEN);
	single_test_b(14, 0.9999999999999999F, MAX_DBL_STR_LEN);
	single_test_b(15, +0.9999999999999999F, MAX_DBL_STR_LEN);
	printf("\n");
}

void	double_tests_b(void)
{
	printf("double_tests_b\n");
	single_test_b(1, -0.0, MAX_DBL_STR_LEN);
	single_test_b(2, 0.0, MAX_DBL_STR_LEN);
	single_test_b(3, +0.0, MAX_DBL_STR_LEN);

	single_test_b(4, -1.0, MAX_DBL_STR_LEN);
	single_test_b(5, 1.0, MAX_DBL_STR_LEN);
	single_test_b(6, +1.0, MAX_DBL_STR_LEN);

	single_test_b(7, -1.5, MAX_DBL_STR_LEN);
	single_test_b(8, 1.5, MAX_DBL_STR_LEN);
	single_test_b(9, +1.5, MAX_DBL_STR_LEN);

	single_test_b(10, -1.0000000000000001, MAX_DBL_STR_LEN);
	single_test_b(11, 1.0000000000000001, MAX_DBL_STR_LEN);
	single_test_b(12, +1.0000000000000001, MAX_DBL_STR_LEN);

	single_test_b(13, -0.9999999999999999, MAX_DBL_STR_LEN);
	single_test_b(14, 0.9999999999999999, MAX_DBL_STR_LEN);
	single_test_b(15, +0.9999999999999999, MAX_DBL_STR_LEN);
	printf("\n");
}

void	edgecase_tests_b(void)
{
	printf("edgecase_tests_b\n");
	single_test_b(1, 0, MAX_DBL_STR_LEN);
	single_test_b(2, -1, MAX_DBL_STR_LEN);
	single_test_b(3, 1, MAX_DBL_STR_LEN);

	single_test_b(4, __DBL_MAX__, MAX_DBL_STR_LEN);
	single_test_b(5, __DBL_MIN__, MAX_DBL_STR_LEN);
	single_test_b(6, __DBL_EPSILON__, MAX_DBL_STR_LEN);			// Smallest difference between two doubles
	single_test_b(7, __DBL_DENORM_MIN__, MAX_DBL_STR_LEN);		// Smallest subnormal number

	single_test_b(8, DBL_MAX_EXP, MAX_DBL_STR_LEN);				// Maximum binary exponent (+1024)
	single_test_b(9, DBL_MIN_EXP, MAX_DBL_STR_LEN);				// Minimum binary exponent (-1021 for normal, subnormals go lower)
	single_test_b(10, DBL_MANT_DIG, MAX_DBL_STR_LEN);			// Number of bits in mantissa (53)
	single_test_b(11, DBL_DIG, MAX_DBL_STR_LEN);				// Max decimal digits of precision (15-17)
	single_test_b(12, DBL_MAX_10_EXP, MAX_DBL_STR_LEN);			// Max base-10 exponent (≈308)
	single_test_b(13, DBL_MIN_10_EXP, MAX_DBL_STR_LEN);			// Min base-10 exponent (≈-307)

	single_test_b(14, INFINITY, MAX_DBL_STR_LEN);
	single_test_b(15, -INFINITY, MAX_DBL_STR_LEN);
	single_test_b(16, NAN, MAX_DBL_STR_LEN);					// Any NaN (implementation-defined)
	single_test_b(17, -NAN, MAX_DBL_STR_LEN);					// Negative NaN

	single_test_b(18, -__DBL_MAX__, MAX_DBL_STR_LEN);
	single_test_b(19, -__DBL_MIN__, MAX_DBL_STR_LEN);
	single_test_b(20, -__DBL_DENORM_MIN__, MAX_DBL_STR_LEN);
	single_test_b(21, -__DBL_EPSILON__, MAX_DBL_STR_LEN);

	single_test_b(22, pow(10, DBL_MAX_10_EXP), MAX_DBL_STR_LEN);// Max possible power of 10
	single_test_b(23, pow(10, DBL_MIN_10_EXP), MAX_DBL_STR_LEN);// Smallest power of 10
	single_test_b(24, 1.0 + DBL_EPSILON, MAX_DBL_STR_LEN);		// Just above 1.0
	single_test_b(25, 1.0 - DBL_EPSILON, MAX_DBL_STR_LEN);		// Just below 1.0
	printf("\n");
}

void	random_tests_b(void)
{
	printf("random_tests_b\n");
	single_test_b(1, -1231246524059005808017408.0F, MAX_DBL_STR_LEN);
	single_test_b(2, -123126877777777781062520432865268252910947010799856319324944859136.0, MAX_DBL_STR_LEN);
	single_test_b(3, 0.1234567891234567837965840908509562723338603973388671875, MAX_DBL_STR_LEN);
	single_test_b(4, -1234567837723.123535, MAX_DBL_STR_LEN);
	printf("\n");
}

void	linear_range_tests_b(void)
{
	size_t	index = 1;

	printf("linear_range_tests_b\n");
	for (double i = -50; i <= 50; i += 0.1)
	{
		single_test_b(index, i, MAX_DBL_STR_LEN);
		++index;
	}
	printf("\n");
}

void	power_of_ten_tests_b(void)
{
	size_t	index = 1;

	printf("power_of_ten_tests_b\n");
	for (double i = 1.0; i < __DBL_MAX__; i *= 10)
	{
		single_test_b(index, i, MAX_DBL_STR_LEN);
		++index;
	}
	printf("\n");
}

void	subnormal_to_max_tests_b(void)
{
	size_t	index = 1;

	printf("subnormal_to_max_tests_b\n");
	for (double i = __DBL_DENORM_MIN__; i < __DBL_MAX__; i *= 10)
	{
		single_test_b(index, i, MAX_DBL_STR_LEN);
		++index;
	}
	printf("\n");
}

void	negative_power_of_ten_tests_b(void)
{
	size_t	index = 1;

	printf("negative_power_of_ten_tests_b\n");
	for (double i = -1.0; i > -__DBL_MAX__; i *= 10)
	{
		single_test_b(index, i, MAX_DBL_STR_LEN);
		++index;
	}
	printf("\n");
}
