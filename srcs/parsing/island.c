/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   island.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:01:42 by ranki             #+#    #+#             */
/*   Updated: 2024/03/23 16:05:01 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	ft_check_read(char *stash, char *buffer, int fd, int ret)
{
	t_game	*game;

	game = ft_game_instance();
	if (ret == -1)
	{
		ft_free_game(game);
		ft_e_str("read crash");
		exit(EXIT_FAILURE);
	}
}

int	is_line_color(char *line)
{
	char	*cpy_line;

	if (!line || line[0] == '\0')
		return (0);
	if (!ft_str_have_three_coma(line) || !is_only_c_f_number(line))
		return (0);
	cpy_line = remove_first_spaces_until_first_letter(line);
	if (!ft_strncmp(cpy_line, "F ", 2)
		|| !ft_strncmp(cpy_line, "C ", 2))
	{
		ft_free(cpy_line);
		return (1);
	}
	ft_free(cpy_line);
	return (0);
}

char	*get_type_texture_from_valid_line_color(char *line)
{
	char	*ret;

	ret = malloc(2 + 1);
	ft_check_null(ret);
	ret[0] = line[0];
	ret[1] = line[1];
	ret[2] = '\0';
	ft_free(line);
	return (ret);
}

unsigned	int	rgb_to_hex(int r, int g, int b)
{
	unsigned int	hex;

	hex = (r << 16) + (g << 8) + b;
	return (hex);
}
