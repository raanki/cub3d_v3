/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:08:41 by mklimina          #+#    #+#             */
/*   Updated: 2024/03/23 13:45:46 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	check_column_from_top(char **map, int mapHeight, int j)
{
	int	i;
	int	foundonefromtop;

	foundonefromtop = 0;
	i = 0;
	while (i < mapHeight)
	{
		if (map[i][j] == '1')
		{
			foundonefromtop = 1;
			break ;
		}
		if (map[i][j] == '0' && !foundonefromtop)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_column_from_bottom(char **map, int mapHeight, int j)
{
	int	i;
	int	foundonefrombottom;

	foundonefrombottom = 0;
	i = mapHeight - 1;
	while (i >= 0)
	{
		if (map[i][j] == '1')
		{
			foundonefrombottom = 1;
			break ;
		}
		if (map[i][j] == '0' && !foundonefrombottom)
		{
			return (0);
		}
		i--;
	}
	return (1);
}

int	check_line_from_left(char **map, int mapWidth, int i)
{
	int	j;
	int	foundonefromleft;

	foundonefromleft = 0;
	j = 0;
	while (j < mapWidth)
	{
		if (map[i][j] == '1')
		{
			foundonefromleft = 1;
			break ;
		}
		if (map[i][j] == '0' && !foundonefromleft)
		{
			return (0);
		}
		j++;
	}
	return (1);
}

int	check_line_from_right(char **map, int mapWidth, int i)
{
	int	j;
	int	foundonefromright;

	foundonefromright = 0;
	j = mapWidth - 1;
	while (j >= 0)
	{
		if (map[i][j] == '1')
		{
			foundonefromright = 1;
			break ;
		}
		if (map[i][j] == '0' && !foundonefromright)
		{
			return (0);
		}
		j--;
	}
	return (1);
}

void	ft_check_map_trade_with_arg(t_game *game)
{
	if (game->count_valid_color != 2
		&& game->count_valid_texture != 4
		&& (!is_only_space(game->current_line)
			&& !is_line_color(game->current_line)
			&& !is_line_texture(game->current_line)))
	{
		ft_free(game->cur_tmp);
		ft_free(game->current_line);
		ft_e_str("Not Valid file");
		ft_free_game(game);
		exit(EXIT_FAILURE);
	}
}
