/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:50:16 by mdakni            #+#    #+#             */
/*   Updated: 2025/02/19 01:47:12 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int	size_word(char const *s, char c)
{
	int	i;

	i = 0;
	if (*(s - 1) == '\'')
	{
		i++;
		while (s[i] != '\'' && s[i])
		{
			i++;
			printf("%c\n", s[i]);
		}
	}
	else if (*(s - 1) == '\"')
	{
		i++;
		while (s[i] != '\"' && s[i])
			i++;
	}
	else
	{
		while (s[i] != c && s[i])
			i++;
	}
	return (i);
}

static void	free_mem(char **answer, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
		free(answer[i++]);
	free(answer);
}

static char	**insert_word(char **answer, size_t count, char const *s, char c)
{
	size_t	i;
	size_t	index;

	i = 0;
	index = 0;
	while (index < count)
	{
		while (s[i] == c && s[i])
			i++;
		if (!s[i])
			return (answer);
		if (s[i] == '\'' || s[i] == '\'')
			i++;
		answer[index] = ft_substr(s, i, size_word(s + i, c));
		if (answer[index] == NULL)
		{
			free_mem(answer, index);
			return (NULL);
		}
		i += size_word(s + i, c);
		index++;
	}
	return (answer);
}

char	**ft_split_ps(char const *s, char c)
{
	char **answer;
	size_t count;

	if (!s)
		return (NULL);
	count = count_word_pss(s, c);
	answer = malloc(sizeof(char *) * (count + 1));
	if (answer == NULL)
		return (NULL);
	answer[count] = NULL;
	return (insert_word(answer, count, s, c));
}
