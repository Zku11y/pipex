/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 00:31:58 by skully            #+#    #+#             */
/*   Updated: 2025/02/23 07:14:51 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_fd	file_manage(char **av, int i)
{
	t_fd fds;

	fds.fd1 = open("outfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	fds.fd2 = open(av[i], O_RDONLY);
	if (fds.fd1 == -1 || fds.fd2 == -1)
	{
		perror("\e[1;41mFd Error\e[0m\n");
		exit(1);
	}
	// printf("\e[1;41mfd1 = %d, fd2 = %d\e[0m\n", fds.fd1, fds.fd2);
	return (fds);
}

char	*path_parse(char **env, char *cmd)
{
	int		i;
	int		j;
	char *tmp;
	char *str;
	char	**str2;

	i = 0;
	j = 0;
	str = NULL;
	while (env[i])
	{
		str = ft_strnstr(env[i], "PATH", sizeof(env[i]));
		if (str)
		{
			// printf("\e[1;32m Path Found! : \n\e[0m\e[1;33m%s\e[0m\n", env[i]);
			break ;
		}
		i++;
	}
	str2 = ft_split(env[i] + 5, ':');
	while (str2[j])
	{
		str = ft_strjoin("/", cmd);
		tmp = ft_strjoin(str2[j], str);
		// printf("\e[1;31mPath : %d\e[0m \e[1;32m%s\e[0m\n", j, str2[j]);
		free(str);
		if (access(tmp, F_OK & X_OK) == 0)
		{
			// printf("\e[1;35m\nFound it! : \e[0m \e[1;36m%s\e[0m\n\n", str);
			break;
		}
		free(tmp);
		j++;
	}
	free_2(str2);
	return (tmp);
}

void free_2(char **str)
{
	int i;

	i = 0;
	while(str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

void	check_leaks(void)
{
	char	cmd[256];

	snprintf(cmd, sizeof(cmd), "leaks %d", getpid());
	system(cmd);
}
char	**cmd_parse(char **av, int index)
{
	int		i;
	char	**command;

	command = NULL;
	command = ft_split_ps(av[index], ' ');
	i = 0;
	// printf("im here!\n");
	while (command[i])
	{
		// printf("part %d : \e[1;44m%s\e[0m\n", i,  command[i]);
		i++;
	}
	return (command);
}
