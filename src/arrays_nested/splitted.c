/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   splitted.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:38:43 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/08 17:44:16 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

//	Static Functions
static void	ft_count(char const *s, char c, int *parts, int *sp_count);
static void	ft_enter_data(char	*data_block, int ptrs_l, char const *s, char c);

char	**splitted(char const *s, char c)
{
	int		ptrs_l;
	int		sp_count;
	char	*data_block;
	int		parts;

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

static void	ft_count(char const *s, char c, int *parts, int *sp_count)
{
	int		i;

	i = 0;
	while (s[i] != 0 && s[i] == c)
	{
		++i;
	}
	*sp_count = i;
	while (s[i] != 0)
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

static void	ft_enter_data(char	*data_block, int ptrs_l, char const *s, char c)
{
	int		i;
	int		j;
	int		skip;

	i = 0;
	j = 0;
	skip = 0;
	if (s[i] != c)
	{
		((char **)data_block)[j] = &data_block[ptrs_l];
		++j;
	}
	while (s[i] != 0)
	{
		if (s[i] == c && s[i] == s[i + 1] && s[i + 1] != '\0')
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
