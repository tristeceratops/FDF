/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:06:16 by ewoillar          #+#    #+#             */
/*   Updated: 2024/04/29 16:22:08 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>


int		close_w(int keycode, t_vars *vars)
{
	printf("keycode: %d\n", keycode);
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

int		red_cross(void)
{
	exit(0);
	return(0);
}
/*
t_coord iso_projection(t_coord coord)
{
	t_coord new_coord;

	new_coord.x = (coord.x - coord.y) * cos(0.523599);
	new_coord.y = -coord.z + (coord.x + coord.y) * sin(0.523599);
	return (new_coord);
}*/

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

//function to generate a square, argument is the image, the color, the size and the left_top corner
void	generate_square(t_data *img, int color, int size, int x, int y)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			my_mlx_pixel_put(img, x + i, y + j, color);
	}
}

void	draw_line_x(t_coord start, t_coord end, t_data *data, int color)
{
	int dx = end.x - start.x;
	int dy = end.y - start.y;
	int y1 = 1;
	if (dy < 0)
	{
		y1 = -1;
		dy = -dy;
	}
	int d = 2 * dy - dx;
	int y = start.y;
	while(start.x <= end.x)
	{
		my_mlx_pixel_put(data, start.x, y, color);
		if (d > 0)
		{
			y += y1;
			d = d + (2 * (dy - dx));
		}
		else
			d = d + 2 * dy;
		start.x += 1;
	}
}
//draw_line_y
void	draw_line_y(t_coord start, t_coord end, t_data *data, int color)
{
	int dx = end.x - start.x;
	int dy = end.y - start.y;
	int x1 = 1;
	if (dx < 0)
	{
		x1 = -1;
		dx = -dx;
	}
	int d = 2 * dx - dy;
	int x = start.x;
	while(start.y <= end.y)
	{
		my_mlx_pixel_put(data, x, start.y, color);
		if (d > 0)
		{
			x += x1;
			d = d + (2 * (dx - dy));
		}
		else
			d = d + 2 * dx;
		start.y += 1;
	}
}
//draw line function that redirect to draw_line_x or draw_line_y depending on the slope of the line
void	draw_line(t_coord start, t_coord end, t_data *data, int color)
{
	if (abs(end.y - start.y) < abs(end.x - start.x))
	{
		if (start.x > end.x)
			draw_line_x(end, start, data, color);
		else
			draw_line_x(start, end, data, color);
	}
	else
	{
		if (start.y > end.y)
			draw_line_y(end, start, data, color);
		else
			draw_line_y(start, end, data, color);
	}
}

//draw square in isometric projection, x and y are the top left corner of the square
void draw_isometric_square(t_coord start, int size, t_data *img)
{
	t_coord p3 = {start.x + size, start.y + size};
	t_coord p4 = {start.x, start.y + size};

	draw_line(p3, p4, img, 0x00FF0000);

	t_coord p7 = {start.x + size / 2 + size, start.y - size / 2 + size};
	t_coord p8 = {start.x + size / 2, start.y - size / 2 + size};

	draw_line(p7, p8, img, 0x00FFFF00);
	draw_line(p3, p7, img, 0x00FF00FF);
	draw_line(p4, p8, img, 0x00FF00FF);
}

int main(void)
{
	t_vars	vars;
	t_data	img;

	vars.mlx = mlx_init();
	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	mlx_hook(vars.win, 2, 1L<<0, close_w, &vars);
	mlx_hook(vars.win, 17, 0L, red_cross, &vars);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_loop(vars.mlx);
}