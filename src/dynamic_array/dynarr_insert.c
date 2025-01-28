/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dynarr_insert.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/09 20:19:40 by rde-brui      #+#    #+#                 */
/*   Updated: 2025/01/19 04:05:04 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <dynarr.h>

//	Static functions
static size_t	get_growth_factor(size_t length, size_t capacity);
static bool		dynarr_grow(t_dynarr *a);

#include <stdio.h>
bool	dynarr_insert(t_dynarr *a, t_cvoid *element)
{
	if (a == NULL)
	{
		return (false);
	}
	if (a->length == a->capacity && dynarr_grow(a) == false)
	{
		return (false);
	}
	ft_memcpy(a->arr + (a->length * a->elem_size), element, a->elem_size);
	++a->length;
	return (true);
}

static bool	dynarr_grow(t_dynarr *a)
{
	const size_t	old_size = a->capacity * a->elem_size;
	size_t			new_capacity;
	void			*new_arr;

	new_capacity = get_growth_factor(a->length, a->capacity);
	new_arr = ft_realloc(&a->arr, new_capacity * a->elem_size, old_size);
	if (new_arr == NULL && a->arr != NULL)
	{
		return (false);
	}
	a->capacity = new_capacity;
	a->arr = new_arr;
	if (new_capacity < a->length)
		a->length = new_capacity;
	return (true);
}

static size_t	get_growth_factor(size_t length, size_t capacity)
{
	const size_t	thresholds[NUM_THRESHOLDS] = {1000000, 500000, 250000};
	const float		factors[NUM_THRESHOLDS] = {1.25f, 1.5f, 1.75f};
	size_t			i;

	if (length < thresholds[0])
	{
		return (capacity * 2);
	}
	i = 0;
	while (i < NUM_THRESHOLDS)
	{
		if (length > thresholds[i])
		{
			break ;
		}
		++i;
	}
	return (capacity * factors[i]);
}
