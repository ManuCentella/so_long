/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 21:22:45 by mcentell          #+#    #+#             */
/*   Updated: 2024/10/21 14:40:29 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	validate_map(t_info_map *info)
{
	int	player_count;
	int	exit_count;
	int	collectible_count;

	player_count = 0;
	exit_count = 0;
	collectible_count = 0;
	if (is_rectangular(info) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (is_surrounded_by_walls(info) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (count_map_elements(info, &player_count, &exit_count,
			&collectible_count) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (has_valid_elements(player_count, exit_count,
			collectible_count) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (!is_valid_path(info, info->player_x, info->player_y))
	{
		ft_printf("Error: No hay un camino válido\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	is_rectangular(t_info_map *info)
{
	int	y;

	if (!info || !info->map || info->width <= 0 || info->height <= 0)
	{
		ft_printf("Error: Información del mapa no válida\n");
		return (EXIT_FAILURE);
	}
	y = 0;
	while (y < info->height)
	{
		if (!info->map[y] || (int)strlen(info->map[y]) != info->width)
		{
			ft_printf("Error: El mapa no es rectangular\n");
			return (EXIT_FAILURE);
		}
		y++;
	}
	return (EXIT_SUCCESS);
}

int	is_surrounded_by_walls(t_info_map *info)
{
	if (info == NULL || info->map == NULL)
	{
		ft_printf("Error: Información del mapa no válida\n");
		return (EXIT_FAILURE);
	}
	if (!check_horizontal_walls(info) || !check_vertical_walls(info))
	{
		ft_printf("Error: El mapa no está cerrado/rodeado de muros\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	check_horizontal_walls(t_info_map *info)
{
	int	x;

	if (info == NULL || info->map == NULL)
	{
		ft_printf("Error: Información del mapa no válida\n");
		return (0);
	}
	x = 0;
	while (x < info->width)
	{
		if (info->map[0] == NULL || info->map[info->height - 1] == NULL)
		{
			ft_printf("Error: Fila del mapa no válida\n");
			return (0);
		}
		if (info->map[0][x] != '1' || info->map[info->height - 1][x] != '1')
			return (0);
		x++;
	}
	return (1);
}

int	check_vertical_walls(t_info_map *info)
{
	int	y;

	if (info == NULL || info->map == NULL)
	{
		ft_printf("Error: Información del mapa no válida\n");
		return (0);
	}
	y = 0;
	while (y < info->height)
	{
		if (info->map[y] == NULL)
		{
			ft_printf("Error: Fila del mapa no válida\n");
			return (0);
		}
		if (info->map[y][0] != '1' || info->map[y][info->width - 1] != '1')
			return (0);
		y++;
	}
	return (1);
}
