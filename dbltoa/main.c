#include "includes/ft_dbltoa.h"
#include <float.h>
#include <math.h>

# define RESET			"\033[0m"
# define BOLD			"\033[1m"
# define ITALIC			"\033[3m"
# define RED			"\033[31m"
# define GREEN			"\033[32m"
# define MAGENTA		"\033[35m"

bool	testing_dbltoa(size_t index, bool check);
void	format_double(char *buffer, size_t size, double input);
bool	single_test(size_t index, double input);
void	float_tests(void);
void	double_tests(void);
void	edgecase_tests(void);
void	random_tests(void);
void	linear_range_tests(void);
void	power_of_ten_tests(void);
void	subnormal_to_max_tests(void);
void	negative_power_of_ten_tests(void);

// typedef union	u_double_bicast
// {
// 	double d;
// 	int64_t i;
// }	t_double_bicast;

// void print_double_bits(double num) {
// 	t_double_bicast bitcast = { .d = num };
// 	printf("Double value: %f\n", num);
// 	printf("Int64 representation: %lld\n", (long long)bitcast.i);
	
// 	// Print each byte
// 	for (uint16_t i = 0; i < sizeof(double); i++) {
// 		uint8_t byte = (bitcast.i >> (i * 8)) & 0xFF;
// 		printf("Byte %d: %02X\n", i, byte);
// 	}
// }

int	main(void)
{
	// double test_num = 3.14;
	// print_double_bits(test_num);
	// char *bit_string = double_to_bitstring(test_num, sizeof(double));
	// if (bit_string) {
	// 	printf("Bit string: %s\n", bit_string);
	// 	free(bit_string);
	// } else {
	// 	printf("Failed to convert to bit string\n");
	// }
	// double dbl = 0;
	// char *str = NULL;

	// dbl = __DBL_MAX__;
	float_tests();
	double_tests();
	edgecase_tests();
	random_tests();
	// linear_range_tests();
	// power_of_ten_tests();
	// subnormal_to_max_tests();
	// negative_power_of_ten_tests();

	// char buff[1078];
	// dbltoa_buff(0.0, buff, 1078);
	// puts(buff);
	// dbltoa_buff(__DBL_MAX__, buff, 1078);
	// puts(buff);
	return (0);
}

bool	testing_dbltoa(size_t index, bool check)
{
	if (check == true)
		printf(GREEN "%zu.OK " RESET, index);
	else
		printf(RED "%zu.KO " RESET, index);
	return (check);
}

void	format_double(char *buffer, size_t size, double input)
{
	snprintf(buffer, size, "%.1075f", input);  // Full precision

	// Trim trailing zeros but keep at least one decimal digit
	char *p = buffer + strlen(buffer) - 1;
	while (*p == '0') {
		*p = '\0';  // Replace '0' with null terminator
		p--;
	}
	if (*p == '.') {
		*p = '\0';  // Remove the decimal point if it's the last character
	}
}

bool	single_test(size_t index, double input)
{
	char buffer[MAX_DBL_STR_LEN];  // longest number + terminator

	char *output = dbltoa(input);
	// printf("%s\n", output);
	format_double(buffer, sizeof(buffer), input);

	// printf("%s\n", buffer);  // Print the buffer content

	testing_dbltoa(index, strncmp(output, buffer, strlen(buffer) + 1) == 0);
	free(output);
	return (0);
}

// 1000000000000000000000000000000000000000000000000000000000000000
void	float_tests(void)
{
	printf("float_tests\n");
	single_test(1, -0.0F);
	single_test(2, 0.0F);
	single_test(3, +0.0F);

	single_test(4, -1.0F);
	single_test(5, 1.0F);
	single_test(6, +1.0F);

	single_test(7, -1.5F);
	single_test(8, 1.5F);
	single_test(9, +1.5F);

	single_test(10, -1.0000000000000001F);
	single_test(11, 1.0000000000000001F);
	single_test(12, +1.0000000000000001F);

	single_test(13, -0.9999999999999999F);
	single_test(14, 0.9999999999999999F);
	single_test(15, +0.9999999999999999F);
	printf("\n");
}

