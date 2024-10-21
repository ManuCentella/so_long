/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:22:03 by mcentell          #+#    #+#             */
/*   Updated: 2024/10/16 19:08:57 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/inc/ft_printf.h"
#include "so_long.h"

void	update_player_position(t_game *game, int new_x, int new_y)
{
	draw_tile(game, game->info.player_x, game->info.player_y, '0');
	game->info.map[game->info.player_y][game->info.player_x] = '0';
	game->info.map[new_y][new_x] = 'P';
	game->info.player_x = new_x;
	game->info.player_y = new_y;
	draw_tile(game, new_x, new_y, 'P');
}

void	handle_collectible(t_game *game, int new_x, int new_y)
{
	if (game->info.map[new_y][new_x] == 'C')
	{
		game->info.num_cols--;
		ft_printf("Coleccionables restantes: %d\n", game->info.num_cols);
		if (game->info.num_cols == 0)
		{
			ft_printf("coleccionables recogidos! Ahora puedes salir.\n");
			game->info.exit_open = 1;
			draw_tile(game, game->info.exit_x, game->info.exit_y, 'E');
		}
	}
}

void	handle_exit(t_game *game, int new_x, int new_y)
{
	if (is_exit_position(new_x, new_y, game))
	{
		ft_printf("Felicidades! Has completado el nivel.\n");
		exit(0);
	}
}

bool	is_exit_position(int new_x, int new_y, t_game *game)
{
	return (game->info.exit_x == new_x && game->info.exit_y == new_y
		&& game->info.exit_open);
}
