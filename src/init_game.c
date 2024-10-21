/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:12:26 by mcentell          #+#    #+#             */
/*   Updated: 2024/10/17 13:19:04 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_info_map(t_info_map *info)
{
	info->width = 0;
	info->height = 0;
	info->map = NULL;
	info->player_x = 0;
	info->player_y = 0;
	info->num_cols = 0;
	info->exit_x = 0;
	info->exit_y = 0;
	info->exit_open = 0;
}

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (game->mlx == NULL)
	{
		ft_printf("Error initializing MLX\n");
		free_info_map(&game->info);
		exit(EXIT_FAILURE);
	}
	game->win = mlx_new_window(game->mlx, game->info.width * TILE_SIZE,
			game->info.height * TILE_SIZE, "so_long");
	if (game->win == NULL)
	{
		ft_printf("Error creating window\n");
		free(game->mlx);
		free_info_map(&game->info);
		exit(EXIT_FAILURE);
	}
}

void	setup_events(t_game *game)
{
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_key_hook(game->win, handle_keypress, game);
}

int	is_valid_path(t_info_map *info, int start_x, int start_y)
{
	bool	**visited;

	visited = allocate_visited(info->height, info->width);
	initialize_visited(visited, info->height, info->width);
	flood_fill(info, start_x, start_y, visited);
	if (!check_path(info, visited))
	{
		free_visited(visited, info->height);
		return (0);
	}
	free_visited(visited, info->height);
	return (1);
}
