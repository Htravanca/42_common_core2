/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepereir <hepereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:27:04 by hepereir          #+#    #+#             */
/*   Updated: 2024/09/12 16:28:24 by hepereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_update_moves(t_game *game)
{
	char	*move;
	char	*steps;

	steps = ft_itoa(game->steps);
	move = ft_strjoin("Moves: ", steps);
	mlx_string_put(game->mlx.mlx_ptr, game->mlx.win_ptr, 12, 12, 0x052CFA,
		move);
	mlx_string_put(game->mlx.mlx_ptr, game->mlx.win_ptr, 13, 12, 0x052CFA,
		move);
	free(steps);
	free(move);
}
