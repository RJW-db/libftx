#include "includes/ft_dbltoa.h"
#include <float.h>
#include <math.h>

# define RESET			"\033[0m"
# define BOLD			"\033[1m"
# define ITALIC			"\033[3m"
# define RED			"\033[31m"
# define GREEN			"\033[32m"
# define MAGENTA		"\033[35m"

void	testing_dbltoa_b(size_t index, bool check);
void	format_double_b(char *buffer, size_t size, double input);
bool	single_test_b(size_t index, double input);
void	float_tests_b(void);
void	double_tests_b(void);
void	edgecase_tests_b(void);
void	random_tests_b(void);
void	linear_range_tests_b(void);
void	power_of_ten_tests_b(void);
void	subnormal_to_max_tests_b(void);
void	negative_power_of_ten_tests_b(void);


int	main(void)
{
	// single_test_b(1, -__DBL_DENORM_MIN__);
	// single_test_b(2, 99999999999999991611392.000000);
	// single_test_b(3, -99999999999999991611392.000000);
	// single_test_b(4, 0.0F);

	// double dbl = 0;
	// dbl = 10000000000000003096614376152413048208109554690349451174220128548038993319997892036002416949924978717442765739064816521709922285414434346682046265082050320008030223212838050621638314677133314688548864.000000;
	// char *output = dbltoa(dbl);
	// printf("%s\n", output);
	// free(output);
	// puts("prima");
	// exit(0);

	float_tests_b();
	// double_tests_b();
	// edgecase_tests_b();
	// random_tests_b();
	// linear_range_tests_b();
	// power_of_ten_tests_b();
	// subnormal_to_max_tests_b();
	// negative_power_of_ten_tests_b();
	return (0);
}

void	testing_dbltoa_b(size_t index, bool check)
{
	if (check == true)
		printf(GREEN "%zu.OK " RESET, index);
	else
		printf(RED "%zu.KO " RESET, index);
}

void	format_double_b(char *buffer, size_t size, double input)
{
	snprintf(buffer, size, "%.1075f", input);  // Full precision

	// Trim trailing zeros but keep at least one decimal digit
	char *p = buffer + strlen(buffer) - 1;
	while (*p == '0') {
		*p = '\0';  // Replace '0' with null terminator
		--p;
	}
	if (*p == '.') {
		*p = '\0';  // Remove the decimal point if it's the last character
	}
}

bool	single_test_b(size_t index, double input)
{
	char buffer[MAX_DBL_STR_LEN];  // longest number + terminator

	char *output = dbltoa(input);
	// printf("%s\n", output);
	format_double_b(buffer, sizeof(buffer), input);

	// printf("%s\n", buffer);  // Print the buffer content

	testing_dbltoa_b(index, strncmp(output, buffer, strlen(buffer) + 1) == 0);
	free(output);
	return (0);
}

// 1000000000000000000000000000000000000000000000000000000000000000
void	float_tests_b(void)
{
	printf("float_tests_b\n");
	// single_test_b(1, -0.0F);
	// single_test_b(2, 0.0F);
	// exit(0);
	// single_test_b(3, +0.0F);

	// single_test_b(4, -1.0F);
	// single_test_b(5, 1.0F);
	// single_test_b(6, +1.0F);

	// single_test_b(7, -1.5F);
	// single_test_b(8, 1.5F);
	// single_test_b(9, +1.5F);

	// single_test_b(10, -1.0000000000000001F);
	// single_test_b(11, 1.0000000000000001F);
	// single_test_b(12, +1.0000000000000001F);

	// single_test_b(13, -0.9999999999999999F);
	// single_test_b(14, 0.9999999999999999F);
	// single_test_b(15, +0.9999999999999999F);
	printf("\n");
}

// void	double_tests_b(void)
// {
// 	printf("double_tests_b\n");
// 	single_test_b(1, -0.0);
// 	single_test_b(2, 0.0);
// 	single_test_b(3, +0.0);

// 	single_test_b(4, -1.0);
// 	single_test_b(5, 1.0);
// 	single_test_b(6, +1.0);

// 	single_test_b(7, -1.5);
// 	single_test_b(8, 1.5);
// 	single_test_b(9, +1.5);

// 	single_test_b(10, -1.0000000000000001);
// 	single_test_b(11, 1.0000000000000001);
// 	single_test_b(12, +1.0000000000000001);

