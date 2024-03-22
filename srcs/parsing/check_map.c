/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:49:21 by ranki             #+#    #+#             */
/*   Updated: 2024/03/22 23:49:00 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	ft_replace_2d(char **array, char to_find, char to_replace)
{
	int		i;
	int		j;
	t_game	*game;

	i = 0;
	game = ft_game_instance();
	while (array && i < game->map->h_map && array[i])
	{
		j = 0;
		while (j <= game->map->w_map && array[i][j])
		{
			if (array[i][j] == to_find)
				array[i][j] = to_replace;
			j++;
		}
		i++;
	}
}

void	ft_set_array_flood(t_game *game)
{
	game->dirs[0][0] = 0;
	game->dirs[0][1] = -1;
	game->dirs[1][0] = 0;
	game->dirs[1][1] = 1;
	game->dirs[2][0] = -1;
	game->dirs[2][1] = 0;
	game->dirs[3][0] = 1;
	game->dirs[3][1] = 0;
}
