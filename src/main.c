/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:08:45 by skully            #+#    #+#             */
/*   Updated: 2025/02/18 06:14:42 by skully           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void child(int *fd, char **env, char **av)
{
    char **paths;

    file_manage(av);
    paths = path_parse(env);
}
void parent(int *fd, char **env, char **av)
{
    printf("\nin the parent process rn\n");
}

int main(int ac, char **av, char **env)
{
    int fd[2];
    pid_t pid;

    if (ac != 5)
        return(printf("./pipex infile cmd1 cmd2 outfile"), 1);
    if (pipe(fd) == -1)
        return(perror("Pipe error"), 1);
    pid = fork();
    if (pid == -1)
        return(perror("Fork error"), 1);
    if (!pid)
    {
        child(fd, env, av);
        exit(1);
    }
    wait(NULL);
    if (access(av[1], F_OK & R_OK) != -1)
        parent(fd, env, av);
    return 0;
}