// 	single_test_b(13, -0.9999999999999999);
// 	single_test_b(14, 0.9999999999999999);
// 	single_test_b(15, +0.9999999999999999);
// 	printf("\n");
// }

// void	edgecase_tests_b(void)
// {
// 	printf("edgecase_tests_b\n");
// 	single_test_b(1, 0);
// 	single_test_b(2, -1);
// 	single_test_b(3, 1);

// 	single_test_b(4, __DBL_MAX__);
// 	single_test_b(5, __DBL_MIN__);
// 	single_test_b(6, __DBL_EPSILON__);			// Smallest difference between two doubles
// 	single_test_b(7, __DBL_DENORM_MIN__);			// Smallest subnormal number

// 	single_test_b(8, DBL_MAX_EXP);				// Maximum binary exponent (+1024)
// 	single_test_b(9, DBL_MIN_EXP);				// Minimum binary exponent (-1021 for normal, subnormals go lower)
// 	single_test_b(10, DBL_MANT_DIG);				// Number of bits in mantissa (53)
// 	single_test_b(11, DBL_DIG);					// Max decimal digits of precision (15-17)
// 	single_test_b(12, DBL_MAX_10_EXP);			// Max base-10 exponent (≈308)
// 	single_test_b(13, DBL_MIN_10_EXP);			// Min base-10 exponent (≈-307)

// 	single_test_b(14, INFINITY);
// 	single_test_b(15, -INFINITY);
// 	single_test_b(16, NAN);						// Any NaN (implementation-defined)
// 	single_test_b(17, -NAN);						// Negative NaN

// 	single_test_b(18, -__DBL_MAX__);
// 	single_test_b(19, -__DBL_MIN__);
// 	single_test_b(20, -__DBL_DENORM_MIN__);
// 	single_test_b(21, -__DBL_EPSILON__);

// 	single_test_b(22, pow(10, DBL_MAX_10_EXP));	// Max possible power of 10
// 	single_test_b(23, pow(10, DBL_MIN_10_EXP));	// Smallest power of 10
// 	single_test_b(24, 1.0 + DBL_EPSILON);			// Just above 1.0
// 	single_test_b(25, 1.0 - DBL_EPSILON);			// Just below 1.0
// 	printf("\n");
// }

// void	random_tests_b(void)
// {
// 	printf("random_tests_b\n");
// 	single_test_b(1, -1231246524059005808017408.0F);
// 	single_test_b(2, -123126877777777781062520432865268252910947010799856319324944859136.0);
// 	single_test_b(3, 0.1234567891234567837965840908509562723338603973388671875);
// 	single_test_b(4, -1234567837723.123535);
// 	printf("\n");
// }

// void	linear_range_tests_b(void)
// {
// 	size_t	index = 1;

// 	printf("linear_range_tests_b\n");
// 	for (double i = -50; i <= 50; i += 0.1)
// 	{
// 		single_test_b(index, i);
// 		++index;
// 	}
// 	printf("\n");
// }

// void	power_of_ten_tests_b(void)
// {
// 	size_t	index = 1;

// 	printf("power_of_ten_tests_b\n");
// 	for (double i = 1.0; i < __DBL_MAX__; i *= 10)
// 	{
// 		// if (index == 24) {
// 			// printf("%f\n", i);
// 			single_test_b(index, i);
// 			// exit(0);
// 		// }
// 		++index;
// 	}
// 	printf("\n");
// }

// void	subnormal_to_max_tests_b(void)
// {
// 	size_t	index = 1;

// 	printf("subnormal_to_max_tests_b\n");
// 	for (double i = __DBL_DENORM_MIN__; i < __DBL_MAX__; i *= 10)
// 	{
// 		single_test_b(index, i);
// 		++index;
// 	}
// 	printf("\n");
// }

// void	negative_power_of_ten_tests_b(void)
// {
// 	size_t	index = 1;

// 	printf("negative_power_of_ten_tests_b\n");
// 	for (double i = -1.0; i > -__DBL_MAX__; i *= 10)
// 	{
// 		// if (index == 24) {
// 		// 	printf("%f\n", i);
// 			single_test_b(index, i);
// 		// 	exit(0);
// 		// }
// 		++index;
// 	}
// 	printf("\n");
// }
