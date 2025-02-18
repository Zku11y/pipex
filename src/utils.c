/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 00:31:58 by skully            #+#    #+#             */
/*   Updated: 2025/02/18 22:46:12 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	file_manage(char **av)
{
	int	outfile;

	outfile = open("outfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		perror("Fd Error");
		exit(1);
	}
	if (access(av[1], F_OK & R_OK) == -1)
	{
		close(outfile);
		perror("Infile Error");
		exit(1);
	}
}

char	*path_parse(char **env)
{
	int		i;
	int		j;
	char	*str;
	char	**str2;

	i = 0;
	j = 0;
	str = NULL;
	while (env[i])
	{
		str = ft_strnstr(env[i], "PATH", sizeof(env[i]));
		if (str)
		{
			printf("\e[1;32m Path Found! : \n\e[0m\e[1;33m%s\e[0m\n", env[i]);
			break ;
		}
		i++;
	}
	str2 = ft_split(env[i] + 5, ':');
	while (str2[j])
	{
		printf("\e[1;31mPath %d :\e[0m \e[1;32m%s\e[0m\n", j, str2[j]);
		if (access(ft_strjoin(str2[j], "/cat"), F_OK & X_OK) == 0)
		{
			printf("\e[1;35m\nFound it! : \e[0m \e[1;36m%s\e[0m\n\n",
				ft_strjoin(str2[j], "/cat"));
			break ;
		}
		j++;
	}
	return (ft_strjoin(str2[j], "/cat"));
}
void	check_leaks(void)
{
	char	cmd[256];

	snprintf(cmd, sizeof(cmd), "leaks %d", getpid());
	system(cmd);
}
char	**cmd_parse(char **av)
{
	int		i;
	char	**command;

	if (!ft_strchr(av[2], '\'') && !ft_strchr(av[2], '\"'))
		command = ft_split(av[2], ' ');
	return (NULL);
}
