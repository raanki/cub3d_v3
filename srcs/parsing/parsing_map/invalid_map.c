/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:07:24 by ranki             #+#    #+#             */
/*   Updated: 2024/04/06 13:27:39 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

void	ft_set_up_all(t_game *game)
{
	game->line = get_next_line(game->fd);
	if (game->save)
	{
		ft_free(game->save);
		game->save = NULL;
	}
	if (game->line)
		game->save = ft_check_null(ft_strdup(game->line));
	else
		game->save = NULL;
}

void	ft_check_up_all(t_game *game)
{
	if (game->line && !ft_valid_char(game->save))
	{
		if (game->save)
			ft_free(game->save);
		ft_free(game->line);
		ft_e_str("Invalid char");
		close(game->fd);
		ft_free_game(game);
		exit(EXIT_FAILURE);
	}
	ft_free(game->line);
	if (game->save)
	{
		ft_free(game->save);
		game->save = NULL;
	}
}

int	ft_check_last_line(t_game *game)
{
	while (game->line != NULL)
	{
		if (!ft_is_only_space(game->line))
			return (0);
		free(game->line);
		game->line = get_next_line(game->fd);
	}
	return (1);
}

void	ft_check_island(t_game *game)
{
	if (game->now_is_map == 1 && (ft_is_only_space(game->line)
			|| !ft_valid_char(game->line)) && !ft_check_last_line(game))
	{
		if (game->save)
			ft_free(game->save);
		ft_free(game->line);
		ft_e_str("Not valid Map");
		close(game->fd);
		ft_free_game(game);
		exit(EXIT_FAILURE);
	}
	ft_check_up_all(game);
}

void	ft_check_invalid_char_map(t_game *g)
{
	g->save = NULL;
	g->now_is_map = 0;
	while (1)
	{
		ft_set_up_all(g);
		if (g->line && ((ft_is_only_space(g->line) && !g->now_is_map)
				|| ft_is_line_color(g->line) || ft_is_line_texture(g->line)))
		{
			ft_free(g->line);
			if (g->save)
			{
				ft_free(g->save);
				g->save = NULL;
			}
			continue ;
		}
		g->now_is_map = 1;
		if (!g->line)
		{
			break ;
		}
		ft_check_island(g);
	}
	close(g->fd);
	g->fd = ft_open_fd(g, g->arg);
}
