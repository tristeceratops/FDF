/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:06:16 by ewoillar          #+#    #+#             */
/*   Updated: 2024/04/30 14:13:08 by ewoillar         ###   ########.fr       */
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

	double radian_angle = M_PI / 180.0;
	p2.x = (p.x - p.y) * cos(45 * radian_angle);
	p2.y = (p.x + p.y) * sin(35.26 * radian_angle) - p.z;
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
void draw_isometric_square(t_data *img)
{
	int size = 25;
	t_2dcoord p1 = proj_3d_to_2d((t_3dcoord){0 + S_WIDTH / 2, 0 + S_HEIGHT/2, 0});
	t_2dcoord p2 = proj_3d_to_2d((t_3dcoord){size + S_WIDTH /2, 0 + S_HEIGHT/2, size*2});
	t_2dcoord p3 = proj_3d_to_2d((t_3dcoord){0 + S_WIDTH/2, size + S_HEIGHT/2, 0});
	t_2dcoord p4 = proj_3d_to_2d((t_3dcoord){size + S_WIDTH/2, size + S_HEIGHT/2, 0});
	
	draw_line(p1, p2, img, 0x00F8F8F8);
	draw_line(p3, p4, img, 0x00F8F8F8);
	draw_line(p1, p3, img, 0x00F8F8F8);
	draw_line(p2, p4, img, 0x00F8F8F8);

	t_2dcoord p6 = proj_3d_to_2d((t_3dcoord){size*2 + S_WIDTH /2, 0 + S_HEIGHT/2, 0});
	t_2dcoord p7 = proj_3d_to_2d((t_3dcoord){size*2 + S_WIDTH/2, size + S_HEIGHT/2, 0});
	
	draw_line(p2, p6, img, 0x00F80000);
	draw_line(p4, p7, img, 0x00F80000);
	draw_line(p6, p7, img, 0x00F80000);

	t_2dcoord p8 = proj_3d_to_2d((t_3dcoord){size + S_WIDTH /2, -size + S_HEIGHT/2, 0});
	t_2dcoord p9 = proj_3d_to_2d((t_3dcoord){size*2 + S_WIDTH/2, -size + S_HEIGHT/2, 0});

	draw_line(p2, p8, img, 0x0000F800);
	draw_line(p6, p9, img, 0x0000F800);
	draw_line(p8, p9, img, 0x0000F800);
}


int main(void)
{
	t_vars	vars;
	t_data	img;

	vars.mlx = mlx_init();
	img.img = mlx_new_image(vars.mlx, S_WIDTH, S_HEIGHT);
	vars.win = mlx_new_window(vars.mlx, S_WIDTH, S_HEIGHT, "Hello world!");
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	mlx_hook(vars.win, 2, 1L<<0, close_w, &vars);
	mlx_hook(vars.win, 17, 0L, red_cross, &vars);
	draw_isometric_square(&img);
	generate_square(&img, 0x00ffff, 1, S_WIDTH /2 -1, S_HEIGHT /2 - 1);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_loop(vars.mlx);
}