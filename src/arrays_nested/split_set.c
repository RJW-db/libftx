/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_set.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:39:22 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/08 17:44:16 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

//	Static Functions
static size_t	count_words(t_cchr *s, char *set);
static int		words(t_cchr *s, char *set, char **res, int *w_index);
static int		alloc(t_cchr *start, t_cchr *end, char **r);

/*
	Used functions:
	- malloc
	- ft_strlcpy
	- ft_strchr
	- free
*/
char	**split_set(char const *s, char *set)
{
	char	**result;
	int		w_index;
	int		i;

	if (strs_ok(s, set) == false)
		return (NULL);
	result = malloc((count_words(s, set) + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	w_index = 0;
	if (words(s, set, result, &w_index) == EXIT_FAILURE)
	{
		i = 0;
		while (w_index > i)
			free(result[i++]);
		free(result);
		return (NULL);
	}
	return (result);
}

static size_t	count_words(t_cchr *s, char *set)
{
	size_t	count;
	bool	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (!ft_strchr(set, *s))
		{
			if (!in_word)
			{
				count++;
				in_word = 1;
			}
		}
		else
			in_word = 0;
		s++;
	}
	return (count);
}

static int	words(t_cchr *s, char *set, char **res, int *w_index)
{
	char	*start;

	start = (char *)s;
	while (*s)
	{
		if (!ft_strchr(set, *s))
			++s;
		else
		{
			if (start != s
				&& alloc(start, s, &res[(*w_index)++]) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			start = (char *)++s;
		}
	}
	if (start != s && alloc(start, s, &res[(*w_index)++]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	*(res + *w_index) = NULL;
	return (EXIT_SUCCESS);
}

static int	alloc(t_cchr *start, t_cchr *end, char **r)
{
	int	len;

	len = end - start;
	*r = (char *)malloc((len + 1) * sizeof(char));
	if (*r == NULL)
		return (EXIT_FAILURE);
	if (!ft_strlcpy(*r, start, len + 1))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
