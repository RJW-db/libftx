#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <unistd.h>
#include <float.h>
#include <stdint.h>
#include <string.h>
// double	ft_floor(double value)
// {
//     double int_part;

// 	int_part = (double)(uint64_t)value;
// 	if (value < int_part)
// 		return (int_part - 1);
// 	return (int_part);
// }

// double floor_float(double val)
// {
// 	printf("%Lf\n", val);

//     double round = ft_floor(val);
//     double decimal = val - round;
// 	// printf("%Lf\n", round + decimal);
// 	printf("%Lf\n", round);
//     return (round + decimal);
// }

// float ft_powf(float base, int exp)
// {
// 	int		positive_exp;
// 	float	result;

// 	positive_exp = exp;
// 	if (exp < 0)
// 		positive_exp = -exp;
// 	result = 1.0f;
// 	while (positive_exp > 0)
// 	{
// 		result *= base;
// 		--positive_exp;
// 	}
// 	if (exp < 0)
// 		result = 1.0f / result;
// 	return (result);
// }

uint32_t	remove_trailing_zeros(uint32_t round)
{
	while (round != 0 && ((round % 10) + '0') == '0')
		round /= 10;
	return (round);
}

uint32_t	getDecimalCount(float decimals)
{
	int dec_count = 0;
	if (decimals == FLT_MAX)
		return (0);
	while ((decimals - (int)decimals) != 0 && dec_count < __FLT_DIG__) {
		decimals *= 10;
		dec_count++;
	}
	return (remove_trailing_zeros((uint32_t)decimals));
}

void	ftoa(float n)
{
	uint64_t 	integer;
	float		decimals;
	uint32_t	decimal_count;

	integer = (unsigned int)n;
	decimals = n - integer;
	decimal_count = getDecimalCount(decimals);
	printf("%llu.%d\n", integer, decimal_count);
}
#include <stdbool.h>
#include <stdlib.h>
// int	create_decimal(float *n, float stash[])
// {
// 	int count = 0;
// 	int max_decimals = 6;
// 	while (*n > 1 && max_decimals > 0)
// 	{
// 		printf("%Lf\n", *n);
// 		*n /= 10;
// 		++count;
// 		--max_decimals;
// 	}
// 	*stash = *n;
// 	printf("huh %Lf\n", *stash);
// 	exit(0);
// 	return (count);
// }

// // 340282346638528859811704183484516925440
// void big_float(void)
// {
// 	float stash[7];
// 	float n = FLT_MAX;
// 	int count = 0;
// 	int stash_i = 0;
// 	while (n > 1)
// 	{
// 		count += create_decimal(&n, stash + stash_i);
// 		printf("%Lf\n", n);
// 		n /= 10;
// 		++count;
// 		++stash_i;
// 	}
// 	printf("%d\n", count);
// }
#include <stdio.h>
#include <float.h>
#include <strings.h> 
#include <stdlib.h>
#include <math.h>
int jovi = 0;
// 1234567895570144

