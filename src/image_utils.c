/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:38:16 by mcentell          #+#    #+#             */
/*   Updated: 2024/10/21 15:01:02 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	verify_image_size(int width, int height)
{
	if (width != TILE_SIZE || height != TILE_SIZE)
	{
		ft_printf("Error: Las imágenes deben tener el tamaño de TILE_SIZE\n");
		exit(EXIT_FAILURE);
	}
}

void	load_images(t_game *game)
{
	int	img_width;
	int	img_height;

	game->img_wall = load_image(game->mlx, "images/wall.xpm", &img_width,
			&img_height);
	verify_image_size(img_width, img_height);
	game->img_empty = load_image(game->mlx, "images/empty.xpm", &img_width,
			&img_height);
	verify_image_size(img_width, img_height);
	game->img_player = load_image(game->mlx, "images/player1.xpm", &img_width,
			&img_height);
	verify_image_size(img_width, img_height);
	game->img_playerleft = load_image(game->mlx, "images/player1left.xpm",
			&img_width, &img_height);
	verify_image_size(img_width, img_height);
	game->img_collectible = load_image(game->mlx, "images/collectible.xpm",
			&img_width, &img_height);
	verify_image_size(img_width, img_height);
	game->img_exit = load_image(game->mlx, "images/exit.xpm", &img_width,
			&img_height);
	verify_image_size(img_width, img_height);
	game->img_player_original = game->img_player;
}

int	has_valid_elements(int player_count, int exit_count, int collectible_count)
{
	if (player_count != 1)
	{
		ft_printf("Error: Tiene que haber una posicion\n");
		return (EXIT_FAILURE);
	}
	if (exit_count != 1)
	{
		ft_printf("Error: El mapa debe tener una salida\n");
		return (EXIT_FAILURE);
	}
	if (collectible_count < 1)
	{
		ft_printf("Error: El mapa debe tener al menos un coleccionable\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	count_map_elements(t_info_map *info, int *player_count, int *exit_count,
		int *collectible_count)
{
	int	y;
	int	x;

	y = 0;
	while (y < info->height)
	{
		x = 0;
		while (x < info->width)
		{
			if (process_tile(info->map[y][x], player_count, exit_count,
				collectible_count) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			x++;
		}
		y++;
	}
	return (EXIT_SUCCESS);
}

void	*load_image(void *mlx, const char *file_path, int *width, int *height)
{
	void	*img;

	img = mlx_xpm_file_to_image(mlx, (char *)file_path, width, height);
	if (!img)
	{
		ft_printf("Error al cargar %s\n", file_path);
		exit(EXIT_FAILURE);
	}
	return (img);
}
