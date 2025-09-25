/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 10:00:00 by ai                #+#    #+#             */
/*   Updated: 2025/09/18 23:35:11 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <time.h>
# include <string.h>
# include <stdio.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_mixer.h>

# ifdef __linux__
#  include "../mlx_linux/mlx.h"
# else
#  include "../mlx/mlx.h"
# endif

# define WIN_W 1024
# define WIN_H 768
# define BUFFER_SIZE 1024

typedef struct s_keys
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_audio
{
	Mix_Music	*background_music;
	Mix_Music	*end_music;
	Mix_Chunk	*door_sound;
}	t_audio;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
}	t_ray;

typedef struct s_off2
{
	int	x;
	int	y;
}	t_off2;

typedef struct s_timer_px
{
	int	color;
	int	x_offset;
	int	y_offset;
	int	scaled_x;
	int	scaled_y;
}	t_timer_px;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	char	**map;
	int		**door_states;
	int		map_width;
	int		map_height;
	int		has_doors;

	char	*tex_north_path;
	char	*tex_south_path;
	char	*tex_east_path;
	char	*tex_west_path;
	char	*floor_color;
	char	*ceiling_color;
	int		floor_rgb;
	int		ceiling_rgb;

	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;

	void	*tex_north;
	void	*tex_south;
	void	*tex_east;
	void	*tex_west;
	void	*tex_door;
	void	*tex_end;
	void	*tex_sticker;
	void	*tex_start;
	void	*tex_start2;

	int		*buf_north;
	int		*buf_south;
	int		*buf_east;
	int		*buf_west;
	int		*buf_door;
	int		*buf_end;
	int		*buf_sticker;
	int		*buf_start;
	int		*buf_start2;

	int		tex_w;
	int		tex_h;
	int		end_tex_w;
	int		end_tex_h;
	int		sticker_tex_w;
	int		sticker_tex_h;
	int		start_tex_w;
	int		start_tex_h;

	void	*timer_textures[11];
	int		timer_tex_w;
	int		timer_tex_h;

	void	**torch_frames;
	int		**torch_buffers;
	int		torch_frame_count;
	int		torch_w;
	int		torch_h;
	int		torch_line_lengths[4];
	int		current_frame;
	time_t	last_frame_time;

	time_t	start_time;
	time_t	end_time;
	int		timer_stopped;
	time_t	black_screen_start;

	int		show_start;
	int		start_pressed;
	int		show_end;

	t_keys	keys;
	t_audio	audio;
}	t_game;

/* Basic utility functions */
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int		ft_atoi(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);

/* File reading */
int		get_next_line(int fd, char **line);
void	get_next_line_cleanup(void);
char	*get_line_from_buffer(char *buffer);
char	*update_static_buffer(char *buffer);
int		read_to_buffer(char **buffer, int fd);

/* Game initialization and management */
void	init_game(t_game *game, const char *map_file);
void	free_game(t_game *game);

/* Map parsing */
void	parse_map(t_game *game, const char *filename);
void	parse_error(void);
int		parse_config_line(t_game *game, char *line);
void	read_complete_map(t_game *game, int fd, char *first_line);

/* Map validation */
int		validate_map(t_game *game);
int		validate_colors(t_game *game);
int		validate_map_complete(t_game *game);
int		convert_colors(t_game *game);

/* Map utilities */
int		find_player_position(t_game *game, int *x, int *y);
void	calculate_map_dimensions(t_game *game);
int		validate_texture_path(char *path);

/* Parser utilities */
void	free_split(char **split);
void	free_lines(char **lines, int count);
int		is_map_line(char *line);
void	extract_map_from_lines(t_game *game, char **lines, int count);
void	allocate_and_fill_map(t_game *game, char **lines);
int		is_valid_map_line(char *line);
void	parse_and_store_config(t_game *game, int fd);

/* Door utilities */
void	initialize_door_states(t_game *game, int row);

/* Memory management */
void	free_map(t_game *game);

/* Player management */
void	set_player_position(t_game *game, int i);
void	move_player(t_game *game);

/* Texture management */
void	load_textures(t_game *game);
int		load_wall_textures_from_config(t_game *game);
void	load_timer_textures(t_game *game);
void	load_start_textures(t_game *game);
void	load_torch_animation(t_game *game);
void	free_textures(t_game *game);
void	free_torch_animation(t_game *game);

/* Rendering */
void	raycast_scene(t_game *game);
void	draw_background(t_game *game);
void	draw_map(t_game *game);
void	draw_wall_column(t_game *game, t_ray *ray, int x, int y);
void	draw_timer(t_game *game);
void	draw_timer_char(t_game *game, void *texture_ptr, t_off2 offset);
void	draw_door_counter(t_game *game);
void	draw_torch(t_game *game);
void	draw_start_screen(t_game *game);
void	draw_end_screen(t_game *game);
void	calculate_step_and_side_dist(t_game *game, t_ray *ray);
void	clamp_map_x(t_game *game, t_ray *ray);
void	clamp_map_y(t_game *game, t_ray *ray);

/* Event handling */
int		close_window(t_game *game);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		mouse_event(int button, int x, int y, t_game *game);
int		game_loop(t_game *game);
int		handle_esc_key(t_game *game);

/* Audio functions */
void	init_audio(t_game *game);
void	cleanup_audio(t_game *game);
void	play_background_music(t_game *game);
void	play_end_music(t_game *game);
void	play_door_sound(t_game *game);

/* Utility functions */
int		count_open_doors(t_game *game);
int		count_total_doors(t_game *game);
int		can_move_to(t_game *game, double new_x, double new_y);
void	move_forward_backward(t_game *game, int forward);
void	handle_door_interaction(t_game *game);
void	init_ray_params(t_game *game, int x, t_ray *ray);

/* Drawing utilities */
void	draw_square(t_game *game, int *params, int size, int color);
void	draw_line(t_game *game, int *start, int *end, int color);

/* Texture loading utilities */
int		load_special_textures(t_game *game);
void	cleanup_timer_textures(t_game *game, int count);
int		load_start_texture(t_game *game);

int		validate_map_complete(t_game *game);
int		validate_flood_fill(t_game *game);
int		check_map_borders(t_game *game, char **visited);
int		*get_wall_texture(t_game *game, t_ray *ray);
void	draw_no_texture_column(t_game *game, t_ray *ray, int x);
void	draw_textured_column(t_game *game, t_ray *ray, int x, int *texture);
int		blend_colors(int color1, int color2, float opacity);
void	initialize_all_doors(t_game *game);
int		verify_textures_loaded(t_game *game);

/* Aggiungi queste dichiarazioni al tuo cube3d.h esistente */

/* Door utilities - NUOVE FUNZIONI */
void	initialize_door_states(t_game *game, int row);
void	initialize_all_doors(t_game *game);
int		verify_textures_loaded(t_game *game);

/* Texture management - FUNZIONI ESISTENTI, non serve ridichiarare */
void	load_textures(t_game *game);
int		load_wall_textures_from_config(t_game *game);
void	load_start_textures(t_game *game);
void	load_torch_animation(t_game *game);
int		load_special_textures(t_game *game);
void	free_textures(t_game *game);
void	free_torch_animation(t_game *game);

#endif