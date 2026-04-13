/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   splitted.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:38:43 by rjw           #+#    #+#                 */
/*   Updated: 2025/05/09 15:36:41 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libftx.h>

static void	ft_count(const char *s, char c, size_t *parts, size_t *sp_count);
static void	\
ft_enter_data(char *data_block, size_t ptrs_l, const char *s, char c);

char	**splitted(const char *s, char c)
{
	size_t		ptrs_l;
	size_t		sp_count;
	char		*data_block;
	size_t		parts;

	parts = 1;
	sp_count = 0;
	ft_count(s, c, &parts, &sp_count);
	ptrs_l = sizeof(char *) * (parts + 1);
	data_block = ft_calloc((ptrs_l + ft_strlen(s) - sp_count + parts), 1);
	if (data_block == 0)
		return (NULL);
	if (*s == '\0')
	{
		((char **)data_block)[0] = NULL;
		return ((char **)data_block);
	}
	ft_enter_data(data_block, ptrs_l, s, c);
	return ((char **)data_block);
}

static void	ft_count(const char *s, char c, size_t *parts, size_t *sp_count)
{
	size_t		i;

	i = 0;
	while (s[i] != 0 && s[i] == c)
	{
		++i;
	}
	*sp_count = i;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			while (s[i] != 0 && s[i] == c)
			{
				++i;
			}
			*sp_count = i;
			if (s[i] == 0)
				return ;
			++(*parts);
		}
		else
			i++;
	}
}

static void	\
ft_enter_data(char *data_block, size_t ptrs_l, const char *s, char c)
{
	size_t		i;
	size_t		j;
	size_t		skip;

	i = 0;
	j = 0;
	skip = 0;
	if (s[i] != c)
	{
		((char **)data_block)[j] = &data_block[ptrs_l];
		++j;
	}
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i] == s[i + 1])
			++skip;
		if (s[i] == c && s[i] != s[i + 1] && s[i + 1] != '\0')
		{
			((char **)data_block)[j] = &data_block[i + ptrs_l + 1 - skip];
			++j;
		}
		else if (s[i] != c)
			data_block[i + ptrs_l - skip] = s[i];
		++i;
	}
}
