/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 23:03:53 by skully            #+#    #+#             */
/*   Updated: 2025/03/24 13:11:46 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "includes/libft/libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>

typedef struct fd_struct
{
    int fd1;
    int fd2;
}       t_fd;

typedef struct fd_pid
{
    pid_t pid1;
    pid_t pid2;
}       t_pid;

void    systema();
void    free_2(char **str);
void	check_leaks(void);
t_fd	file_manage(char **av, int i);
char	**cmd_parse(char **av, int index);
char	*path_parse(char **env, char *cmd);
void    check_is_path(char **cmd);
char    **ft_split_ps(char const *s, char c);
size_t  count_word_pss(char const *s, char c);
void    cmd1(int fd, char **cmd, char *path, int *fd_pipe);
void    cmd2(int fd, char **cmd, char *path, int *fd_pipe);

#endif