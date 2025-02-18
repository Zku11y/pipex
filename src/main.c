/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:08:45 by skully            #+#    #+#             */
/*   Updated: 2025/02/18 18:29:07 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	child(int *fd, char **env, char **av)
{
	char	*path;
	char	**command;

	file_manage(av);
	path = path_parse(env);
	printf("the path to the first command is : %s\n", path);
	command = cmd_parse(av);
}
void	parent(int *fd, char **env, char **av)
{
	printf("\nin the parent process rn\n");
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
		child(fd, env, av);
		exit(1);
	}
	wait(NULL);
	if (access(av[1], F_OK & R_OK) != -1)
		parent(fd, env, av);
	return (0);
}
