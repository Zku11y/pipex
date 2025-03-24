/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 00:31:58 by skully            #+#    #+#             */
/*   Updated: 2025/03/24 17:18:12 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_fd	file_manage(char **av, int i)
{
	t_fd	fds;

	fds.fd1 = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	fds.fd2 = open(av[i], O_RDONLY);
	return (fds);
}

int	check_perms(char **env)
{
	char	*str;
	int		i;

	i = 0;
	while (env[i])
	{
		str = ft_strnstr(env[i], "PATH", sizeof(env[i]));
		if (str)
			break ;
		i++;
	}
	return (i);
}

char	*path_parse(char **env, char *cmd)
{
	int		i;
	int		j;
	char	*tmp;
	char	*str;
	char	**str2;

	i = 0;
	j = 0;
	str = NULL;
	if (cmd == NULL)
		return (NULL);
	i = check_perms(env);
	str2 = ft_split(env[i] + 5, ':');
	while (str2[j])
	{
		str = ft_strjoin("/", cmd);
		tmp = ft_strjoin(str2[j], str);
		free(str);
		if (access(tmp, F_OK & X_OK) == 0)
			break ;
		free(tmp);
		tmp = NULL;
		j++;
	}
	return (free_2(str2), tmp);
}

void	free_2(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

char	**cmd_parse(char **av, int index)
{
	char	**command;

	command = NULL;
	command = ft_split_ps(av[index], ' ');
	return (command);
}
