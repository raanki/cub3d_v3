/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:14:27 by ranki             #+#    #+#             */
/*   Updated: 2024/03/24 04:02:44 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	int	i;

	i = 0;
	while (src && src[i] && i < (int)n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < (int)n)
	{
		dest[i++] = '\0';
	}
	return (dest);
}

void	ft_copy_line_map(t_game *game, t_map *map)
{
	ft_strncpy(map->map2d[game->i], game->line, ft_strlen(game->line));
	if (game->line)
	{
		ft_free(game->line);
		game->line = NULL;
	}
	game->i++;
}

int	ft_valid_char(char *line)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (1);
	while (line && line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != '\n'
			&& line[i] != 'S' && line[i] != 'W' && line[i] != 'N'
			&& line[i] != 'E' && line[i] != ' ' && line[i] != '\0')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_create_real_map_skip_rest(t_game *game, t_map *map)
{
	ft_check_invalid_char_map(game);
	while (1)
	{
		game->line = get_next_line(game->fd);
		if ((game->line && is_only_space(game->line))
			|| is_line_color(game->line) || is_line_texture(game->line))
		{
			ft_free(game->line);
			game->line = NULL;
			continue ;
		}
		if (!game->line)
		{
			while (game->i < map -> h_map)
			{
				ft_free(map->map2d[game->i]);
				map->map2d[game->i] = NULL;
				game->i++;
			}
			ft_free(map->map2d[game->i]);
			map->map2d[game->i] = NULL;
			break ;
		}
		ft_copy_line_map(game, map);
	}
}

t_map	*create_map(t_game *game, t_map *map, char *file)
{
	game->i = 0;
	game->line = NULL;
	game->fd = open_fd(game, file);
	map->map2d = ft_calloc(map -> h_map + 1, sizeof(char *));
	map->map2d[map -> h_map] = NULL;
	while (game->i < map -> h_map)
	{
		map->map2d[game->i] = ft_calloc(map -> w_map + 1, sizeof(char));
		game->j = -1;
		while (++game->j < map -> w_map)
			map->map2d[game->i][game->j] = ' ';
		game->i++;
	}
	game->i = 0;
	ft_create_real_map_skip_rest(game, map);
	close(game->fd);
	return (map);
}
