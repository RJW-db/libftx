#include <libft.h>
#include <stdio.h>
int main(void)
{
	char buf[1000];
	
	cpy_srcs_s(buf, "bur", NULL, "yur");
	puts(buf);
	return (0);
}
// int main(void)
// {
// 	char buff[6];
// 	ssize_t	rd;

// 	rd = get_user_input(buff, 6, "Name your file: ");
// 	printf("rd = %lu\n", rd);
// 	exit(0);
// 	return (0);
// }