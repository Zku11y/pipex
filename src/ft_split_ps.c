/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:50:16 by mdakni            #+#    #+#             */
/*   Updated: 2025/03/24 21:21:16 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include <stdbool.h>

static int	size_word(char const *s, char c)
{
	int		i;
	bool	inside_quotes;

	i = 0;
	inside_quotes = false;
	while (s[i])
	{
		if (s[i] == '\'')
			inside_quotes = !inside_quotes;
		else if (s[i] == c && !inside_quotes)
			break ;
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

static char	*extract_word_without_quotes(char const *s, int size)
{
	char	*word;
	int		i;
	int		j;

	word = (char *)malloc(sizeof(char) * (size + 1));
	if (!word)
		return (NULL);
	i = 0;
	j = 0;
	while (i < size)
	{
		if (s[i] != '\'')
			word[j++] = s[i];
		i++;
	}
	word[j] = '\0';
	return (word);
}

static char	**insert_word(char **answer, size_t count, char const *s, char c)
{
	size_t	i;
	size_t	index;
	int		size;

	i = 0;
	index = 0;
	while (index < count)
	{
		while (s[i] == c && s[i])
			i++;
		if (!s[i])
			return (answer);
		size = size_word(s + i, c);
		answer[index] = extract_word_without_quotes(s + i, size);
		if (answer[index] == NULL)
		{
			free_mem(answer, index);
			return (NULL);
		}
		i += size;
		if (s[i] == c)
			i++;
		index++;
	}
	return (answer);
}

char	**ft_split_ps(char const *s, char c)
{
	char	**answer;
	size_t	count;

	if (!s)
		return (NULL);
	count = count_word_ps(s, c);
	answer = malloc(sizeof(char *) * (count + 1));
	if (answer == NULL)
		return (NULL);
	answer = insert_word(answer, count, s, c);
	answer[count] = NULL;
	return (answer);
}
