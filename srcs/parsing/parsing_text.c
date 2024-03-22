/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_text.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 09:55:01 by ranki             #+#    #+#             */
/*   Updated: 2024/03/22 14:47:52 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] && s2[i]) && (s1[i] == s2[i]) && i < n)
	{
		i++;
	}
	if (i >= n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	is_line_texture(char *line)
{
	char	*cpy_line;
	t_game	*game;

	game = ft_game_instance();
	if (!(line && line[0] != '\0'))
		return (0);
	cpy_line = remove_first_spaces_until_first_letter(line);
	if (cpy_line && ft_strlen(cpy_line) >= 3)
	{
		if (!ft_strncmp(cpy_line, "NO ", 3))
			return (game->current_sprite = 0, 1);
		else if (!ft_strncmp(cpy_line, "SO ", 3))
			return (game->current_sprite = 1, 1);
		else if (!ft_strncmp(cpy_line, "WE ", 3))
			return (game->current_sprite = 3, 1);
		else if (!ft_strncmp(cpy_line, "EA ", 3))
			return (game->current_sprite = 2, 1);
	}
	return (0);
}

int	is_only_space(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
	{
		return (0);
	}
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != '\n' && str[i] != '\t')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

char	*get_path_from_valid_line_texture(char *line)
{
	char	*path_line;

	path_line = remove_first_spaces_until_first_letter(line + 3);
	return (path_line);
}

char	*parse_line_texture(char *line)
{
	char	*cpy_line;

	if (!is_line_texture(line))
	{
		ft_e_str("not valid line color");
		return (NULL);
	}
	cpy_line = remove_first_spaces_until_first_letter(line);
	cpy_line = get_path_from_valid_line_texture(cpy_line);
	cpy_line = remove_last_spaces(cpy_line);
	return (cpy_line);
}
