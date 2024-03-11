/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:47:13 by ranki             #+#    #+#             */
/*   Updated: 2024/03/09 12:15:45 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	parse_line_color(NULL, "SO ./path_to_the_north_texture");
	exit(1);
	t_game	*game;

	(void)argc;
	game = ft_game_instance();
	ft_init_map(game, argv[1]);
    ft_start_the_game(game);
	return (0);
}
