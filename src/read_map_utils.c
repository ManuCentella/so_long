/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:29:43 by mcentell          #+#    #+#             */
/*   Updated: 2024/10/17 18:05:48 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_info_map(t_info_map *info)
{
	int	i;

	if (info == NULL || info->map == NULL)
		return ;
	i = 0;
	while (i < info->height)
	{
		if (info->map[i] != NULL)
			free(info->map[i]);
		i++;
	}
	free(info->map);
	info->map = NULL;
}

void	update_map_dimensions(char *line, int *width, int *height)
{
	if (line == NULL || width == NULL || height == NULL)
		return ;
	if (*width == 0)
		*width = ft_strlen(line);
	(*height)++;
}

int	open_file(const char *filename)
{
	int	fd;

	if (filename == NULL)
	{
		perror("Error: filename is NULL");
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		perror("Error opening map file");
	return (fd);
}

int	allocate_map_memory(t_info_map *info)
{
	if (info == NULL)
	{
		ft_printf("Error: info is NULL\n");
		return (EXIT_FAILURE);
	}
	info->map = malloc(info->height * sizeof(char *));
	if (!info->map)
	{
		ft_printf("Error: No se pudo asignar memoria para el mapa\n");
		return (EXIT_FAILURE);
	}
	info->num_cols = 0;
	return (EXIT_SUCCESS);
}

void	count_collectibles(t_info_map *info, int i)
{
	int	j;

	if (info == NULL || info->map == NULL || i < 0 || i >= info->height)
		return ;
	if (info->map[i] == NULL)
		return ;
	j = 0;
	while (j < info->width)
	{
		if (info->map[i][j] == '\0')
			break ;
		if (info->map[i][j] == 'C')
			info->num_cols++;
		else if (info->map[i][j] == 'E')
		{
			info->exit_x = j;
			info->exit_y = i;
		}
		else if (info->map[i][j] == 'P')
		{
			info->player_x = j;
			info->player_y = i;
		}
		j++;
	}
}