size_t ft_floatlen(float num)
{
	double int_part = (double)num; // Use double for better precision
	size_t count = 0;

	while (int_part >= 1) { // Count digits until < 1
		int_part /= 10;
		count++;
	}

	return count;
}
long double custom_fmod(long double x, long double y, long double *stash, int iteration) {
	// Handle special cases
	long double power = 10.0;
	if (y == 0.0) {
		return 0.0;
	}
	// Handle negative numbers
	int sign = (x < 0) ? -1 : 1;
	x = (x < 0) ? -x : x;
	y = (y < 0) ? -y : y;
	long double z = 0;

	if (x > 1e23)
	{
		while (x >= y) 
		{
			// printf("XXx %Lf\n", x);
			long double multiple = y;

			while ((multiple * 10.0) <= x) {
				multiple *= 10.0;
				// printf("multiple %Lf\n", multiple);
			}
			// multiple *= 10.0;
			// 	printf("multiple %Lf\n", multiple);
			// exit(0);
			if (iteration >= 2 && x < pow(power, iteration)) {
				z = x - *stash; // 90
				*stash = x;		// 96
				z /= (pow(power, iteration) / 10.0);		// 9
				return sign * z; 
			}
			if (iteration == 2 && x < 100) {
				z = x - *stash; // 90
				*stash = x;		// 96
				z /= 10;		// 9
				printf("z %Lf\n", z);
				printf("x %Lf\n", x);
				// return sign * z; 
				exit(0);
			}
			// 696 - 96
			if (iteration == 3 && x < 1000) {
				z = x - *stash; // 600
				*stash = x;		// 696
				z /= 100;		// 6
				printf("z %Lf\n", z);
				printf("x %Lf\n", x);
				return sign * z; 
				// exit(0);
			}
			if (iteration == 4 && x < 10000) {
				z = x - *stash; // 600
				*stash = x;		// 696
				z /= 1000;		// 6
				printf("z %Lf\n", z);
				printf("x %Lf\n", x);
				return sign * z; 
				// exit(0);
			}
			if (iteration == 5 && x < 100000) {
				z = x - *stash; // 600
				*stash = x;		// 696
				z /= 10000;		// 6
				printf("z %Lf\n", z);
				printf("x %Lf\n", x);
				// return sign * z; 
				exit(0);
			}

			while (multiple <= x) {
				x -= multiple;
			}
		}
		*stash = x;
		printf("stash %Lf\n", *stash);
		return sign * x;
	}
	if (x > 1e20) {  // threshold for when to use alternative method
		while (x >= y) 
		{
			// Find largest multiple of y that's less than x
			long double multiple = y;

			while ((multiple * 10.0) <= x) {
				multiple *= 10.0;
			}
			
	// printf("XXx %Lf\n", x);
			if (iteration >= 2 && x < pow(power, iteration)) {
				z = x - *stash; // 90
				*stash = x;		// 96
				z /= (pow(power, iteration) / 10.0);		// 9
				return sign * z; 
			}
			if (iteration == 2 && x < 100) {
				z = x - *stash; // 90
				*stash = x;		// 96
				z /= 10;		// 9
				printf("z %Lf\n", z);
				printf("x %Lf\n", x);
				// return sign * z; 
				exit(0);
			}
			// 696 - 96
			if (iteration == 3 && x < 1000) {
				z = x - *stash; // 600
				*stash = x;		// 696
				z /= 100;		// 6
				printf("z %Lf\n", z);
				printf("x %Lf\n", x);
				return sign * z; 
				// exit(0);
			}
			if (iteration == 4 && x < 10000) {
				z = x - *stash; // 600
				*stash = x;		// 696
				z /= 1000;		// 6
				printf("z %Lf\n", z);
				printf("x %Lf\n", x);
				return sign * z; 
				// exit(0);
			}
			if (iteration == 5 && x < 100000) {
				z = x - *stash; // 600
				*stash = x;		// 696
				z /= 10000;		// 6
				printf("z %Lf\n", z);
				printf("x %Lf\n", x);
				// return sign * z; 
				exit(0);
			}
			while (multiple <= x) {
				x -= multiple;
			}
		}
		*stash = x;
		printf("stash %Lf\n", *stash);
		return sign * x;
	}

	// if (jovi == 16)
		// printf("%Lf\n", x);
	// For smaller numbers, use the original method
	long double quotient = x / y;
	long double integer_part = (long double)((long long)quotient);
	// long double integer_part = floor(quotient); // Use floor to ensure correct integer part

	double remainder = x - (integer_part * y);
	
	return sign * remainder;
}
// 1234567946798590091853824
// 1234567946798590058299392.000000
int main()
{
	// float num = FLT_MAX;
	// float num = 123456789557014429696.0F;
	// float num = 1234567965938888474624.0F;
	// float num = 12345679377913908035584.0F;

	//	to big to work again.
	float num = 123456798282738707726336.0F;

	// float num = 1234567946798590058299392.0F;
	// float num = FLT_MAX / 1.5;
	printf("%f\n", num);
	// // exit(0);
	// printf("%Lf\n", num / 10.0);
	// exit(0);
	size_t len = ft_floatlen(num);
	int *result = (int *)malloc(len * sizeof(int));
	if (!result)
		return 1;
	bzero(result, len * sizeof(int));
	
	size_t past_15_digit = len - 15; // 2
	// Extract integer part using double
	long double int_part = (long double)num;

	long double	stash = 0;
	int iteration = 1;
	// Store digits in result array (backward)
	for (size_t i = len; i > 0; i--)
	{
		// result[i - 1] = (int)fmod(int_part, 10); // Get last digit
		result[i - 1] = (int)custom_fmod(int_part, 10.0, &stash, iteration); // Get last digit
		if (iteration == past_15_digit)
			int_part /= pow(10, iteration); // Remove last digit
		else if (iteration > past_15_digit)
			int_part /= 10;
			// int_part /= 10.0 * iteration; // Remove last digit
		// printf("%Lf\n", int_part);
		// exit(0);
		// for (size_t i = 0; i < len; i++)
		// 	printf("%d", result[i]);
		// printf("\n");
		// if (iteration >= 8)
		// 	exit(0);
		// ++jovi;
		++iteration;
	}

	// --- PRINT ---
	printf("Result After: ");
	for (size_t i = 0; i < len; i++)
		printf("%d", result[i]);
	printf("\n");
	// -------------

	printf("PRINTF:       %f\n", num);

	free(result);
	// printf("              %Lf\n", __FLT_MAX__);
	// printf("%Lf\n", __FLT_MAX__ / 1.5F);
	// printf("%Lf\n", __FLT_MAX__ / 2.0F);

	return 0;
}

