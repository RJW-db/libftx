/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   2d_shrink_array.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:39:30 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/09 20:34:37 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

//	Static Functions
static void	transfer(char **arr, char **new_arr, size_t target, size_t arr_len);
static void	transfer_all(char ***arr, char **new_arr, char *rm, size_t arr_len);

/**
	Find and removes the that index, moves all next index back one step.
	
	Use find_rm_2d_arr() or find_rm_all_2d_arr for correct malloc size,
	don't use this function	if you gonna use expand_2d_array() as well.
*/
char	**search_rm_2d_arr(char **arr, char *rm)
{
	size_t	arr_len;
	size_t	i;

	if (arr == NULL || rm == NULL)
		return (NULL);
	i = -1;
	while (arr[++i] != NULL)
	{
		if (ft_strncmp(arr[i], rm, ft_strlen(rm) + 1) == 0 \
			&& free_str(&arr[i]) == NULL)
			break ;
	}
	if (arr[i] == NULL)
		return (NULL);
	arr_len = count_arr_2d(arr);
	if (arr_len != i && arr[i] == NULL)
	{
		while (arr[i + 1] != NULL)
		{
			arr[i] = arr[i + 1];
			++i;
		}
		arr[i] = NULL;
	}
	return (arr);
}

/**
	Counts array indexes, mallocs new array.
	Find and removes that index, moves all next index back one step.
*/
char	**find_rm_2d_arr(char ***arr, char *rm)
{
	char	**new_arr;
	size_t	arr_len;
	size_t	target;

	if (arr == NULL || *arr == NULL || rm == NULL)
		return (NULL);
	target = 0;
	while ((*arr)[target] != NULL)
	{
		if (ft_strncmp((*arr)[target], rm, ft_strlen(rm) + 1) == 0)
			break ;
		++target;
	}
	if ((*arr)[target] == NULL)
		return (NULL);
	arr_len = count_arr_2d(*arr);
	new_arr = (char **)malloc(arr_len * sizeof(char *));
	if (new_arr == NULL)
		return (NULL);
	transfer(*arr, new_arr, target, --arr_len);
	free((*arr)[target]);
	free(*arr);
	*arr = NULL;
	return (new_arr);
}

char	**find_rm_all_2d_arr(char ***arr, char *rm)
{
	char	**new_arr;
	size_t	rm_len;
	size_t	arr_len;
	size_t	target;
	size_t	count;

	if (arr == NULL || *arr == NULL || rm == NULL)
		return (NULL);
	target = 0;
	count = 0;
	rm_len = ft_strlen(rm);
	while ((*arr)[target] != NULL)
	{
		if (ft_strncmp((*arr)[target], rm, rm_len + 1) == 0)
			++count;
		++target;
	}
	arr_len = count_arr_2d(*arr);
	if (arr_len == count || (*arr)[target] == NULL)
		return (NULL);
	new_arr = (char **)malloc((arr_len - count + 1) * sizeof(char *));
	if (new_arr == NULL)
		return (NULL);
	transfer_all(arr, new_arr, rm, arr_len - 1);
	return (new_arr);
}

static void	transfer(char **arr, char **new_arr, size_t target, size_t arr_len)
{
	size_t	i;

	i = 0;
	while (i <= arr_len)
	{
		if (i == target)
		{
			++arr;
			--target;
			continue ;
		}
		new_arr[i] = arr[i];
		++i;
	}
}

static void	transfer_all(char ***arr, char **new_arr, char *rm, size_t arr_len)
{
	size_t	rm_len;
	size_t	i;
	size_t	j;

	rm_len = ft_strlen(rm);
	i = 0;
	j = 0;
	while (i <= arr_len)
	{
		if (ft_strncmp((*arr)[i], rm, rm_len + 1) == 0)
		{
			free_str(&(*arr)[i]);
			++i;
			continue ;
		}
		new_arr[j] = (*arr)[i];
		++i;
		++j;
	}
	new_arr[j] = NULL;
	free(*arr);
	*arr = NULL;
}
