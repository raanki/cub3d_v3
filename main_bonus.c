/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:47:13 by ranki             #+#    #+#             */
/*   Updated: 2024/03/24 04:09:10 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc == 2)
	{
		game = ft_game_instance();
		game->is_bonus = 1;
		game->arg = ft_strdup(argv[1]);
		if (!game->arg)
			ft_free_game(game);
		ft_init_map(game, argv[1]);
		ft_start_the_game(game);
	}
	return (0);
}
