#include <wrap_functions.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

// typedef struct ok
// {
// 	size_t i;
// }	t_ok;

// bool	set_malloc_amount(size_t size, void *ptr)
// {
// 	static	t_ok *ok = NULL;

// write(1, "hello\n", 6);
// 	if (ok == NULL)
// 	{
// 		ok = (t_ok *)ptr;
// 	}
// 	else if (ok->i > 0)
// 	{
// 		write(1, "middle\n", 7);
// 		ok->i--;
// 	} else {
// 		write(1, "SHOULDN'T see this message, use malloc_toggle()\n", 48);
// 		return (false);
// 	}
// 	return (true);
// }

// #include <libft.h>
// int main(void)
// {
// 	t_ok	ok;
// 	ok.i = 2;
// 	write(1, "first\n", 6);

// 	malloc_handler(0, &ok, set_malloc_amount);
// 	// malloc_toggle(SET_MALLOC);
// 	malloc_toggle(SET_MALLOC);
// 	ft_putendl_fd("hiero", 1);
// 	char *str = malloc(5);
// 	free(str);
// 	char *arr = ft_strdup("mooi\n");
// 	if (arr)
// 		write(1, arr, 5);
// 	free(arr);
// 	handle_close(get_handle());
// 	handle_close(get_handle());
// 	return (0);
// }

#include <common_defs.h>
#include <libft.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>


// int open(const char *path, int oflag, ...)
// {
// 	static int (*real_open)(const char *, int, ...) = NULL;
// 	static void	**handle_open = NULL;

// 	if (real_open == NULL) {
// 		handle_open = pass_handles(handle_open);
// 		// dlopen_handler(handle_open);
// 		// *(void **)(&real_open) = dlsym_handler(*handle_open, "open");
// 		*(void **)(&real_open) = wrap_your_func(handle_open, "open");
// 	}
// 	if (real_open != NULL) {
// 		if (*handle_open == NULL)
// 		{
// 			ft_putendl_fd("stop",1);
// 			handle_open = NULL;
// 			real_open = NULL;
// 			return (-2);	// not bad, handler was closed in another function
// 		}
// 		int fd = real_open(path, oflag);
// 		ft_putendl_fd("jovi", 1);
// 		return (fd);
// 	}
// 	return (-1);
// }

// int	main(void)
// {
// 	void	*handle;

// 	handle = MAP_FAILED;
// 	pass_handles(&handle);
// 	int fd = open("./wow.txt", O_RDONLY);
// 	char buff[10];
// 	int ret = read(fd, buff, 1);
// 	close(fd);
// 	write(1, buff, ret);
// 	handle_close(&handle);
// 	fd = open("./wow.txt", O_RDONLY);
// 	ft_putstr_fd("\nend\n", 1);
// 	return (0);
// }

// int open(const char *path, int oflag, ...)
// {
// 	static int (*real_open)(const char *, int, ...) = NULL;

// 	if (real_open == NULL) {
// 		*(void **)(&real_open) = wrap_your_func(get_handle(), "open");
// 		if (real_open == NULL)
// 		{
// 			return (-1);
// 		}
// 	}
// 	if (real_open != NULL) {
// 		if (*get_handle() == NULL)
// 		{
// 			ft_putendl_fd("handle closed",1);
// 			real_open = NULL;
// 			return (-2);	// not bad, handler was closed in another function
// 		}
// 		int fd = real_open(path, oflag);
// 		return (fd);
// 	}
// 	return (-1);
// }

// int main(void)
// {
// 	int fd = open("./wow.txt", O_RDONLY);
// 	close(fd);
// 	// handle_close(get_handle());
// 	fd = open("./wow.txt", O_RDONLY);
// 	char buff[10];
// 	int ret = read(fd, buff, 10);
// 	write(1, buff, ret);
// 	ft_putstr_fd("\nend\n", 1);
// 	return (0);
// }

// gcc -g -I ./include main.c -shared -o libft.so -Wl,--whole-archive libft.a -Wl,--no-whole-archive
// gcc -g -I ./include main.c libft.a && ./a.out

bool	set_malloc_amount(size_t size, void *ptr)
{
	static int	*input = NULL;

// write(1, "hello\n", 6);
	if (input == NULL)
	{
		input = (int *)ptr;
	}
	else if ((*input) > 0)
	{
		// write(1, "middle\n", 7);
		(*input)--;
	} else {
		// write(1, "SHOULDN'T see this message, use malloc_toggle()\n", 48);
		input = NULL;
		return (false);
	}
	return (true);
}

#include <libft.h>

bool	return_NULL_second_malloc(void)
{
	int		malloc_attempts = 1;
	char	*str;
	malloc_handler(0, &malloc_attempts, set_malloc_amount);
	str = malloc(1);
	if (str == NULL)
	{
		return (false);
	}
	free(str);
	str = malloc(1);
	if (str != NULL)
	{
		return (false);
	}
	errno = 0;
	return (true);
}

