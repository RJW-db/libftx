/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   open_wrapper.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/03 15:41:56 by rde-brui      #+#    #+#                 */
/*   Updated: 2025/02/23 16:46:31 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <wrap_functions.h>

int open(const char *path, int oflag, ...)
{
	static int	(*real_open)(const char *, int, ...) = NULL;
	va_list		args;
	mode_t		mode;

	if (real_open == NULL)
	{
		*(void **)(&real_open) = dlsym_handler(RTLD_NEXT, "open");
		if (real_open == NULL) {
			// write(2, "Error: dlsym failed to find 'open': ", 36);
			// char *err = dlerror();
			// write(2, err, ft_strlen(err));;
			// ft_putendl_fd(dlerror(), 2);
			// errno = EINVAL;
			return -1;
		}
		mode = 0;
		if (oflag & O_CREAT) {
			va_start(args, oflag);
			mode = (mode_t)va_arg(args, int);
			va_end(args);	
		}

	}
	if (general_toggle(true) == true)
	{
		// ft_putendl_fd("real malloc being used", 1);
		if (real_open == NULL) {
			// ft_putendl_fd("should return NULL", 1);
			return (-1);
		}
		// ft_putendl_fd("or here", 1);

	} else if (general_handler(NULL, NULL) == false)
	{
		// ft_putendl_fd("FAILURE", 1);
		real_open = NULL;
		return (-1);
	}
	return (real_open(path, oflag, mode));
}

// int	use_va_list(const char *path, int oflag, mode_t mode)
// {

// 		if (oflag & O_CREAT) {
// 			va_start(args, oflag);
// 			mode = va_arg(args, mode_t);
// 			va_end(args);	
// 		}
// }

bool	general_handler(void *ptr, bool (*custom)(void *))
{
	static bool (*func)(void *) = NULL;

	if (func != NULL)
	{
		if (func(NULL) == true)
		{
			// ft_putendl_fd("using ptr function, true",1);
			return (true);
		}
		// ft_putendl_fd("failed using ptr function, false",1);
		func = NULL;
		return (false);
	}
	else if (func == NULL && custom != NULL && ptr != NULL)
	{
		// ft_putendl_fd("only once?",1 );
		func = custom;
		func(ptr);
		return (true);
	}
	// errno = EINVAL;
	return (false);
}

bool	general_toggle(bool check)
{
	static bool	switch_malloc = true;

	if (check == true)
	{
		return (switch_malloc);
	}
	else if (check == false)
	{
		switch_malloc = !switch_malloc;
	}
	return (switch_malloc);
}
