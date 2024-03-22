/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 09:54:44 by ranki             #+#    #+#             */
/*   Updated: 2024/03/22 16:16:49 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

char	*remove_all_space(char *str)
{
	int		i;
	int		size_str;
	int		size_return;
	char	*ret;
	int		index_new_str;

	size_return = 0;
	index_new_str = 0;
	i = -1;
	size_str = ft_strlen(str);
	if (!size_str)
		return (NULL);
	while (str && str[++i])
		if (str[i] == ' ' || str[i] == '\n')
			size_return++;
	ret = malloc(size_str - size_return + 1);
	if (!ret)
		return (0);
	i = -1;
	while (str && str[++i])
		if (str[i] != ' ' && str[i] != '\n')
			ret[index_new_str++] = str[i];
	ret[index_new_str] = '\0';
	return (ret);
}

char	*get_color_from_valid_line_color(char *line)
{
	char	*color_str;

	color_str = remove_first_spaces_until_first_letter(line + 2);
	return (color_str);
}

int	ft_check_split(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		i++;
	}
	if (i != 2)
		return (0);
	return (1);
}

void	set_rgb_index(t_game *game)
{
	game->split_rgb = ft_split(game->cpy_line, ',');
	free(game->cpy_line);
	game->cpy_line = NULL;
	while (game->split_rgb && game->split_rgb[++(game->i)])
		if (game->i == 0)
			game->r = atoi(game->split_rgb[0]);
	else if (game->i == 1)
		game->g = atoi(game->split_rgb[1]);
	else if (game->i == 2)
		game->b = atoi(game->split_rgb[2]);
	if (game->r < 0 || game->r > 255
		|| game->g < 0 || game->g > 255
		|| game->b < 0 || game->b > 255
		|| ft_check_split(game->split_rgb))
	{
		game->i = -1;
		while (game->split_rgb && game->split_rgb[++game->i])
			free(game->split_rgb[game->i]);
		free(game->split_rgb);
		free(game->current_tmp);
		free(game->current_line);
		ft_free_game(game);
		ft_e_str("not valid line color");
		exit(1);
	}
}

unsigned	int	parse_line_color(t_game *game, char *line)
{
	game->i = -1;
	game->is_ceilling = 0;
	if (!is_line_color(line))
		return (ft_e_str("not valid line color"), 0);
	game->cpy_line = remove_first_spaces_until_first_letter(line);
	if (line && (line[0] == 'C'))
		game->is_ceilling = 1;
	game->cpy_line = get_color_from_valid_line_color(game->cpy_line);
	game->cpy_line = remove_all_space(game->cpy_line);
	set_rgb_index(game);
	game->i = 0;
	while (game->split_rgb && game->split_rgb[game->i])
		free(game->split_rgb[(game->i)++]);
	free(game->split_rgb);
	game->split_rgb = NULL;
	if (game->is_ceilling)
		game->color_ceilling = rgb_to_hex(game->r, game->g, game->b);
	else
		game->color_round = rgb_to_hex(game->r, game->g, game->b);
	return (rgb_to_hex(game->r, game->g, game->b));
}