// int	main(void)
// {

// // char str[40];
// float number = 123.456;
// number = FLT_MAX;
// // floatToStr(number, str, 6);
// // printf("%s\n", str);
// printf("%Lf\n", number);
// printf("%Lf\n", number / 1.5F);
// printf("%Lf\n", number / 5);
// return (0);
// 	// big_float();

// 	// remove_trailing_zeros(150);
// 	// remove_trailing_zeros(2390000);
// 	// ftoa(2.9F);
// 	// ftoa(1.123F);
// 	// ftoa(1.123456F);
// 	// ftoa(123.123455F);
// 	// ftoa(123.123456F);
// 	// ftoa(123.12345F);
// 	// ftoa(14123.123456F);
// 	// ftoa(3.4e38F);
// 	// ftoa(987654321.0F);
// // floor_float(9876543219876.0F);
// // floor_float(987654321987612312312312.01110);
// // printf("%Lf\n", 123.123455F);
// // printf("%Lf\n", 123.123456F);
// // printf("%Lf\n", FLT_MAX);
// 	// ftoa(1.123456F);
// 	// ftoa(FLT_MAX);
// 	// ftoa(3.40282345e+38F);
// 	// ftoa(1.123456F);
//     // printf("Max float value: %e\n", FLT_MAX);
//     // printf("Max float value - 1: %e\n", FLT_MAX - 1);
//     // printf("Max float value - 1e30: %e\n", FLT_MAX - 1e30);

// 	// printf("%Lf\n", powf(FLT_MAX, 2));
// 	// printf("%Lf\n", my_powf(FLT_MAX, 2));
// 	// printf("%Lf\n", powf(-2.0F, 2));
// 	// printf("%Lf\n", my_powf(1.8F, 2));
// 	// printf("%Lf\n", my_powf(1.5F, 2));
// 	// printf("%lld\n", LLONG_MAX);
// 	// printf("%Lf\n", FLT_MIN);
// 	// printf("%Lf\n", -FLT_TRUE_MIN);
// 	// printf("%Lf\n", -1.0F);
// 	return (0);
// }
// 340282346638528859811704183484516925440.000000