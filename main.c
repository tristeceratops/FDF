/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:06:16 by ewoillar          #+#    #+#             */
/*   Updated: 2024/04/29 14:21:25 by ewoillar         ###   ########.fr       */
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

//function to draw a smiley face
void	draw_smiley(t_data *img, int color)
{
	//face with draw_line
	draw_line((t_coord){100, 100}, (t_coord){160, 100}, img, color);
	draw_line((t_coord){100, 100}, (t_coord){100, 160}, img, color);
	draw_line((t_coord){160, 100}, (t_coord){160, 160}, img, color);
	draw_line((t_coord){100, 160}, (t_coord){160, 160}, img, color);
	//eyes
	draw_line((t_coord){110, 110}, (t_coord){120, 110}, img, color);
	draw_line((t_coord){140, 110}, (t_coord){150, 110}, img, color);
	//nose
	draw_line((t_coord){130, 120}, (t_coord){130, 130}, img, color);
	//mouth
	draw_line((t_coord){120, 140}, (t_coord){140, 140}, img, color);
	draw_line((t_coord){120, 140}, (t_coord){130, 150}, img, color);
	draw_line((t_coord){130, 150}, (t_coord){140, 140}, img, color);
}


int main(void)
{
	t_vars	vars;
	t_data	img;

	vars.mlx = mlx_init();
	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	//generate_square(&img, 0x00FF0000, 50, 100, 100);
	//generate_square(&img, 0x00FFFF00, 50, 500, 500);
	//generate_square(&img, 0x0000FFFF, 100, 1820, 980);
	mlx_hook(vars.win, 2, 1L<<0, close_w, &vars);
	mlx_hook(vars.win, 17, 0L, red_cross, &vars);
	draw_smiley(&img, 0x00FF0000);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	draw_line((t_coord){100, 100}, (t_coord){200, 200}, &img, 0x00FF0000);
	mlx_loop(vars.mlx);
}