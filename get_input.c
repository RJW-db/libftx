// #include <libft.h>
#include "include/libft.h"
#include <stdio.h>
int main(void)
{
	char buff[6];
	ssize_t	rd;

	rd = get_user_input(buff, 6, "Name your file: ");
	printf("rd = %lu\n", rd);
	exit(0);
	return (0);
}