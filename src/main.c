/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:08:45 by skully            #+#    #+#             */
/*   Updated: 2025/02/23 07:24:38 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void systema()
{
    char cmd[50];
    snprintf(cmd, sizeof(cmd), "leaks %d", getpid());
    system(cmd);
}

void	child(int *fd, char **env, char **av)
{
	char	*path;
	char	**command;
	t_fd fds;

	fds = file_manage(av, 1);
	close(fds.fd1);
	command = cmd_parse(av, 2);
	// printf("\e[1;45mim here!!\e[0m\n");
	path = path_parse(env, command[0]);
	// printf("\n\npath is : %s\n\n", path);
	// printf("the path to the first command is : %s\n", path);
	cmd1(fds.fd2, command, path, fd);
	free(path);
	free_2(command);
	// atexit(systema);
}
void	parent(int *fd, char **env, char **av)
{
	char	*path;
	char	**command;
	t_fd 	fds;

	fds = file_manage(av, 1);
	close(fds.fd2);
	command = cmd_parse(av, 3);
	// printf("\e[1;45mim here!!\e[0m\n");
	path = path_parse(env, command[0]);
	// printf("\n\npath is : %s\n\n", path);
	// printf("the path to the first command is : %s\n", path);
	cmd2(fds.fd1, command, path, fd);
	free(path);
	free_2(command);
	// atexit(systema);
}

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	pid_t	pid;

	check_leaks();
	if (ac != 5)
		return (printf("./pipex infile cmd1 cmd2 outfile"), 1);
	if (pipe(fd) == -1)
		return (perror("Pipe error"), 1);
	pid = fork();
	if (pid == -1)
		return (perror("Fork error"), 1);
	if (!pid)
	{
		systema();
		child(fd, env, av);
		exit(1);
	}
	else
	{
		wait(NULL);
		if (access(av[1], F_OK & R_OK) != -1)
		{
			systema();
			parent(fd, env, av);
		}
	}
	return (0);
}
