/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_aux_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepereir <hepereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 16:43:47 by hepereir          #+#    #+#             */
/*   Updated: 2024/09/19 18:34:07 by hepereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(char **var)
{
	int	i;

	i = 0;
	if (!var || !*var)
		return ;
	while (var[i] != NULL)
	{
		free(var[i]);
		i++;
	}
	free(var);
}

static char	*ft_find_path(char **options, char *cmd)
{
	int		i;
	char	*temp;
	char	*temp2;
	char	*pfinal;

	i = 0;
	pfinal = NULL;
	while (options[i])
	{
		temp = ft_strjoin(options[i], "/");
		temp2 = ft_strjoin(temp, cmd);
		free(temp);
		if (access(temp2, F_OK) == 0)
		{
			pfinal = ft_strdup(temp2);
			free(temp2);
			break ;
		}
		free(temp2);
		i++;
	}
	return (pfinal);
}

char	*ft_path(char **cmdsarr, char **envp)
{
	char	**options;
	char	*pfinal;
	int		i;

	i = 0;
	pfinal = NULL;
	while (!ft_strnstr(envp[i], "PATH", 4))// procura nos sistem variables a variavel PATH
		i++;
	options = ft_split(envp[i] + 5, ':');// separa os paths possvies onde pode existir o cmd
	if (!options)
		return (NULL);
	pfinal = ft_find_path(options, cmdsarr[0]); // tirar o "-l" do "ls -l"
	ft_free(options);
	return (pfinal);
}

void	ft_split_result(char **cmdsarr)
{
	if (!cmdsarr || !cmdsarr[0])
	{
		perror("Error while spliting the comands");
		exit(1);
	}
}