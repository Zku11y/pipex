/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 00:31:58 by skully            #+#    #+#             */
/*   Updated: 2025/02/18 06:18:22 by skully           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void file_manage(char **av)
{
    int outfile;

    outfile = open("outfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outfile == -1)
    {
        perror("Fd Error");
        exit(1);
    }
    if (access(av[1], F_OK & R_OK) == -1)
    {
        close(outfile);
        perror("Infile Error");
        exit(1);
    }
}
char **path_parse(char **env)
{
    int i = 0;
    int j = 0;
    char *str;
    str = NULL;
    while(env[i] && !str)
    {
        str = ft_strnstr(env[i], "PATH", sizeof(env[i]));
        if(str)
            {
                printf("\e[1;32m Path Found! : \n\e[0m\e[1;33m%s\e[0m", env[i]);
                break;
            }
        i++;
    }


    return (NULL);
}
