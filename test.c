#include <stdio.h>
#include <string.h>

// Function to get the length of the string representing a floating-point number
int get_num_len(double num) {
	int len = 0;
	if (num < 0) {
		len++; // for the minus sign
		num = -num;
	}

	// Handle the integer part
	int integer_part = (int) num;
	do {
		len++;
		integer_part /= 10;
	} while (integer_part > 0);

	// Handle the decimal part
	num -= (int) num; // removing the integer part
	if (num > 0) {
		len++; // for the decimal point
		while (num != (int) num) {
			num *= 10;
			len++;
		}
	}

	return len;
}

// Function to print the floating-point number using Dragon4 algorithm
void dragon4_print(double num, int precision) {
    if (num < 0) {
        putchar('-');
        num = -num;
    }

    // Handle the integer part
    int integer_part = (int) num;
    printf("%d", integer_part);

    num -= integer_part;

    // Handle the decimal part with given precision
    if (precision > 0) {
        putchar('.');
        for (int i = 0; i < precision; i++) {
            num *= 10;
            int digit = (int) num;
            printf("%d", digit);
            num -= digit;
        }
    }
}

int main() {
    // double num = -123.456789;
    double num = __FLT_MAX__;
    int precision = 6;  // You can change the precision
    dragon4_print(num, precision);
    return 0;
}