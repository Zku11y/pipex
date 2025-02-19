/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 23:03:53 by skully            #+#    #+#             */
/*   Updated: 2025/02/19 00:50:30 by mdakni           ###   ########.fr       */
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

void	check_leaks(void);
void	file_manage(char **av);
char	**cmd_parse(char **av);
char	*path_parse(char **env);
char    **ft_split_ps(char const *s, char c);
size_t  count_word_pss(char const *s, char c);

#endif