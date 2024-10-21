/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:04:47 by mcentell          #+#    #+#             */
/*   Updated: 2024/10/16 19:11:18 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	set_initial_player_position(t_info_map *info)
{
	int	y;
	int	x;

	y = 0;
	while (y < info->height)
	{
		x = 0;
		while (x < info->width)
		{
			if (info->map[y][x] == 'P')
			{
				info->player_x = x;
				info->player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	move_player(t_game *game, int new_x, int new_y)
{
	static int	move_count = -1;

	move_count++;
	ft_printf("Número de movimientos: %d\n", move_count);
	handle_collectible(game, new_x, new_y);
	handle_exit(game, new_x, new_y);
	update_player_position(game, new_x, new_y);
}

void	init_game(t_info_map *info)
{
	init_info_map(info);
}

bool	is_valid_new_position(int new_x, int new_y, t_game *game)
{
	return (is_valid_move(new_x, new_y, game) && (new_x != game->info.player_x
			|| new_y != game->info.player_y));
}
