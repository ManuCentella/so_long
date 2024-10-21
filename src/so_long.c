/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:03:42 by mcentell          #+#    #+#             */
/*   Updated: 2024/10/17 17:58:37 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	is_ber_file(const char *filename)
{
	const char	*ext = strrchr(filename, '.');

	return (ext != NULL && strcmp(ext, ".ber") == 0);
}

void	initialize_game(t_info_map *info, t_game *game, const char *map_file)
{
	init_info_map(info);
	if (get_map_dimensions(map_file, info) == EXIT_FAILURE)
	{
		ft_printf("Error: Failed to get map dimensions.\n");
		exit(EXIT_FAILURE);
	}
	if (read_map(map_file, info) == EXIT_FAILURE)
	{
		ft_printf("Error: Failed to read map.\n");
		exit(EXIT_FAILURE);
	}
	if (validate_map(info) == EXIT_FAILURE)
	{
		free_info_map(info);
		exit(EXIT_FAILURE);
	}
	game->info = *info;
}

void	start_game(t_game *game)
{
	init_mlx(game);
	load_images(game);
	draw_map(game);
	setup_events(game);
	start_game_loop(game);
}

int	main(int argc, char **argv)
{
	t_info_map	info;
	t_game		game;

	if (argc != 2)
	{
		ft_printf("Usage: %s <map_file>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	if (!is_ber_file(argv[1]))
	{
		ft_printf("Error: The file must have a .ber extension.\n");
		return (EXIT_FAILURE);
	}
	initialize_game(&info, &game, argv[1]);
	start_game(&game);
	free_info_map(&info);
	return (EXIT_SUCCESS);
}
