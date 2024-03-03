/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:47:26 by ranki             #+#    #+#             */
/*   Updated: 2024/03/03 14:35:53 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//****************************************************************
//****************************************************************
//******************************* INCLUDES ***********************
//****************************************************************
//****************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>
#include "./minilibx-linux/mlx.h"
#include "./minilibx-linux/mlx_int.h"

//****************************************************************
//****************************************************************
//******************************** DEFINES ***********************
//****************************************************************
//****************************************************************

#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define SCREEN_WIDTH 640 
#define SCREEN_HEIGHT 480
#define COLOR_CEILLING 0x00FF00
#define COLOR_FLOOR 0x0000FF
#define M_PI 3.14159265358979323846 
#define TILE_SIZE 64
#define SPRITE_WEST "sprites/sky-blue.xpm"
#define SPRITE_EAST "sprites/dark.xpm"
#define SPRITE_NORTH "sprites/brown.xpm"
#define SPRITE_SOUTH "sprites/grey.xpm"

//*****************************************************************
//*****************************************************************
//******************************* STUCTURES ***********************
//*****************************************************************
//*****************************************************************

typedef struct s_map
{
	char	**map2d;
	int		w_map;
	int		h_map;
	double	time;
	double	old_time;
}	t_map;

typedef struct s_player
{
	double		plyr_x;
	double		plyr_y;
	double		dir_x;
	double		dir_y;
	double		plan_x;
	double		plan_y;
}	t_player;

typedef struct s_mlx
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	void	*mlx_p;
	void	*win_p;
	int		endian;
}	t_mlx;

typedef struct s_sprite
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	int		*pixel_colors;
}	t_sprite;

typedef struct s_game
{
	t_map		*map;
	t_player	*player;
	t_mlx		*mlx;
	t_sprite	**sprite;
	int			buffer[SCREEN_HEIGHT + 1][SCREEN_WIDTH + 1];
	double		camera_x;
	double		camera_y;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_player_x;
	int			map_player_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	double		wall_x;
	int			pitch;
	int			step_x;
	int			step_y;
	int			side;
	int			line_height;
	int			hit;
	int			draw_start;
	int			draw_end;
	int			tex_num;
	int			tex_x;
	int			tex_y;
	double		step;
	double		tex_pos;
	int			color;
	int			color_ceilling;
	int			color_floor;
}	t_game;

//************************************************************
//************************************************************
//**************************** FUNCTIONS *********************
//************************************************************
//************************************************************

//************************************************************
//************************* EXE ******************************
//************************************************************

double	ft_nor_angle(double angle);
int		ft_which_wall(t_game *game, double ray_angle, int side);
void	ft_load_sprite(t_game *game);
void	ft_free_game(t_game *game);
int		ft_reles(int key, t_game *game);
int		ft_exit(void *param);
int		ft_char_to_int(char c);
t_game	*ft_game_instance(void);
void	ft_start_the_game(t_game *game);
void	ft_init_map(t_game *game);
int		ft_mlx_key(int key, void *gam);
int		ft_game_loop(void);
void	ft_hook(t_game *game);
void	ft_my_mlx_pixel_put(t_game *game, int x, int y, int color);
void	ft_hook_init_side_dist(t_game *game);
void	ft_hook_find_hit(t_game *game);
void	ft_hook_init_loop(t_game *game, int x);
void	ft_hook_target_draw(t_game *game);
void	ft_hook_find_text_x_y(t_game *game);
void	*ft_calloc(size_t count, size_t size);

//************************************************************
//************************* PARSING **************************
//************************************************************
