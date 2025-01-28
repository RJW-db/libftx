/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dynarr.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/09 20:34:59 by rde-brui      #+#    #+#                 */
/*   Updated: 2025/01/09 21:32:45 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYNARR_H
# define DYNARR_H
# define NUM_THRESHOLDS 3

# include <libft.h>
# include <stdlib.h>
# include <stdbool.h>

/*
 * arr is the internal array
 * elem_size is the length of the data type (sizeof <type>)
 * capacity is the length (in objects!) of the internal array
 * length is the amount of objects currently in the array
*/
typedef struct s_dynarr
{
	void		*arr;
	t_csize_t	elem_size;
	size_t		capacity;
	size_t		length;
}	t_dynarr;

bool	dynarr_create(t_dynarr *ptr, size_t init_size, const size_t data_size);
bool	dynarr_insert(t_dynarr *a, t_cvoid *element);
bool	dynarr_shrink_to_fit(t_dynarr *a);
void	dynarr_free(t_dynarr *a);
void	*dynarr_take_arr(t_dynarr *a);

#endif
