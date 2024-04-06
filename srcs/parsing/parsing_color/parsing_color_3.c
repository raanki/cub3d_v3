/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 10:25:25 by ranki             #+#    #+#             */
/*   Updated: 2024/04/06 11:13:28 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

int	ft_index_first_letter(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (i);
		i++;
	}
	return (-1);
}

int	check_all_texture_is_load(void)
{
	t_game	*game;
	int		i;

	game = ft_game_instance();
	i = 0;
	while (i < 4)
	{
		if (game->valid_texture[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_check_max_size(int i, int width, t_game *game)
{
	if (i >= MAX_HEIGHT_MAP || width >= MAX_WIDTH_MAP)
	{
		ft_e_str("Map is too big.");
		ft_free_game(game);
		exit(EXIT_FAILURE);
	}
}
