/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wrap_malloc_tester.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 22:53:54 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/28 22:58:50 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <wrap_functions.h>
#include <libft.h>

/*
	inside the wrap_malloc_teser folder
	make -C ../../.. && gcc -I ../../../include wrap_malloc_tester.c ../../../libft.a && ./a.out
*/

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
		free(str);
		return (false);
	}
	malloc_toggle(SET_MALLOC);
	str = malloc(1);
	if (str == NULL)
	{
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

int main(void)
{
	malloc_toggle(SET_MALLOC);
	testing(return_NULL_second_malloc);
	testing(allow_2_mallocs);
	testing(not_using_any_setup_functions_return_NULL);
	testing(real_malloc_shouldnot_change_attempts);
	testing(wrap_malloc_fail_but_real_malloc_success);
	testing(wrap_malloc_fail_but_forget_toggle_real_malloc);
}
