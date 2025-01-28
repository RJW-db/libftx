/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dynarr.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/09 20:31:53 by rde-brui      #+#    #+#                 */
/*   Updated: 2025/01/19 02:28:45 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <dynarr.h>

bool	dynarr_create(t_dynarr *ptr, size_t init_size, const size_t data_size)
{
	if (ptr == NULL || data_size == 0)
		return (false);
	*(size_t *)&ptr->elem_size = data_size;
	ptr->capacity = init_size;
	ptr->length = 0;
	ptr->arr = ft_calloc(init_size, data_size);
	if (ptr->arr == NULL)
		return (false);
	return (true);
}

/**
 * use this function in a if statement and check for ENOMEM.
 */
bool	dynarr_shrink_to_fit(t_dynarr *a)
{
	void	*ar;

	if (a == NULL || a->arr == NULL)
		return (false);
	ar = ft_realloc(&a->arr, a->length * a->elem_size, a->capacity * a->elem_size);
	if (ar == NULL)
		return (false);
	a->arr = ar;
	a->capacity = a->length;
	return (true);
}

void	dynarr_free(t_dynarr *a)
{
	free_ptr(&a->arr);
	*(size_t *)&a->elem_size = 0;
	a->capacity = 0;
	a->length = 0;
}

void	*dynarr_take_arr(t_dynarr *a)
{
	void	*arr_copy;

	if (a == NULL || a->arr == NULL)
		return (NULL);
	arr_copy = a->arr;
	a->arr = NULL;
	dynarr_free(a);
	return (arr_copy);
}

// void	showcase(t_dynarr myArray)
// {
// 	for (size_t i = 0; i < myArray.length; i++)
// 	{
// 		printf("%d ", ((int *)myArray.arr)[i]);
// 	}
// 	printf("\n");
// }
// int	main()
// {
// 	t_dynarr myArray;
// 	int initialSize = 5;
// 	int dataSize = sizeof(int);

// 	if (!dynarr_create(&myArray, initialSize, dataSize))
// 	{
// 		return 1;
// 	}
// 	for (int i = 0; i < 15; i++)
// 	{
// 		dynarr_insert(&myArray, &i);
// 	}
// 	showcase(myArray);
// 	printf("\t%zu\n", myArray.capacity);
// 	dynarr_shrink_to_fit(&myArray);
// 	printf("\t%zu\n", myArray.capacity);

// 	size_t	arr_len = myArray.length;
// 	int cpy_value = ((int *)myArray.arr)[5];
// 	int	*arr = dynarr_take_arr(&myArray);
// 	printf("copied value = %d\n", cpy_value);
// 	printf("set to 0 %ld\n", myArray.capacity);
// 	printf("set to 0 %ld\n", myArray.elem_size);
// 	printf("set to 0 %ld\n", myArray.length);

// 	printf("extracted array from dynarr %d\n", arr[0]);
// 	return (0);
// }