/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   2d_array_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:39:53 by rjw           #+#    #+#                 */
/*   Updated: 2025/05/08 21:22:44 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libftx.h>

size_t	count_arr_2d(char **arr)
{
	size_t	i;

	if (arr == NULL)
		return (0);
	i = 0;
	while (arr[i] != NULL)
		++i;
	return (i);
}

/**
 * expand array and add string pointer at the end.
 * if NULL is returned check errno for ENOMEM.
 * Expand_2d will set arr to NULL
 * in this scope, and if ft_strdup fails it will return NULL and thus,
 * overwriting a malloced arr(in previous func) with NULL, unable to free.
*/
char	**add_str_arr(char **arr, const char *str)
{
	char	**new_arr;
	size_t	count;

	if (arr == NULL || str == NULL)
		return (free_2d_arr(&arr), NULL);
	new_arr = expand_2d_array(&arr, 1);
	if (new_arr == NULL)
		return (free_2d_arr(&arr), NULL);
	free(arr);
	count = count_arr_2d(new_arr);
	new_arr[count] = ft_strdup(str);
	if (new_arr[count] == NULL)
	{
		free_2d_arr(&new_arr);
		return (NULL);
	}
	new_arr[count + 1] = NULL;
	return (new_arr);
}

void	print_2d_array(char **arr)
{
	size_t	i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i] != NULL)
	{
		ft_putendl_fd(arr[i], STDOUT_FILENO);
		++i;
	}
}
