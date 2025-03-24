/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:08:45 by skully            #+#    #+#             */
/*   Updated: 2025/03/24 13:45:42 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void systema()
{
    char cmd[50];
    snprintf(cmd, sizeof(cmd), "leaks %d", getpid());
    system(cmd);
}

void manager_2(int *fd, t_fd fds, char **env, char **av, pid_t pid)
{
	char	*path;
	char	**command;

	command = cmd_parse(av, 3);
	check_is_path(command);
	path = path_parse(env, command[0]);
	if (!pid)
	{
		if(fds.fd1 == -1)
		{
			perror("\e[41mOutfile Error\e[0m\n");
			exit(1);
		}
		close(fds.fd2);
		cmd2(fds.fd1, command, path, fd);
	}
	else
	{
		free(path);
		free_2(command);
		close(fd[0]);
		close(fd[1]);
		close(fds.fd1);
		close(fds.fd2);
	}
}

void manager_1(int *fd,t_fd fds, char **env, char **av, pid_t pid)
{
	char	*path;
	char	**command;

	command = cmd_parse(av, 2);
	check_is_path(command);
	path = path_parse(env, command[0]);
	if (!pid)
	{
		if(fds.fd2 == -1)
		{
			perror("\e[41mInfile Error\e[0m\n");
			exit(1);
		}
		close(fds.fd1);
		cmd1(fds.fd2, command, path, fd);
	}
	else
	{
		free(path);
		free_2(command);
	}	
}

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	t_pid	pid;
	t_fd	fds;

	check_leaks();
	fds = file_manage(av, 1);
	if (ac != 5)
	{
		ft_putstr_fd("\e[1;33mUsage: ./pipex infile cmd1 cmd2 outfile\e[0m\n", 1);
		return (1);
	}
	if (pipe(fd) == -1)
		return (perror("\e[1;41mPipe error\e[0m\n"), 1);
	pid.pid1 = fork();
	if (pid.pid1 == -1)
		return (perror("\e[1;41mFirst Fork error\e[0m\n"), 1);
	manager_1(fd, fds, env, av, pid.pid1);
	pid.pid2 = fork();
	if (pid.pid2 == -1)
		return (perror("\e[1;41mSecond Fork error\e[0m\n"), 1);
	manager_2(fd, fds, env, av, pid.pid2);
	waitpid(pid.pid2, NULL, 0);
    waitpid(pid.pid1, NULL, 0);
	return (0);
}
