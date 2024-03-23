/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 00:16:07 by ranki             #+#    #+#             */
/*   Updated: 2024/03/23 13:46:40 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//****************************************************************
//****************************************************************
//******************************* INCLUDES ***********************
//****************************************************************
//****************************************************************

#include "./minilibx-linux/mlx.h"
#include "./minilibx-linux/mlx_int.h"
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//****************************************************************
//****************************************************************
//******************************** DEFINES ***********************
//****************************************************************
//****************************************************************

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 400
#define M_PI 3.14159265358979323846
#define TILE_SIZE 64
#define FOV 0.66

#include "srcs/gnl/get_next_line.h"
//*****************************************************************
//*****************************************************************
//******************************* STUCTURES ***********************
//*****************************************************************
//*****************************************************************

typedef struct s_map
{
	char			**map2d;
	int				w_map;
	int				h_map;
	double			time;
	double			old_time;
}					t_map;

typedef struct s_player
{
	double			plyr_x;
	double			plyr_y;
	double			dir_x;
	double			dir_y;
	double			plan_x;
	double			plan_y;
}					t_player;

typedef struct s_mlx
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	void			*mlx_p;
	void			*win_p;
	int				endian;
}					t_mlx;

typedef struct s_sprite
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
	int				*pixel_colors;
}					t_sprite;

typedef struct s_game
{
	t_map			*map;
	t_player		*player;
	t_mlx			*mlx;
	t_sprite		**sprite;
	unsigned int	buffer[SCREEN_HEIGHT + 1][SCREEN_WIDTH + 1];
	double			camera_x;
	double			camera_y;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_player_x;
	int				map_player_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	double			wall_x;
	int				pitch;
	int				step_x;
	int				step_y;
	int				side;
	int				line_height;
	int				hit;
	int				draw_start;
	int				draw_end;
	int				tex_num;
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;
	int				color;
	unsigned int	color_ceilling;
	unsigned int	color_round;
	double			move_speed;
	double			sure_mode;
	double			rot_speed;
	double			step_side;
	char			**sprite_path;
	char			*cpy_line;
	char			*type_text;
	char			*path;
	int				b;
	int				r;
	int				g;
	char			**split_rgb;
	int				i;
	int				j;
	int				is_ceilling;
	int				number_player_letter_find;
	int				angle_player;
	int				current_sprite;
	char			*current_line;
	char			*cur_tmp;
	double			sure_mode_h;
	int				index_sprite_path;
	int				count_valid_texture;
	int				count_valid_color;
	int				first;
	int				fd;
	int				flag;
	int				flag_1;
	char			**check_map;
	int				cnt;
	int				is_ws;
	int				has_next_line;
	int				has_prev_line;
	char			*line;
	char			*arg;
	char			*save;
	int				now_is_map;
	int				dirs[4][2];
	int				index_spaces;

}					t_game;

//************************************************************
//************************************************************
//**************************** FUNCTIONS *********************
//************************************************************
//************************************************************

//************************************************************
//************************* EXE ******************************
//************************************************************

double				ft_nor_angle(double angle);
int					ft_which_wall(t_game *game, double ray_angle, int side);
void				ft_load_sprite(t_game *game);
void				ft_free_game(t_game *game);
int					ft_reles(int key, t_game *game);
int					ft_exit(void *param);
int					ft_char_to_int(char c);
t_game				*ft_game_instance(void);
void				ft_start_the_game(t_game *game);
void				ft_init_map(t_game *game, char *args);
int					ft_mlx_key(int key, void *gam);
int					ft_game_loop(void);
void				ft_hook(t_game *game);
void				ft_my_mlx_pixel_put(t_game *game, int x, int y, int color);
void				ft_hook_init_side_dist(t_game *game);
void				ft_hook_find_hit(t_game *game);
void				ft_hook_init_loop(t_game *game, int x);
void				ft_hook_target_draw(t_game *game);
void				ft_hook_find_text_x_y(t_game *game);
void				*ft_calloc(size_t count, size_t size);
void				ft_e_str(char *s);
int					ft_exit(void *param);
void				ft_free_mlx(t_game *game);
void				ft_free_map(t_game *game, int *i);
void				rotate_left(int key, t_game *game);
void				rotate_right(int key, t_game *game);
int					find_nice_pitch(void);
int					check_res(t_game *game);

//************************************************************
//************************* PARSING **************************
//************************************************************

t_map				*fetch_map_params(int fd, t_map *map, char *file_name,
						t_game *game);
unsigned int		parse_line_color(t_game *game, char *line);
char				*parse_lt(char *line);
int					is_line_texture(char *line);
int					open_fd(t_game *game, char *name);
void				prnt(char **arr);
int					is_line_color(char *line);
int					is_only_space(char *str);
char				*remove_last_spaces(char *line);
char				**ft_split(char const *s, char c);
int					ft_strncmp(char *s1, char *s2, size_t n);
char				*remove_first_spaces_until_first_letter(char *line);
unsigned int		rgb_to_hex(int r, int g, int b);
int					is_line_bigger(char *str, int old_len);
int					find_last_non_whitespace_char(char *line);
int					scan_first_last_line(char *line, int line_curr, char **map,
						t_map *map_info);
int					stupid_count_one_algo(char *line, int line_curr,
						char **map);
t_map				*test_map(t_game *game, t_map *map);
t_map				*create_map(t_game *game, t_map *map, char *file);
void				first_check(t_game *game, char **map);
void				set_start_angle_player(t_game *game);
void				ft_check_invalid_char_map(t_game *game);
int					ft_valid_char(char *line);
void				ft_replace_2d(char **array, char to_find, char to_replace);
int					mapvalid(char **map, int mapHeight, int mapWidth,
						t_game *game);
int					check_column_from_top(char **map, int mapHeight, int j);
int					check_column_from_bottom(char **map, int mapHeight, int j);
int					check_line_from_left(char **map, int mapWidth, int i);
int					check_line_from_right(char **map, int mapWidth, int i);
void				ft_set_array_flood(t_game *game);
void				ft_check_map_trade_with_arg(t_game *game);
void				*ft_free(void *ptr);