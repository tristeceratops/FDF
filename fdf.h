/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:20:58 by ewoillar          #+#    #+#             */
/*   Updated: 2024/05/23 14:35:12 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <mlx.h>
# include <math.h>
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include <X11/keysym.h>
# include <fcntl.h>
# define B_COLOR 0xd4feea
# define T_COLOR 0xfab8b4

typedef struct s_dot
{
	int	x;
	int	y;
	int	z;
	int	is_last_in_line;
	int	zoom;
	int	color;
}		t_dot;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		win_width;
	int		win_height;
	int		zoom;
	int		x_pad;
	int		y_pad;
	int		min_z;
	int		max_z;
	int		rows;
	int		columns;
	t_dot	**map;
}		t_data;

typedef struct s_bresenham
{
	t_dot	*start;
	t_dot	*end;
	int		dx;
	int		dy;
	int		d;
	int		iterator;
	int		iterator_value;
}		t_bresenham;

void	ft_error(char *str);
t_dot	**read_map(char *path, t_data data);
void	draw_line(t_dot start, t_dot end, t_data *data);
t_dot	projection_iso(t_dot p);
void	draw_map(t_dot **map, t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		get_min_height(t_dot **tableau, int rows, int columns);
int		get_max_height(t_dot **tableau, int rows, int columns);
int		get_rows(t_dot **table);
int		get_columns(t_dot **table);
t_dot	**fill_color_tab(t_data data);
int		get_light(int start, int end, double percentage);
void	free_map(t_dot **table);
int		hexarraytoint(char *hex);
void	move_image(int	*pad, int value, t_data *data);

#endif