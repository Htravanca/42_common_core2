/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepereir <hepereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 16:43:52 by hepereir          #+#    #+#             */
/*   Updated: 2024/10/07 20:25:39 by hepereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

// PIPEX AUX
void	ft_free_arr(char **var);
// static char	*ft_find_path(char **options, char *cmd);
char	*ft_path(char **cmdsarr, char **envp);
int		ft_handle_error(int val, const char *msg, int ret_val);
void	ft_split_result(char **cmdsarr);

// PIPEX AUX 2
char	**ft_options(void);
void	ft_wait(int i);

// SPLIT ADAPT
char	**ft_split_adapt(char const *s, char c);
// SPLIT ADAPT
char	*ft_write_arr(char const *s, char c, size_t *pos);

#endif