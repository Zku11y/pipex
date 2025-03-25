/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 05:44:10 by mdakni            #+#    #+#             */
/*   Updated: 2025/03/25 16:35:48 by skully           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

size_t	count_word_ps(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			while (s[i] != c && s[i])
			{
				if (s[i] == '\'')
				{
					i++;
					while (s[i] != '\'' && s[i])
						i++;
				}
				i++;
			}
			count++;
		}
	}
	return (count);
}

char	**check_is_path(char **cmd)
{
	char	*str;

	int (i), (start);
	i = 0;
	start = 0;
	if(!cmd || !cmd[0])
		return(free_2(cmd), NULL);
	if (cmd[0][0] == '/')
	{
		if (access(cmd[0], F_OK & X_OK) != 0)
		{
			free(cmd[0]);
			cmd[0] = NULL;
			return (free_2(cmd), NULL);
		}
		while (cmd[0][i])
		{
			if (cmd[0][i] == '/')
				start = i;
			i++;
		}
		str = ft_substr(cmd[0], start + 1, i - start);
		if(!str)
			return(free_2(cmd), NULL);
		return(free(cmd[0]), cmd[0] = str, cmd);
	}
	return(0);
}

void close_fds(int *fd_pipe, int fd)
{
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	close(fd);
}

void	cmd1(int fd, char **cmd, char *path, int *fd_pipe)
{
	if (dup2(fd, STDIN_FILENO) == -1 || dup2(fd_pipe[1], STDOUT_FILENO) == -1)
	{
		perror("\e[1;41mFirst Dup Error\e[0m");
		close_fds(fd_pipe, fd);
		free_allocs(path, cmd);
		exit(EXIT_FAILURE);
	}
	close_fds(fd_pipe, fd);
	if(!cmd || !(*cmd) || !path)
		(perror("\e[1;41mCommand 1 Error\e[0m") ,free_allocs(path, cmd), exit(1));
	if (execve(path, cmd, NULL) == -1)
	{
		perror("\e[1;41mFirst Execve Error\e[0m");
		free_allocs(path, cmd);
		exit(EXIT_FAILURE);
	}
}

void	cmd2(int fd, char **cmd, char *path, int *fd_pipe)
{
	if (dup2(fd, STDOUT_FILENO) == -1 || dup2(fd_pipe[0], STDIN_FILENO) == -1)
	{
		perror("\e[1;41mSecond Dup Error\e[0m");
		close_fds(fd_pipe, fd);
		free_allocs(path, cmd);
		exit(EXIT_FAILURE);
	}
	close_fds(fd_pipe, fd);
	if(!cmd || !(*cmd) || !path)
		(perror("\e[1;41mCommand 2 Error\e[0m") ,free_allocs(path, cmd), exit(1));
	if (execve(path, cmd, NULL) == -1)
	{
		perror("\e[1;41mSecond Execve Error\e[0m");
		free_allocs(path, cmd);
		exit(EXIT_FAILURE);
	}
}
