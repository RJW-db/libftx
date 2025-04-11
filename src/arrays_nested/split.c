/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:38:52 by rjw           #+#    #+#                 */
/*   Updated: 2025/04/11 01:29:39 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

//	Static Functions
static size_t	count_words(t_cchr *s, char c);
static bool		words(t_cchr *s, char c, char **res, int *w_index);
static bool		split_alloc(t_cchr *start, t_cchr *end, char **r);

/*
	Used functions:
	- malloc
	- ft_strlcpy
	- free
*/
char	**split(char const *s, char c)
{
	char	**result;
	int		w_index;
	int		i;

	if (s == NULL)
		return (NULL);
	result = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	w_index = 0;
	if (words(s, c, result, &w_index) == false)
	{
		i = 0;
		while (w_index > i)
			free(result[i++]);
		free(result);
		return (NULL);
	}
	return (result);
}

static size_t	count_words(t_cchr *s, char c)
{
	size_t	count;
	size_t	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c)
		{
			if (in_word == 0)
			{
				count++;
				in_word = 1;
			}
		}
		else
			in_word = 0;
		++s;
	}
	return (count);
}

static bool	words(t_cchr *s, char c, char **res, int *w_index)
{
	char	*start;

	start = (char *)s;
	while (*s)
	{
		if (*s != c)
			++s;
		else
		{
			if (start != s
				&& split_alloc(start, s, &res[(*w_index)++]) == false)
				return (false);
			start = (char *)++s;
		}
	}
	if (start != s && split_alloc(start, s, &res[(*w_index)++]) == false)
		return (false);
	*(res + *w_index) = NULL;
	return (true);
}

static bool	split_alloc(t_cchr *start, t_cchr *end, char **r)
{
	size_t	len;

	len = (size_t)(end - start);
	*r = (char *)malloc((len + 1) * sizeof(char));
	if (*r == NULL)
		return (false);
	if (ft_strlcpy(*r, start, len + 1) == 0)
		return (false);
	return (true);
}
