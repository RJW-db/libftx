/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   open_wrapper.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/03 15:41:56 by rde-brui      #+#    #+#                 */
/*   Updated: 2025/03/19 02:49:38 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <wrap_functions.h>

//	Static Functions
static int	handle_general_conditions(int (**real_open)(const char *, int, ...));

int	open(const char *path, int oflag, ...)
{
	static int	(*real_open)(const char *, int, ...) = NULL;
	va_list		args;
	mode_t		mode;

	if (real_open == NULL)
	{
		*(void **)(&real_open) = dlsym_handler(RTLD_NEXT, "open");
		if (real_open == NULL)
		{
			errno = EINVAL;
			return (-1);
		}
		mode = 0;
		if (oflag & O_CREAT)
		{
			va_start(args, oflag);
			mode = (mode_t)va_arg(args, int);
			va_end(args);
		}
	}
	if (handle_general_conditions(&real_open) == -1)
		return (-1);
	return (real_open(path, oflag, mode));
}

static int	handle_general_conditions(int (**real_open)(const char *, int, ...))
{
	if (general_toggle(true) == true)
	{
		if (*real_open == NULL)
			return (-1);
	}
	else if (general_handler(NULL, NULL) == false)
	{
		*real_open = NULL;
		return (-1);
	}
	return (0);
}
