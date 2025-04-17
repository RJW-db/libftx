#include <stdio.h>
#include <stdbool.h>
#include <float.h>
#include <math.h>
#include <string.h>
#include <libft.h>

#include <ft_atof.h>
// Define colors for output
#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

void	atofinette(void);
void	manual_descriptive_test(void);

// cc -Wall -Wextra -Werror -Wunreachable-code -Wpedantic -Wconversion -Wshadow -I . -I ../../include main.c dt_atof.c process_exponent.c process_first_part.c process_second_part.c ../../lib.a && ./a.out
// cc -I . -I ../../include main.c dt_atof.c process_exponent.c process_first_part.c process_second_part.c ../../lib.a && ./a.out

int	main(void)
{
	manual_descriptive_test();
	atofinette();
	return (0);
}


void test_case(const char *input, const char *description) {
	bool overflow = false;
	float result = ft_atof(input, &overflow);
	
	printf("Test: %s\n", description);
	printf("Input: \"%s\"\n", input);
	printf("Result: %e\n", result);
	// printf("Result: %f\n", result);
	printf("Overflow/Underflow detected: %s\n", overflow ? "Yes" : "No");
	printf("Result is %s\n", 
		overflow ? (result == 0.0F ? "UNDERFLOW (set to 0)" : 
					(result > 0 ? "OVERFLOW (set to FLT_MAX)" : "OVERFLOW (set to -FLT_MAX)")) : 
		"NORMAL");
	printf("Difference from FLT_MAX: %e\n", FLT_MAX - result);
	printf("-----------------------------\n");
}

void	manual_descriptive_test(void)
{
	printf("FLT_MAX = %e\n", FLT_MAX);
	printf("FLT_MIN = %e\n\n", FLT_MIN);
	
	// Normal cases
	test_case("0.0", "Zero");
	test_case("123.456", "Normal positive number");
	test_case("-42.5", "Normal negative number");
	
	// Overflow cases
	char huge_number[100] = "1";
	for (int i = 0; i < 40; i++) strcat(huge_number, "0");  // 1e40
	test_case(huge_number, "Large positive number");

	char huge_negative[101] = "-";
	strcat(huge_negative, huge_number);
	test_case(huge_negative, "Large negative number");

	test_case("3.4e38", "Near FLT_MAX");
	test_case("3.5e38", "Exceeding FLT_MAX");
	test_case("3.403e38", "Slightly exceeding FLT_MAX");
	test_case("4e38", "Far exceeding FLT_MAX");
	
	// Underflow cases
	test_case("1.0e-46", "Small positive number near underflow");
	test_case("1.0e-50", "Very small positive number (underflow)");
	test_case("1e-100", "Exponent causing underflow");

	// Special values
	test_case("inf", "Positive infinity");
	test_case("-inf", "Negative infinity");
	test_case("nan", "Not-a-Number (NaN)");
	test_case("-nan", "Negative Not-a-Number (NaN)");
	test_case("NaN", "Uppercase NaN");
	test_case("nAn", "Mixed case NaN");
	test_case("-NaN", "Uppercase negative NaN");
	test_case("Infinity", "Full word Infinity");
	test_case("INFINITY", "Uppercase Infinity");
	test_case("-Infinity", "Negative full word Infinity");

	// Whitespace handling
	test_case("   123.456", "Leading whitespace");
	test_case("123.456   ", "Trailing whitespace");
	test_case("   123.456   ", "Leading and trailing whitespace");
	test_case(" +123.456e+2", "Number with whitespace, sign and exponent");

	// Invalid strings
	test_case("", "Empty string");
	test_case("abc", "Invalid string with letters");
	test_case("123abc", "Number followed by letters");
	test_case("abc123", "Letters followed by numbers");
	test_case("..123", "Invalid format with multiple dots");
	test_case("123..456", "Invalid format with multiple dots in the middle");
	test_case(".", "Only decimal point");
	test_case("-", "Only negative sign");
	test_case("+", "Only positive sign");
	test_case("--123.456", "Double negative sign");
	test_case("++123.456", "Double positive sign");
	test_case("+-123.456", "Mixed signs");

	// Exponent handling
	test_case("1e38", "Exponent at upper boundary");
	test_case("1e-38", "Exponent at lower boundary");
	test_case("1e39", "Exponent exceeding upper boundary");
	test_case("1e-39", "Exponent exceeding lower boundary");
	test_case("1e-1", "Small negative exponent");
	test_case("1e-10", "Larger negative exponent");
	test_case("1e", "Missing exponent");
	test_case("1e+", "Missing exponent after sign");
	test_case("e10", "Missing mantissa");

	// Boundary cases
	test_case("3.4028234e+38", "Just below FLT_MAX");
	test_case("3.4028235e+38", "Just above FLT_MAX");
	test_case("1.1754943e-38", "Just above FLT_MIN");
	test_case("1.1754942e-38", "Just below FLT_MIN");
	test_case("1.0e-45", "At FLT_MIN boundary");

	// Leading zeros
	test_case("000123.456", "Number with leading zeros");
	test_case("0000.123", "Fractional number with leading zeros");

	// Negative zero
	test_case("-0.0", "Negative zero");

	// Long numbers
	char long_number[1000];
	memset(long_number, '9', 999);
	long_number[999] = '\0';
	test_case(long_number, "Excessively long number");

	// Exact and slightly above FLT_MAX
	char max_float[100];
	sprintf(max_float, "%.10e", FLT_MAX);
	test_case(max_float, "Exact FLT_MAX value");

	char above_max[100];
	sprintf(above_max, "%.10e", FLT_MAX);
	// Find the last digit and increment it
	for (int i = 0; above_max[i]; i++) {
		if (above_max[i] >= '0' && above_max[i] <= '8' && 
			(above_max[i+1] == 'e' || above_max[i+1] == 'E')) {
			++above_max[i];
			break;
		}
	}
	test_case(above_max, "Slightly above FLT_MAX");
}




