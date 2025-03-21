/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   deallocation.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/09 20:31:53 by rde-brui      #+#    #+#                 */
/*   Updated: 2025/03/21 18:52:21 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
	Used functions:
	- free
	
	usage:
	char *ptr = "see this as a malloced pointer";

	free_ptr(&ptr);
*/
void	*free_ptr(void **ptr)
{
	if (dp_ptr_ok(ptr) == true)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}

/*
	Used functions:
	- free

	usage:
	char *str = "see this as a malloced string";

	free_str((char **)&str);
*/
void	*free_str(char **str)
{
	if (dpstr_ok(str) == true)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}
