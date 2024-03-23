/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:47:13 by ranki             #+#    #+#             */
/*   Updated: 2024/03/23 23:00:24 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	printf("bonus\n");
	if (argc == 2)
	{
		game = ft_game_instance();
		game->arg = ft_strdup(argv[1]);
		if (!game->arg)
			ft_free_game(game);
		ft_init_map(game, argv[1]);
		ft_start_the_game(game);
	}
	return (0);
}
