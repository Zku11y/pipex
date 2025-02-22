/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 05:44:10 by mdakni            #+#    #+#             */
/*   Updated: 2025/02/22 19:13:12 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void cmd1(int fd, char **cmd, char *path, int *fd_pipe)
{
    if (dup2(fd, STDIN_FILENO) == -1 || dup2(fd_pipe[1], STDOUT_FILENO) == -1)
    {
        perror("First Dup Error");
        free_2(cmd);
        free(path);
        exit(EXIT_FAILURE);
    }
    close(fd_pipe[0]);
    close(fd);
    if (execve(path, cmd, NULL) == -1)
    {
        perror("Execve Error");
        free_2(cmd);
        free(path);
        exit(EXIT_FAILURE);
    }
}
void cmd2(int fd, char **cmd, char *path, int *fd_pipe)
{
    if (dup2(fd, STDOUT_FILENO) == -1 || dup2(fd_pipe[0], STDIN_FILENO) == -1)
    {
        perror("Second Dup Error");
        free_2(cmd);
        free(path);
        exit(EXIT_FAILURE);
    }
    close(fd_pipe[1]);
    close(fd);
    if(execve(path, cmd, NULL) == -1)
    {
        perror("Execve Error");
        free_2(cmd);
        free(path);
        exit(EXIT_FAILURE);
    }
}