/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:06:16 by ewoillar          #+#    #+#             */
/*   Updated: 2024/04/29 18:24:00 by ewoillar         ###   ########.fr       */
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
t_2dcoord	proj_3d_to_2d(t_3dcoord p)
{
	t_2dcoord p2;

	p2.x = (p.x - p.y) * 0.71;
	p2.y = ((p.x + p.y) * -0.41) + 0.82 * p.z;
	return (p2);
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


//draw square in isometric projection, x and y are the top left corner of the square
void draw_isometric_square(t_2dcoord start, int size, t_data *img)
{
	t_2dcoord p3 = {start.x + size, start.y + size};
	t_2dcoord p4 = {start.x, start.y + size};

	draw_line(p3, p4, img, 0x00F8F8F8);

	t_2dcoord p7 = {start.x + size / 2 + size, start.y - size / 2 + size};
	t_2dcoord p8 = {start.x + size / 2, start.y - size / 2 + size};

	draw_line(p7, p8, img, 0x00F8F8F8);
	draw_line(p3, p7, img, 0x00F8F8F8);
	draw_line(p4, p8, img, 0x00F8F8F8);
}

void	draw_grid(t_data *img)
{
	int size = 50;
	int x = 1920 / 4 + ((size / 2) * 2);
	int y = 1080 / 4;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			t_2dcoord start = {x, y};
			draw_isometric_square(start, size, img);
			x += size / 2;
		}
		x = 1920 / 4 + (size / 2) - i * size / 2;
		y += (size / 2);
	}
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
	draw_grid(&img);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_loop(vars.mlx);
}