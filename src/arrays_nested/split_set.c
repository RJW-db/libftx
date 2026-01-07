/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_set.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:39:22 by rjw           #+#    #+#                 */
/*   Updated: 2025/05/09 15:35:58 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libftx.h>

static size_t	count_words(const char *s, const char *set);
static bool		words(const char *s, const char *set, char **res, size_t *w_index);
static bool		split_alloc(const char *start, const char *end, char **r);

char	**split_set(const char *s, const char *set)
{
	char	**result;
	size_t	w_index;
	size_t	i;

	if (strs_ok(s, set) == false)
		return (NULL);
	result = malloc((count_words(s, set) + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	w_index = 0;
	if (words(s, set, result, &w_index) == false)
	{
		i = 0;
		while (w_index > i)
			free(result[i++]);
		free(result);
		return (NULL);
	}
	return (result);
}

static size_t	count_words(const char *s, const char *set)
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

static bool	words(const char *s, const char *set, char **res, size_t *w_index)
{
	const char	*start;

	start = (char *)s;
	while (*s)
	{
		if (!ft_strchr(set, *s))
			++s;
		else
		{
			if (start != s
				&& split_alloc(start, s, &res[(*w_index)++]) == false)
				return (false);
			start = ++s;
		}
	}
	if (start != s && split_alloc(start, s, &res[(*w_index)++]) == false)
		return (false);
	*(res + *w_index) = NULL;
	return (true);
}

static bool	split_alloc(const char *start, const char *end, char **r)
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
