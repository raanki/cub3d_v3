/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:07:24 by ranki             #+#    #+#             */
/*   Updated: 2024/03/22 20:34:09 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

void	ft_set_up_all(t_game *game)
{
	game->line = get_next_line(game->fd);
	if (game->save)
	{
		free(game->save);
		game->save = NULL;
	}
	if (game->line)
		game->save = ft_strdup(game->line);
	else
		game->save = NULL;
}

void	ft_check_up_all(t_game *game)
{
	if (game->line && !ft_valid_char(game->save))
	{
		if (game->save)
			free(game->save);
		free(game->line);
		ft_e_str("Invalid char");
		close(game->fd);
		ft_free_game(game);
		exit(EXIT_FAILURE);
	}
	free(game->line);
	if (game->save)
	{
		free(game->save);
		game->save = NULL;
	}
}

void	ft_check_invalid_char_map(t_game *game)
{
	game->save = NULL;
	game->now_is_map = 0;
	while (1)
	{
		ft_set_up_all(game);
		if (game->line && ((is_only_space(game->line) && !game->now_is_map )
				|| is_line_color(game->line) || is_line_texture(game->line)))
		{
			free(game->line);
			if (game->save)
			{
				free(game->save);
				game->save = NULL;
			}
			continue ;
		}
		game->now_is_map = 1;
		if (!game->line)
		{
			break ;
		}
		if (game->now_is_map == 1 && is_only_space(game->line))
		{
			if (game->save)
				free(game->save);
			free(game->line);
			ft_e_str("Not valid Map");
			close(game->fd);
			ft_free_game(game);
			exit(EXIT_FAILURE);
		}
		ft_check_up_all(game);
	}
	close(game->fd);
	game->fd = open_fd(game, game->arg);
}