bool	allow_2_mallocs(void)
{
	int		malloc_attempts = 2;
	char	*str;
	malloc_handler(0, &malloc_attempts, set_malloc_amount);
	str = malloc(1);
	if (str == NULL)
	{
		return (false);
	}
	free(str);
	str = malloc(1);
	if (str == NULL)
	{
		return (false);
	}
	free(str);
	return (true);
}

bool	not_using_any_setup_functions_return_NULL(void)
{
	char	*str;
	str = malloc(1);
	if (str != NULL)
	{
		free(str);
		return (false);
	}
	return (true);
}

bool	real_malloc_shouldnot_change_attempts(void)
{
	int		malloc_attempts = 3;
	int		index = 0;
	char	*str;
	malloc_handler(0, &malloc_attempts, set_malloc_amount);
	malloc_toggle(SET_MALLOC);
	while (index != 5)
	{
		str = malloc(1);
		if (str == NULL)
		{
			ft_putendl_fd("not get here", 1);
			return (false);
		}
		free(str);
		++index;
	}
	malloc_toggle(SET_MALLOC);
	return (true);
}

bool	wrap_malloc_fail_but_real_malloc_success(void)
{
	int		malloc_attempts = 0;
	char	*str;
	malloc_handler(0, &malloc_attempts, set_malloc_amount);
	str = malloc(1);
	if (str != NULL)
	{
		ft_putendl_fd("naw",1);
		free(str);
		return (false);
	}
	malloc_toggle(SET_MALLOC);
	str = malloc(1);
	if (str == NULL)
	{
		ft_putendl_fd("naww",1);
		return (false);
	}
	free(str);
	malloc_toggle(SET_MALLOC);
	return (true);
}

bool	wrap_malloc_fail_but_forget_toggle_real_malloc(void)
{
	int		malloc_attempts = 0;
	char	*str;
	malloc_handler(0, &malloc_attempts, set_malloc_amount);
	str = malloc(1);
	if (str != NULL)
	{
		ft_putendl_fd("naw",1);
		free(str);
		return (false);
	}
	str = malloc(1);
	if (str != NULL)
	{
		free(str);
		return (false);
	}
	return (true);
}

void testing(bool (*ptr)(void))
{
	if (ptr() == true)
		write(1, "ok\n", 3);
	else
		write(1, "KO\n", 3);
}

#include <limits.h>
int main(void)
{
	malloc_toggle(SET_MALLOC);
	testing(return_NULL_second_malloc);
	testing(allow_2_mallocs);
	testing(not_using_any_setup_functions_return_NULL);
	testing(real_malloc_shouldnot_change_attempts);
	testing(wrap_malloc_fail_but_real_malloc_success);
	testing(wrap_malloc_fail_but_forget_toggle_real_malloc);

	// if (test1() == true)
	// 	write(1, "ok\n", 3);
	// else
	// 	write(1, "KO\n", 3);
	// if (test2() == true)
	// 	write(1, "ok\n", 3);
	// else
	// 	write(1, "KO\n", 3);
	// if (test3() == true)
	// 	write(1, "ok\n", 3);
	// else
	// 	write(1, "KO\n", 3);
	// t_ok	ok;
	// ok.i = 1;

	// write(1, "first\n", 6);
	// // malloc_toggle(SET_MALLOC);	//	switch to use_custom_malloc/use_real_malloc

	// malloc_handler(0, &ok, set_malloc_amount);
	// // malloc_toggle(SET_MALLOC);
	// ft_putendl_fd("hiero", 1);
	// char *str = ft_strdup("mooi\n");
	// ft_putendl_fd("passed strdup", 1);
    // if (str == NULL)
    // {
    //     ft_putendl_fd("malloc returned NULL", 1);
    // } else {
	// 	write(1, str, 5);
	// }

	// ft_putendl_fd("malloc voorbij", 1);
	// free(str);
	// ft_putendl_fd("freed", 1);
	// char *arr = ft_strdup("deze\n");
	// if (arr)
	// 	write(1, arr, 5);
	// free(arr);
	// handle_close(handle);
	// handle_close(handle);
	return (0);
}

// int	main(void)
// {
// 	void	*handle;

// 	handle = MAP_FAILED;
// 	pass_handles(&handle);
// 	int fd = open("./wow.txt", O_RDONLY);
// 	char buff[10];
// 	int ret = read(fd, buff, 1);
// 	close(fd);
// 	write(1, buff, ret);
// 	handle_close(&handle);
// 	fd = open("./wow.txt", O_RDONLY);
// 	ft_putstr_fd("\nend\n", 1);
// 	return (0);
// }