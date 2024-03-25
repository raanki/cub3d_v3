/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:47:13 by ranki             #+#    #+#             */
/*   Updated: 2024/03/25 23:09:07 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_end_file(char *str)
{
	int	size_str;

	if (!str)
		return (0);
	size_str = ft_strlen(str);
	if (size_str < 5)
		return (0);
	size_str--;
	while (size_str >= 0 && str[size_str] != '.')
	{
		size_str--;
	}
	if (size_str == 0)
		return (0);
	if (!ft_strncmp(str + size_str, ".cub", 4))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc == 2)
	{
		if (!ft_check_end_file(argv[1]))
		{
			ft_e_str("File is not good");
			exit(EXIT_FAILURE);
		}
		game = ft_game_instance();
		game->is_bonus = 0;
		game->arg = ft_strdup(argv[1]);
		if (!game->arg)
			ft_free_game(game);
		ft_init_map(game, argv[1]);
		ft_start_the_game(game);
	}
	return (0);
}
