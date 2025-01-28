/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   2d_array_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:39:53 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/08 17:44:16 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

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
 * 	Used functions:
 * 	- expand_2d_array
 * 	-	count_arr_2d
	-	malloc
	-	free
	- count_arr_2d
	- ft_strdup
	-	malloc
	- free_2d_arr
	- 	free
 *
 * expand array and add string pointer at the end.
 * if NULL is returned check errno for ENOMEM.
 * Expand_2d will set arr to NULL
 * in this scope, and if ft_strdup fails it will return NULL and thus,
 * overwriting a malloced arr(in previous func) with NULL, unable to free.
*/
char	**add_str_arr(char **arr, char *str)
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

/*
	Used functions:
	- ft_putendl_fd
*/
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
