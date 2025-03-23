/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 23:07:48 by mdakni            #+#    #+#             */
/*   Updated: 2025/03/23 19:26:46 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int quote_handle(char const *s, int i)
{
    if(s[i] == '\'')
    {
        i++;
        while (s[i] != '\'' && s[i])
        {
            printf("s[i] = %c\n", s[i]);
            i++;
        }
        if (!s[i])
        {
            perror("Opened quotes error 1");
            exit(1);
        }
        i++;
    }
    else
    {
        i++;
        while (s[i] != '\"' && s[i])
            i++;
        if(!s[i])
        {
            perror("Opened quotes error 2");
            exit(1);
        }
        i++;
    }
    return (i);
}

size_t	count_word_pss(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{

            while (s[i] != c && s[i])
                i++;
            count++;
		}
		else
			i++;
	}
	return (count);
}