bool float_equals(float a, float b)
{
	if (isnan(a) && isnan(b))
		return true; // Both NAN
	if (isnan(a) || isnan(b))
		return false; // One NAN, one not
	if (isinf(a) && isinf(b))
		return signbit(a) == signbit(b); // Both INF with same sign
	if (isinf(a) || isinf(b))
		return false; // One INF, one not
	
	// For regular numbers
	float diff = fabsf(a - b);
	float tolerance = FLT_EPSILON * fmaxf(1.0f, fmaxf(fabsf(a), fabsf(b)));
	return diff <= tolerance;
}

// Tester function
bool test_case_auto_check(const char *input, float expected_result, bool expected_overflow, size_t index) {
	const char *table[2] = {
		RED "%zu.KO " RESET,
		GREEN "%zu.OK " RESET
	};

	bool overflow = false;
	float result = ft_atof(input, &overflow);

	// Check if the result matches the expected result and overflow status
	bool result_match = false;
	if (isnan(expected_result)) {
		result_match = isnan(result); // Check if both are NAN
	} else if (isinf(expected_result)) {
		result_match = (isinf(result) && (signbit(expected_result) == signbit(result))); // Check for INFINITY and sign
	} else {
		result_match = float_equals(result, expected_result);
	}

	bool overflow_match = (overflow == expected_overflow);

	// Print the test result
	bool test_passed = result_match && overflow_match;
	printf((table[test_passed]), index);

	if (!test_passed) {
		printf("\nInput: \"%s\"\n", input);
		printf("Expected: %e, Got: %e\n", expected_result, result);
		printf("Expected Overflow: %s, Got: %s\n", expected_overflow ? "Yes" : "No", overflow ? "Yes" : "No");
	}

	return test_passed;
}

