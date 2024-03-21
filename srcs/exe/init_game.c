/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:57:02 by ranki             #+#    #+#             */
/*   Updated: 2024/03/21 21:49:00 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"


void	set_start_angle_player(t_game *game)
{
	if (game->angle_player == 0) // EAST
	{
		game->player->dir_x = 0;
		game->player->dir_y = -1;
		game->player->plan_x = FOV;
		game->player->plan_y = 0;
	}
	else if (game->angle_player == 1) // SUD
	{
		game->player->dir_x = 1;
		game->player->dir_y = 0;
		game->player->plan_x = 0;
		game->player->plan_y = FOV;
	}
	else if (game->angle_player == 2) // WEST
	{
		game->player->dir_x = 0;
		game->player->dir_y = 1;
		game->player->plan_x = -FOV;
		game->player->plan_y = 0;
	}
	else if (game->angle_player == 3) // NORD
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

	char *tmp;

	game->sprite_path = ft_calloc(5, sizeof(char *));
	if (!game->sprite_path)
	{
		ft_free_game(game);
		exit(EXIT_FAILURE);
	}
	game->sprite_path[0] = NULL;
	game->sprite_path[1] = NULL;
	game->sprite_path[2] = NULL;
	game->sprite_path[3] = NULL;

	int fd = open_fd(game, arg);
	char *line = "";
	int	index_sprite_path = 0;
	int	count_valid_information = 0;

    while (line != NULL && count_valid_information < 6)
    {
        line = get_next_line(fd);
		if (!line)
			break ;
		tmp = ft_strdup(line);
		if (is_line_texture(line))
		{
			game->sprite_path[index_sprite_path] = parse_line_texture(game, tmp);
			count_valid_information++;
			index_sprite_path++;
		}
		else if (is_line_color(line))
		{
			
			parse_line_color(game, tmp);
			count_valid_information++;
		}
        
		free(tmp);
        free(line);
    }

	game->sprite_path[4] = NULL;
	
	if (count_valid_information != 6)
	{
		ft_free_game(game);
		printf("lack informations (texture or color)\n");
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
