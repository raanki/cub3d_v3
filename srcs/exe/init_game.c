/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:57:02 by ranki             #+#    #+#             */
/*   Updated: 2024/03/22 13:01:03 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/**
 * EAST
 * SUD
 * WEST
 * NORD
*/
void	set_start_angle_player(t_game *game)
{
	game->player->plan_x = FOV;
	game->player->dir_x = 0;
	game->player->plan_y = 0;
	game->player->dir_y = -1;
	if (game->angle_player == 1)
	{
		game->player->dir_x = 1;
		game->player->dir_y = 0;
		game->player->plan_x = 0;
	}
	else if (game->angle_player == 2)
	{
		game->player->dir_y = 1;
		game->player->plan_x = -FOV;
	}
	else if (game->angle_player == 3)
	{
		game->player->dir_x = -1;
		game->player->dir_y = 0;
		game->player->plan_x = 0;
		game->player->plan_y = -FOV;
	}
}

void	ft_init_map(t_game *game, char *arg)
{
	t_player	*player;

	game->map = malloc(sizeof(t_map));
	if (!game->map)
	{
		ft_free_game(game);
		exit(EXIT_FAILURE);
	}
	game->map->map2d = NULL;
	game->player = malloc(sizeof(t_player));
	if (game->player  == NULL)
	{
		ft_free_game(game);
		exit(EXIT_FAILURE);
	}

//*************************************************************************************************************
    // here do the color / player / texture parsing

	game->sprite_path = ft_calloc(5, sizeof(char *));
	if (!game->sprite_path)
	{
		ft_free_game(game);
		exit(EXIT_FAILURE);
	}
	game->sprite_path[0] = ft_strdup("nothing but essential");
	game->sprite_path[1] = ft_strdup("nothing but essential");
	game->sprite_path[2] = ft_strdup("nothing but essential");
	game->sprite_path[3] = ft_strdup("nothing but essential");

	int fd = open_fd(game, arg);
	int	index_sprite_path = 0;
	game->current_sprite = 0;
	int	count_valid_texture = 0;
	int	count_valid_color = 0;
	int first = 1;

    while ((game->current_line != NULL && (count_valid_texture < 4 || count_valid_color < 2)) || first)
    {
		first = 0;
        game->current_line= get_next_line(fd);
		if (!game->current_line)
			break ;
		game->current_tmp = ft_strdup(game->current_line);
		if (is_line_texture(game->current_line))
		{
			if (game->sprite_path[game->current_sprite])
				free(game->sprite_path[game->current_sprite]);
			game->sprite_path[game->current_sprite] = parse_line_texture(game, game->current_tmp);
			count_valid_texture++;
			index_sprite_path++;
		}
		else if (is_line_color(game->current_line))
		{
			parse_line_color(game, game->current_tmp);
			count_valid_color++;
		}
		free(game->current_tmp);
        free(game->current_line);
    }
	game->sprite_path[4] = NULL;
	
	if (count_valid_texture != 4)
	{
		ft_free_game(game);
		printf("You have to put 4 valid textures\n");
		exit(EXIT_FAILURE);
	}

	if (count_valid_color != 2)
	{
		ft_free_game(game);
		printf("You have to put 2 valid colors\n");
		exit(EXIT_FAILURE);
	}
	
// end parse color / player / texture 
//*************************************************************************************************************


	game->map = fetch_map_params(fd, game->map , arg, game);

	if (!game->map->map2d)
	{
		ft_free_game(game);
		exit(EXIT_FAILURE);
	}
	
	set_start_angle_player(game);
	game->map = game->map;
	game->delta_dist_x = 0;
	game->delta_dist_y = 0;

}

void	ft_start_the_game(t_game *game)
{
	t_mlx	*mlx;

	mlx = ft_calloc(1, sizeof(t_mlx));
	if (!mlx)
		exit(EXIT_FAILURE);
	game->mlx = mlx;
	game->mlx->mlx_p = mlx_init();
	if (!game->mlx->mlx_p)
	{
		exit (EXIT_FAILURE);
	}
	mlx->win_p = mlx_new_window(mlx->mlx_p, SCREEN_WIDTH,
			SCREEN_HEIGHT, "Cub3D");
	mlx->img = mlx_new_image(mlx->mlx_p, SCREEN_WIDTH, SCREEN_HEIGHT);
	ft_load_sprite(game);
	mlx_loop_hook(mlx->mlx_p, &ft_game_loop, game);
	mlx_hook(game->mlx->win_p, KeyRelease, KeyReleaseMask, &ft_reles, game);
	mlx_hook(mlx->win_p, KeyPress, KeyPressMask, ft_mlx_key, game);
	mlx_hook(mlx->win_p, 33, 1L << 17, ft_exit, game);
	mlx_loop(mlx->mlx_p);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (i < n)
	{
		*(char *)(s + i) = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count);
	return (ptr);
}
