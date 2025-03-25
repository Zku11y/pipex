/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:08:45 by skully            #+#    #+#             */
/*   Updated: 2025/03/25 17:05:25 by skully           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	check_leaks(void)
{
	system("leaks -q pipex");
}

void free_allocs(char *path, char **cmd)
{
	free(path);
	free_2(cmd);
}

bool is_empty(char **cmd)
{
	int i;

	i = 0;
	if(!cmd || !cmd[0])
	return(true);
	while(cmd[0][i] == ' ')
	i++;
	printf("here\n");
	if(cmd[0][i] == '\0')
		return(true);
	return(false);
}

pid_t	manager_2(int *fd, t_fd fds, char **env, char **av)
{
	char	*path;
	char	**command;
	pid_t	pid;

	command = cmd_parse(av, 3);
	check_is_path(command);
	if(command == NULL)
		path = NULL;
	else
		path = path_parse(env, command[0]);
	pid = fork();
	if (pid == -1)
		return (perror("\e[1;41mSecond Fork error\e[0m\n"), free_allocs(path, command),exit(1), -1);
	if (!pid)
	{
		if (fds.fd1 == -1)
		{
			close_fds(fd, fds.fd1);
			free_allocs(path, command);
			exit(1);
		}
		close(fds.fd2);
		cmd2(fds.fd1, command, path, fd);
	}
	return (free_allocs(path, command), pid);
}

pid_t	manager_1(int *fd, t_fd fds, char **env, char **av)
{
	char	*path;
	char	**command;
	pid_t	pid;

	command = cmd_parse(av, 2);
	check_is_path(command);
	if(command == NULL)
		path = NULL;
	else	
		path = path_parse(env, command[0]);
	pid = fork();
	if (pid == -1)
		return (perror("\e[1;41mFirst Fork error\e[0m\n"), free_allocs(path, command), exit(1), -1);
	if (!pid)
	{
		if (fds.fd2 == -1)
		{
			close_fds(fd, fds.fd1);
			free_allocs(path, command);
			exit(1);
		}
		close(fds.fd1);
		cmd1(fds.fd2, command, path, fd);
	}
	return (free_allocs(path, command), pid);
}

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	t_pid	pid;
	t_fd	fds;

	fds = file_manage(av, 1);
	if (ac != 5)
	{
		ft_putstr_fd("\e[1;33mUsage: ./pipex infile cmd1 cmd2 outfile\e[0m\n",
			1);
		return (1);
	}
	if (pipe(fd) == -1)
		return (perror("\e[1;41mPipe error\e[0m\n"), 1);
	pid.pid1 = manager_1(fd, fds, env, av);
	pid.pid2 = manager_2(fd, fds, env, av);
	(close(fd[0]), close(fd[1]), close(fds.fd1), close(fds.fd2));
	waitpid(pid.pid2, NULL, 0);
	waitpid(pid.pid1, NULL, 0);
	return (0);
}
