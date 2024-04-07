/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:34:29 by ranki             #+#    #+#             */
/*   Updated: 2024/04/07 19:15:55 by ranki            ###   ########.fr       */
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
	t_game	*game;

	game = ft_game_instance();
	if (ptr == NULL)
	{
		ft_e_str("ptr is null");
		ft_free_game(game);
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

char	*ft_remove_first_spaces_until_first_letter(char *line)
{
	int		index_last_space;
	char	*ret;
	t_game	*game;

	game = ft_game_instance();
	index_last_space = 0;
	game->index_spaces = 0;
	if (!line)
		return (NULL);
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
	int	count_not_zero;

	i = 0;
	count = 0;
	count_not_zero = 0;
	while (string && string[i])
	{
		if (string[i] == ',')
			count++;
		if (string[i] == ',' && string[i + 1] != ',')
			count_not_zero++;
		i++;
	}
	if (count == 2 && count_not_zero != 2)
		return (1);
	return (0);
}

int	ft_is_only_c_f_number(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
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
