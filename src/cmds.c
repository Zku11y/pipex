/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 05:44:10 by mdakni            #+#    #+#             */
/*   Updated: 2025/03/24 17:23:43 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

size_t	count_word_ps(char const *s, char c)
{
	size_t	i;
	size_t	count;
	bool	inside_quotes;

	i = 0;
	count = 0;
	inside_quotes = false;
	while (s[i])
	{
		if (s[i] == '\'')
			inside_quotes = !inside_quotes;
		if (s[i] != c || inside_quotes)
		{
			while ((s[i] != c || inside_quotes) && s[i])
			{
				if (s[i] == '\'')
					inside_quotes = !inside_quotes;
				i++;
			}
			count++;
		}
		else
			i++;
	}
	return (count);
}

void	check_is_path(char **cmd)
{
	int		i;
	int		start;
	char	*str;

	i = 0;
	start = 0;
	if (cmd[0][0] == '/')
	{
		if (access(cmd[0], F_OK & X_OK) != 0)
		{
			free(cmd[0]);
			cmd[0] = NULL;
			return ;
		}
		while (cmd[0][i])
		{
			if (cmd[0][i] == '/')
				start = i;
			i++;
		}
		str = ft_substr(cmd[0], start + 1, i - start);
		free(cmd[0]);
		cmd[0] = str;
	}
}

void	cmd1(int fd, char **cmd, char *path, int *fd_pipe)
{
	if (dup2(fd, STDIN_FILENO) == -1 || dup2(fd_pipe[1], STDOUT_FILENO) == -1)
	{
		perror("\e[1;41mFirst Dup Error\e[0m");
		exit(EXIT_FAILURE);
	}
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	close(fd);
	if (execve(path, cmd, NULL) == -1)
	{
		perror("\e[1;41mFirst Execve Error\e[0m");
		exit(EXIT_FAILURE);
	}
}

void	cmd2(int fd, char **cmd, char *path, int *fd_pipe)
{
	if (dup2(fd, STDOUT_FILENO) == -1 || dup2(fd_pipe[0], STDIN_FILENO) == -1)
	{
		perror("\e[1;41mSecond Dup Error\e[0m");
		exit(EXIT_FAILURE);
	}
	close(fd_pipe[1]);
	close(fd_pipe[0]);
	close(fd);
	if (execve(path, cmd, NULL) == -1)
	{
		perror("\e[1;41mSecond Execve Error\e[0m");
		exit(EXIT_FAILURE);
	}
}
