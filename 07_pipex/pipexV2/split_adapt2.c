/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_adapt2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepereir <hepereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 14:31:45 by hepereir          #+#    #+#             */
/*   Updated: 2024/10/03 13:20:45 by hepereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_aux_write(char *arr, char *pos_begin, size_t len)
{
	size_t	j;

	j = 0;
	while (j < len)
	{
		arr[j] = pos_begin[j];
		j++;
	}
	arr[j] = '\0';
	return (arr);
}

static size_t	ft_find_quote_len(char *pos_begin, char const *s, size_t *pos)
{
	size_t	len;
	char	*pos_final;

	len = 0;
	pos_begin = (char *)&s[*pos + 1];
	(*pos)++;
	pos_final = (char *)&s[*pos];
	while (s[*pos] != '\'' && s[*pos])
	{
		pos_final = (char *)&s[*pos + 1];
		(*pos)++;
	}
	len = pos_final - pos_begin;
	(*pos)++;
	return (len);
}

static size_t	ft_find_len(char *pos_begin, char const *s, size_t *pos, char c)
{
	size_t	len;
	char	*pos_final;

	len = 0;
	pos_final = (char *)&s[*pos];
	while (s[*pos] != c && s[*pos])
	{
		pos_final = (char *)&s[*pos + 1];
		(*pos)++;
	}
	len = pos_final - pos_begin;
	return (len);
}

char	*ft_write_arr(char const *s, char c, size_t *pos)
{
	char	*pos_begin;
	size_t	len;
	char	*arr;

	len = 0;
	while (s[*pos] == c && s[*pos])
		(*pos)++;
	pos_begin = (char *)&s[*pos];
	if (s[*pos] == '\'' && s[*pos])
	{
		pos_begin = (char *)&s[*pos + 1];
		len = ft_find_quote_len(pos_begin, s, pos);
	}
	else
		len = ft_find_len(pos_begin, s, pos, c);
	arr = (char *)malloc(len + 1);
	if (!arr)
		return (NULL);
	arr = ft_aux_write(arr, pos_begin, len);
	return (arr);
}

char	**ft_options(void)
{
	char	**options;

	options = (char **)malloc(3 * sizeof(char *));
	if (!options)
		exit(1);
	options[0] = ft_strdup("/usr/bin");
	options[1] = ft_strdup("/bin");
	options[2] = NULL;
	return (options);
}
