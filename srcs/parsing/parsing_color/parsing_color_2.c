/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:34:29 by ranki             #+#    #+#             */
/*   Updated: 2024/03/23 15:17:21 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

void	ft_free(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	*ft_check_null(void *ptr)
{
	t_game *game;

	game = ft_game_instance();
	if (ptr == NULL)
	{
		ft_e_str("ptr is null");
		ft_free_game(game);
		exit(EXIT_FAILURE);
	}

	return (ptr);
}

char	*remove_first_spaces_until_first_letter(char *line)
{
	int		index_last_space;
	char	*ret;
	t_game	*game;

	game = ft_game_instance();
	index_last_space = 0;
	game->index_spaces = 0;
	if (!line)
		return NULL;
	while (line[index_last_space] == ' ')
		index_last_space++;
	game->index_spaces = index_last_space;
	if (index_last_space == 0)
		return (ft_check_null(ft_strdup(line)));
	ret = ft_strdup(line + index_last_space);
	ft_check_null(ret);
	return (ret);
}

int	ft_str_have_three_coma(char *string)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (string && string[i])
	{
		if (string[i] == ',' && string[i + 1] != ',')
			count++;
		i++;
	}
	if (count == 2)
		return (1);
	return (0);
}

int	is_only_c_f_number(char *line)
{
	int	i;

	i = 0;
	while(line && line[i])
	{
		if (line[i] != 'F' && line[i] != 'C' && line[i] != ' '
			&& line[i] != '\t' && line[i] != ',' && line[i] != '\n'
			&& !(line[i] >= '0' && line[i] <= '9'))
			{
				return (0);
			}
			
		i++;
	}
	return (1);
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
