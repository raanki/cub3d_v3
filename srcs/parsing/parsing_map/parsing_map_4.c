/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:27:53 by ranki             #+#    #+#             */
/*   Updated: 2024/04/06 11:13:21 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

t_map	*ft_fetch_map_params(int fd, t_map *map, char *file, t_game *game)
{
	char	*line;
	int		width;
	int		i;

	i = 0;
	line = "";
	width = -1;
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (line && !ft_is_only_space(line))
		{
			width = ft_is_line_bigger(line, width);
			i++;
		}
		ft_free(line);
		ft_check_max_size(i, width, game);
	}
	close(fd);
	map -> w_map = width - 1;
	map -> h_map = i;
	map = ft_create_map(game, map, file);
	map = ft_test_map(game, map);
	return (map);
}

char	*ft_remove_last_spaces(char *line)
{
	int		index_last_letter;
	int		i;
	char	*ret;
	int		size_line;

	size_line = 0;
	size_line = ft_strlen(line);
	index_last_letter = size_line - 1;
	while ((line[index_last_letter] == ' ' || line[index_last_letter] == '\n')
		&& index_last_letter >= 0)
		index_last_letter--;
	if (index_last_letter < 0)
		return (ft_strdup(line));
	index_last_letter++;
	ret = malloc(2 * size_line - index_last_letter + 1);
	if (!ret)
		return (ft_e_str("malloc"), NULL);
	i = -1;
	while (++i < index_last_letter)
		ret[i] = line[i];
	ret[i] = '\0';
	return (ret);
}

char	*ft_strdup(const char *src)
{
	char	*cpy;
	int		i;

	i = 0;
	if (!src)
		return (NULL);
	cpy = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	ft_check_null(cpy);
	while (src[i] != '\0')
	{
		cpy[i] = src[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
