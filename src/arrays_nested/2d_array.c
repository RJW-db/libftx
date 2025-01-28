/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   2d_array.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:39:46 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/08 17:44:16 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

/**
 * 	Used functions:
	- malloc
	- ft_strdup
	-	ft_strlen
	-	ft_strlcpy
	- free_2d_arr
	-	free
*/
char	**cpy_2d_array(char **arr)
{
	char	**new_arr;
	size_t	count;
	size_t	i;

	if (arr == NULL)
		return (NULL);
	count = count_arr_2d(arr);
	new_arr = (char **)malloc((count + 1) * sizeof(char *));
	if (new_arr == NULL)
		return (NULL);
	new_arr[count] = NULL;
	i = 0;
	while (i < count)
	{
		new_arr[i] = ft_strdup(arr[i]);
		if (new_arr[i] == NULL)
			return (free_2d_arr(&new_arr), NULL);
		++i;
	}
	return (new_arr);
}

/**
 * 	Used functions:
 	- count_arr_2d
	- malloc
	- free

 * malloc + 1 because for the already existing NULL.
 * frees old 2D array.
 *
 * CAUTION you gotta ft_strdup() on the newly added rows, if you use
 * stack pointers you will get this message: "free(): invalid pointer".
*/
char	**expand_2d_array(char ***arr, size_t add_rows)
{
	size_t	i;
	char	**new_arr;

	if (arr == NULL || *arr == NULL)
		return (NULL);
	i = count_arr_2d(*arr);
	new_arr = (char **)malloc((i + add_rows + 1) * sizeof(char *));
	if (new_arr == NULL)
		return (NULL);
	while (add_rows > 0)
	{
		new_arr[i + add_rows] = NULL;
		--add_rows;
	}
	while (i > 0)
	{
		new_arr[i] = (*arr)[i];
		--i;
	}
	new_arr[i] = (*arr)[i];
	free(*arr);
	*arr = NULL;
	return (new_arr);
}

/*
	free double array and set to NULL.

	Used functions:
	- free
*/
void	free_2d_arr(char ***arr)
{
	size_t	i;

	i = 0;
	if (arr != NULL && *arr != NULL)
	{
		while ((*arr)[i] != NULL)
		{
			free_str(&(*arr)[i]);
			++i;
		}
		free(*arr);
	}
	*arr = NULL;
}
