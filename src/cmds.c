/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 05:44:10 by mdakni            #+#    #+#             */
/*   Updated: 2025/03/24 04:32:02 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void check_is_path(char **cmd)
{
    int i;
    int start;
    char *str;

    i = 0;
    start = 0;
    if(cmd[0][0] == '/')
    {
        while(cmd[0][i])
        {
            if(cmd[0][i] == '/')
                start = i;
            i++;
        }
        str = ft_substr(cmd[0], start, i - start);
        free(cmd[0]);
        cmd[0] = str;
    }
}
void cmd1(int fd, char **cmd, char *path, int *fd_pipe)
{
    if (dup2(fd, STDIN_FILENO) == -1 || dup2(fd_pipe[1], STDOUT_FILENO) == -1)
    {
        perror("\e[1;41mFirst Dup Error\e[0m");
        exit(EXIT_FAILURE);
    }
    close(fd_pipe[0]);
    close(fd_pipe[1]);
    close(fd);
    dprintf(2 ,"1 => path = %s, cmd 1 = %s, cmd 2 = %s\n", path, cmd[0], cmd[1]);
    if (execve(path, cmd, NULL) == -1)
    {
        perror("\e[1;44mFirst Execve Error\e[0m");
        exit(EXIT_FAILURE);
    }
}

void  cmd2(int fd, char **cmd, char *path, int *fd_pipe)
{
    if (dup2(fd, STDOUT_FILENO) == -1 || dup2(fd_pipe[0], STDIN_FILENO) == -1)
    {
        perror("\e[1;41mSecond Dup Error\e[0m");
        exit(EXIT_FAILURE);
    }
    close(fd_pipe[1]);
    close(fd_pipe[0]);
    close(fd);
    dprintf(2 ,"2 => path = %s, cmd 1 = %s, cmd 2 = %s\n", path, cmd[0], cmd[1]);
    if (execve(path, cmd, NULL) == -1)
    {
        perror("\e[1;44mSecond Execve Error\e[0m");
        exit(EXIT_FAILURE);
    }
}