void	double_tests(void)
{
	printf("double_tests\n");
	single_test(1, -0.0);
	single_test(2, 0.0);
	single_test(3, +0.0);

	single_test(4, -1.0);
	single_test(5, 1.0);
	single_test(6, +1.0);

	single_test(7, -1.5);
	single_test(8, 1.5);
	single_test(9, +1.5);

	single_test(10, -1.0000000000000001);
	single_test(11, 1.0000000000000001);
	single_test(12, +1.0000000000000001);

	single_test(13, -0.9999999999999999);
	single_test(14, 0.9999999999999999);
	single_test(15, +0.9999999999999999);
	printf("\n");
}

void	edgecase_tests(void)
{
	printf("edgecase_tests\n");
	single_test(1, 0);
	single_test(2, -1);
	single_test(3, 1);

	single_test(4, __DBL_MAX__);
	// exit(0);
	single_test(5, __DBL_MIN__);
	single_test(6, __DBL_EPSILON__);			// Smallest difference between two doubles
	single_test(7, __DBL_DENORM_MIN__);			// Smallest subnormal number

	single_test(8, DBL_MAX_EXP);				// Maximum binary exponent (+1024)
	single_test(9, DBL_MIN_EXP);				// Minimum binary exponent (-1021 for normal, subnormals go lower)
	single_test(10, DBL_MANT_DIG);				// Number of bits in mantissa (53)
	single_test(11, DBL_DIG);					// Max decimal digits of precision (15-17)
	single_test(12, DBL_MAX_10_EXP);			// Max base-10 exponent (≈308)
	single_test(13, DBL_MIN_10_EXP);			// Min base-10 exponent (≈-307)

	single_test(14, INFINITY);
	single_test(15, -INFINITY);
	single_test(16, NAN);						// Any NaN (implementation-defined)
	single_test(17, -NAN);						// Negative NaN

	single_test(18, -__DBL_MAX__);
	single_test(19, -__DBL_MIN__);
	single_test(20, -__DBL_DENORM_MIN__);
	single_test(21, -__DBL_EPSILON__);

	single_test(22, pow(10, DBL_MAX_10_EXP));	// Max possible power of 10
	single_test(23, pow(10, DBL_MIN_10_EXP));	// Smallest power of 10
	single_test(24, 1.0 + DBL_EPSILON);			// Just above 1.0
	single_test(25, 1.0 - DBL_EPSILON);			// Just below 1.0
	printf("\n");
}

void	random_tests(void)
{
	printf("random_tests\n");
	single_test(1, -1231246524059005808017408.0F);
	single_test(2, -123126877777777781062520432865268252910947010799856319324944859136.0);
	single_test(3, 0.1234567891234567837965840908509562723338603973388671875);
	single_test(4, -1234567837723.123535);
	printf("\n");
}

void	linear_range_tests(void)
{
	size_t	index = 1;

	printf("linear_range_tests\n");
	for (double i = -50; i <= 50; i += 0.1)
	{
		single_test(index, i);
		++index;
	}
	printf("\n");
}

void	power_of_ten_tests(void)
{
	size_t	index = 1;

	printf("power_of_ten_tests\n");
	for (double i = 1.0; i < __DBL_MAX__; i *= 10)
	{
		single_test(index, i);
		++index;
	}
	printf("\n");
}

void	subnormal_to_max_tests(void)
{
	size_t	index = 1;

	printf("subnormal_to_max_tests\n");
	for (double i = __DBL_DENORM_MIN__; i < __DBL_MAX__; i *= 10)
	{
		single_test(index, i);
		++index;
	}
	printf("\n");
}

void	negative_power_of_ten_tests(void)
{
	size_t	index = 1;

	printf("negative_power_of_ten_tests\n");
	for (double i = -1.0; i > -__DBL_MAX__; i *= 10)
	{
		single_test(index, i);
		++index;
	}
	printf("\n");
}