void	atofinette(void)
{
	// test_case_auto_check("1.1754942e-38", 1.1754942e-38f, false, 51);
	// exit(0);


	printf("FLT_MAX = %e\n", FLT_MAX);
	printf("FLT_MIN = %e\n\n", FLT_MIN);

	test_case_auto_check("123.456", 123.456f, false, 1);
	test_case_auto_check("-42.5", -42.5f, false, 2);
	test_case_auto_check("0.0", 0.0f, false, 3);
	
	// Overflow cases
	test_case_auto_check("10000000000000000000000000000000000000000", FLT_MAX, true, 4);
	test_case_auto_check("-10000000000000000000000000000000000000000", -FLT_MAX, true, 5);
	test_case_auto_check("3.4e38", 3.4e38f, false, 6);
	test_case_auto_check("3.5e38", FLT_MAX, true, 7);
	test_case_auto_check("3.403e38", FLT_MAX, true, 8);
	test_case_auto_check("4e38", FLT_MAX, true, 9);
	
	// Underflow cases
	test_case_auto_check("1.0e-46", 0.0f, true, 10);
	test_case_auto_check("1.0e-50", 0.0f, true, 11);
	test_case_auto_check("1e-100", 0.0f, true, 12);
	
	// Special values
	test_case_auto_check("inf", INFINITY, false, 13);
	test_case_auto_check("-inf", -INFINITY, false, 14);
	test_case_auto_check("nan", NAN, false, 15);
	test_case_auto_check("-nan", NAN, false, 16);
	test_case_auto_check("NaN", NAN, false, 17);
	test_case_auto_check("nAn", NAN, false, 18);
	test_case_auto_check("-NaN", NAN, false, 19);
	test_case_auto_check("Infinity", INFINITY, false, 20);
	test_case_auto_check("INFINITY", INFINITY, false, 21);
	test_case_auto_check("-Infinity", -INFINITY, false, 22);
	
	// Whitespace handling
	test_case_auto_check("   123.456", 123.456f, false, 23);
	test_case_auto_check("123.456   ", 123.456f, false, 24);
	test_case_auto_check("   123.456   ", 123.456f, false, 25);
	test_case_auto_check(" +123.456e+2", 12345.6f, false, 26);
	
	// Invalid strings
	test_case_auto_check("", 0.0f, false, 27);
	test_case_auto_check("abc", 0.0f, false, 28);
	test_case_auto_check("123abc", 123.0f, false, 29);
	test_case_auto_check("abc123", 0.0f, false, 30);
	test_case_auto_check("..123", 0.0f, false, 31);
	test_case_auto_check("123..456", 123.0f, false, 32);
	test_case_auto_check(".", 0.0f, false, 33);
	test_case_auto_check("-", 0.0f, false, 34);
	test_case_auto_check("+", 0.0f, false, 35);
	test_case_auto_check("--123.456", 0.0f, false, 36);
	test_case_auto_check("++123.456", 0.0f, false, 37);
	test_case_auto_check("+-123.456", 0.0f, false, 38);
	
	// Exponent handling
	test_case_auto_check("1e38", 1e38f, false, 39);
	test_case_auto_check("1e-38", 0.0f, true, 40);
	test_case_auto_check("1e39", FLT_MAX, true, 41);
	test_case_auto_check("1e-39", 0.0f, true, 42);
	test_case_auto_check("1e-1", 0.1f, false, 43);
	test_case_auto_check("1e-10", 1e-10f, false, 44);
	test_case_auto_check("1e", 1.0f, false, 45);
	test_case_auto_check("1e+", 1.0f, false, 46);
	test_case_auto_check("e10", 0.0f, false, 47);
	
	// Boundary cases
	test_case_auto_check("3.4028234e+38", FLT_MAX, true, 48);
	test_case_auto_check("3.4028235e+38", FLT_MAX, true, 49);
	test_case_auto_check("1.1754943e-38", 1.1754943e-38f, false, 50);
	test_case_auto_check("1.1754942e-38", 1.1754942e-38f, false, 51);
	test_case_auto_check("1.0e-45", 0.0f, true, 52);
	
	// Leading zeros
	test_case_auto_check("000123.456", 123.456f, false, 53);
	test_case_auto_check("0000.123", 0.123f, false, 54);
	
	// Negative zero
	test_case_auto_check("-0.0", -0.0f, false, 55);
	
	// Long numbers
	char long_number[1000];
	memset(long_number, '9', 999);
	long_number[999] = '\0';
	test_case_auto_check(long_number, FLT_MAX, true, 56);
	
	// Exact and slightly above FLT_MAX
	char max_float[100];
	sprintf(max_float, "%.10e", FLT_MAX);
	test_case_auto_check(max_float, FLT_MAX, true, 57);
	
	char above_max[100];
	sprintf(above_max, "%.10e", FLT_MAX);
	for (int i = 0; above_max[i]; i++) {
		if (above_max[i] >= '0' && above_max[i] <= '8' && 
			(above_max[i+1] == 'e' || above_max[i+1] == 'E')) {
			++above_max[i];
			break;
		}
	}
	test_case_auto_check(above_max, FLT_MAX, true, 58);
	printf("\n");
}
